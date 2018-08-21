#include "app.h"
#include "Senario.h"
#include "RobotController.h"

#define ARRAY_LENGTH(array) (sizeof(array) / sizeof(array[0]))

//PID制御用パラメータ
//ライントレース用
#define LT_PROPORTIONAL_FACTOR 0.9 /* 比例係数 */
#define LT_DIFFERENTIAL_FACTOR 0.0 /* 微分制御 */
#define LT_INTEGRATION_FACTOR 0.0 /* 積分制御 */
#define LT_PID_GAIN 0.0
#define LT_PID_OFFSET 0.0
//尻尾制御用
#define TAIL_PROPORTIONAL_FACTOR 0.5 /* 比例係数 */
#define TAIL_DIFFERENTIAL_FACTOR 0.0 /* 微分制御 */
#define TAIL_INTEGRATION_FACTOR 0.0 /* 積分制御 */
#define TAIL_PID_GAIN 0.0
#define TAIL_PID_OFFSET 0.0

#define DELTA_T 0.004  /* ループタスクの1回の処理時間 */

//PID電圧補正用パラメータ
#define PWM_REF_VOLTAGE 300 //mv

//検知用パラメータ
#define IMP_DET_T_THRESHOLD = 15; //衝撃検知　持続時間
#define IMP_DET_T_WIDTH = 30;


// デストラクタ問題の回避
// https://github.com/ETrobocon/etroboEV3/wiki/problem_and_coping
void *__dso_handle = 0;

// using宣言
using Hardware::ColorSensor;
using Hardware::GyroSensor;
using Hardware::Motor;
using Hardware::MotorRaSensor;
using Hardware::BatterySensor;
using Scenario::SectionLineTracer;
using Scenario::SectionSenarioTracer;
using Scenario::SectionInfo;

//using ev3api::TouchSensor;
//using ev3api::Clock;


// オブジェクトを静的に確保する
//Clock       gClock;
//TouchSensor gTouchSensor(PORT_1);

// オブジェクトの定義:走行体制御パッケージ
static RobotControl::BalanceController    *gBalanceCtrl; //姿勢制御
static RobotControl::LineTracerController *gLineTrCtrl; //ライントレース制御

static RobotControl::PidController        *gPidLine; //ライントレース用PID制御
static RobotControl::PidController        *gPidTail; //尻尾制御用PID制御

static RobotControl::PwmVoltageCorr       *gPwmVolCorr; //PWM 電圧補正

static RobotControl::RobotController      *gRobotCtrl; //走行体制御
static RobotControl::TailContoroller      *gTailCtrl; //尻尾制御

// オブジェクトの定義:ハードウェアパッケージ
static Hardware::SensorManager            *gSensorManager; //センサ管理
static Hardware::BatterySensor            *gBatterySensor; //バッテリセンサ
ColorSensor   gColorSensor(PORT_3); //カラーセンサ
GyroSensor    gGyroSensor(PORT_4); //
Motor         gLeftWheel(PORT_C);
Motor         gRightWheel(PORT_B);
Motor         gTailMotor(PORT_A);
MotorRaSensor gLWheelRaSensor(PORT_C);
MotorRaSensor gRWheelRaSensor(PORT_B);
MotorRaSensor gTailRaSensor(PORT_A);

// オブジェクトの定義:検知
static Detection::DetectionManager  *gDetManager;
static Detection::DistanceDetection *gDistDet;
static Detection::GrayDetection     *gGrayDet;
static Detection::ImpactDetection   *gImpactDet;
static Detection::StepDetection     *gStepDet;

//オブジェクトの定義:シナリオ
static Scenario::SectionManager       *gSectManager;

//オブジェクトの定義:バランサ
static Balancer        *gBalancer;

//区間例
static SectionLineTracer    gSection_1(0, 0, 0, 0, 0, 0); //フォワード値, 尻尾の角度, 姿勢, 使用する検知, 検知の閾値, 反射光の閾値
static SectionSenarioTracer gSection_2(0, 0, 0, 0, 0, 0); //フォワード値, 尻尾の角度, 姿勢, 使用する検知, 検知の閾値, ターン値
///区間の数だけオブジェクトを生成する

//ここに区間を格納する
static SectionInfo gSection[] = {gSection_1, gSection_2}; //例

//
static double gLtPParameter = LT_PROPORTIONAL_FACTOR;
static double gLtDParameter = LT_DIFFERENTIAL_FACTOR;
static double gLtIParameter = LT_INTEGRATION_FACTOR;
static double gLtPidGain = LT_PID_GAIN;
static double gLtPidOffset = LT_PID_OFFSET;

static double gTailPParameter = TAIL_PROPORTIONAL_FACTOR;
static double gTailDParameter = TAIL_DIFFERENTIAL_FACTOR;
static double gTailIParameter = TAIL_INTEGRATION_FACTOR;
static double gTailPidGain = TAIL_PID_GAIN;
static double gTailPidOffset = TAIL_PID_OFFSET;

static double gDeltaT = DELTA_T;

//
static int gPwmRefVoltage = PWM_REF_VOLTAGE;

//Detection
static int gImpactDetTimeThreshold = IMP_DET_T_THRESHOLD;
static int gImpactDetTimeWidth = IMP_DET_T_WIDTH;

/**
 * EV3システム生成
 */
static void user_system_create() {
    // [TODO] タッチセンサの初期化に2msのdelayがあるため、ここで待つ
    tslp_tsk(2);

    // オブジェクトの作成
    gBatterySensor = new Hardware::BatterySensor();
    gSensorManager = new Hardware::SensorManager(gBatterySensor,
                                                 gColorSensor,
                                                 gGyroSensor,
                                                 gLWheelRaSensor,
                                                 gRWheelRaSensor,
                                                 gTailRaSensor);

    gDistDet       = new Detection::DistanceDetection();
    gGrayDet       = new Detection::GrayDetection();
    gImpactDet     = new Detection::ImpactDetection(gImpactDetTimeThreshold, gImpactDetTimeWidth);
    gStepDet       = new Detection::StepDetection();
    gDetManager    = new Detection::DetectionManager(gSensorManager,
                                                     gDistDet,
                                                     gGrayDet,
                                                     gImpactDet,
                                                     gStepDet);

   gPwmVolCorr = new RobotControl::PwmVoltageCorr(gPwmRefVoltage,
                                                  gSensorManager);

   gPidLine = new RobotControl::PidController(gLtPParameter,
                                              gLtDParameter,
                                              gLtIParameter,
                                              gLtPidGain,
                                              gLtPidOffset,
                                              gDeltaT); //ライントレース用PID制御
   gPidTail = new RobotControl::PidController(gTailPParameter,
                                              gTailDParameter,
                                              gTailIParameter,
                                              gTailPidGain,
                                              gTailPidOffset,
                                              gDeltaT); //尻尾制御用PID制御

   gBalanceCtrl = new RobotControl::BalanceController(gSensorManager, gBalancer); //姿勢制御
   gLineTrCtrl = new RobotControl::LineTracerController(gPidLine, gSensorManager); //ライントレース制御
   gTailCtrl  = new RobotControl::TailContoroller(gPidTail, gSensorManager); //尻尾制御

   gRobotCtrl = new RobotControl::RobotController(gBalanceCtrl, gLineTrCtrl, gTailCtrl
                                                  gPwmVolCorr,
                                                  gLeftWheel,
                                                  gRightWheel,
                                                  gTailMotor
                                                ); //走行体制御

    gSectManager = new Scenario::SectionManager(gSection,
                                              (int)ARRAY_LENGTH(gSection),
                                              gDetManager,
                                              gRobotCtrl);

    // シナリオを構築する
    //for (uint32_t i = 0; i < (sizeof(gScenes)/sizeof(gScenes[0])); i++) {
    //    gScenario->add(&gScenes[i]);
    //}

    // 初期化完了通知
    ev3_led_set_color(LED_ORANGE);
}

/**
 * EV3システム破棄
 */
static void user_system_destroy() {
    gLeftWheel.reset();
    gRightWheel.reset();
    gTailMotor.reset();
    gLWheelRaSensor.reset();
    gRWheelRaSensor.reset();
    gTailRaSensor.reset();

    delete gBalanceCtrl; //姿勢制御
    delete gLineTrCtrl; //ライントレース制御

    delete gPidLine; //ライントレース用PID制御
    delete gPidTail; //尻尾制御用PID制御

    delete gPwmVolCorr; //PWM 電圧補正

    delete gRobotCtrl; //走行体制御
    delete gTailCtrl; //尻尾制御

    delete gSensorManager; //センサ管理
    delete gBatterySensor; //バッテリセンサ

    delete gDetManager;
    delete gDistDet;
    delete gGrayDet;
    delete gImpactDet;
    delete gStepDet;

    delete gSectManager;
}

/**
 * トレース実行タイミング
 */
void ev3_cyc_tracer(intptr_t exinf) {
    act_tsk(TRACER_TASK);
}

/**
 * メインタスク
 */
void main_task(intptr_t unused) {
    user_system_create();  // センサやモータの初期化処理

    // 周期ハンドラ開始
    ev3_sta_cyc(EV3_CYC_TRACER);

    slp_tsk();  // バックボタンが押されるまで待つ

    // 周期ハンドラ停止
    ev3_stp_cyc(EV3_CYC_TRACER);

    user_system_destroy();  // 終了処理

    ext_tsk();
}

/**
 * ライントレースタスク
 */
void tracer_task(intptr_t exinf) {
    if (ev3_button_is_pressed(BACK_BUTTON)) {
        wup_tsk(MAIN_TASK);  // バックボタン押下
    } else {
        区間管理 -> 区間に応じた走行をする();  // 倒立走行
    }

    ext_tsk();
}
