#include "app.h"
#include "Senario.h"
#include "RobotController.h"

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
static RobotControl::AttitudeController   *gAttiCtrl; //姿勢制御
static RobotControl::LineTracerController *gLineTrCtrl; //ライントレース制御

static RobotControl::PidController        *gPidLine; //ライントレース用PID制御
static RobotControl::PidController        *gPidTail; //尻尾制御用PID制御

static RobotControl::PwmVoltageCorr       *gPwmVolCorrLWheel; //PWM 電圧補正　左タイヤ
static RobotControl::PwmVoltageCorr       *gPwmVolCorrRWheel; //PWM 電圧補正　右タイヤ
static RobotControl::PwmVoltageCorr       *gPwmVolCorrTail; //PWM 電圧補正　尻尾

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

//区間例
static SectionLineTracer    gSection_1(0, 0, 0, 0, 0, 0); //フォワード値, 尻尾の角度, 姿勢, 使用する検知, 検知の閾値, 反射光の閾値
static SectionSenarioTracer gSection_2(0, 0, 0, 0, 0, 0); //フォワード値, 尻尾の角度, 姿勢, 使用する検知, 検知の閾値, ターン値
///区間の数だけオブジェクトを生成する

static SectionInfo gSection[]={gSection_1, gSection_2}; //例

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
    gImpactDet     = new Detection::ImpactDetection();
    gStepDet       = new Detection::StepDetection();
    gDetManager    = new Detection::DetectionManager(gSensorManager,
                                                     gDistDet,
                                                     gGrayDet,
                                                     gImpactDet,
                                                     gStepDet);

   gPwmVolCorrLWheel = new RobotControl::PwmVoltageCorr(gSensorManager);
   gPwmVolCorrRWheel = new RobotControl::PwmVoltageCorr(gSensorManager);
   gPwmVolCorrTail   = new RobotControl::PwmVoltageCorr(gSensorManager);

   gPidLine = new RobotControl::PidController(); //ライントレース用PID制御
   gPidTail = new RobotControl::PidController(); //尻尾制御用PID制御

   gAttiCtrl = new RobotControl::AttitudeController(gSensorManager); //姿勢制御
   gLineTrCtrl = new RobotControl::LineTracerController(gSensorManager, gPidLine); //ライントレース制御
   gTailCtrl  = new RobotControl::TailContoroller(gSensorManager, gPidTail); //尻尾制御

   gRobotCtrl = new RobotControl::RobotController(gAttiCtrl, gLineTrCtrl, gTailCtrl
                                                  gPwmVolCorrLWheel,
                                                  gPwmVolCorrRWheel,
                                                  gPwmVolCorrTail,
                                                  gLeftWheel,
                                                  gRightWheel,
                                                  gTailMotor
                                                ); //走行体制御

    gSectManager = new Scenario::SectionManager(gSection);

    // シナリオを構築する
    for (uint32_t i = 0; i < (sizeof(gScenes)/sizeof(gScenes[0])); i++) {
        gScenario->add(&gScenes[i]);
    }
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

    delete gRandomWalker;
    delete gScenarioTracer;
    delete gScenario;
    delete gLineTracer;
    delete gWalkerTimer;
    delete gScenarioTimer;
    delete gLineMonitor;
    delete gStarter;
    delete gBalancingWalker;
    delete gBalancer;
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
        gRandomWalker->run();  // 倒立走行
    }

    ext_tsk();
}
