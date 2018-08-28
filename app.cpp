#include "app.h"
#include "SectionManager.h"
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
#define PWM_REF_VOLTAGE 8000 //mv

//検知用パラメータ
#define IMP_DET_T_THRESHOLD 15 //衝撃検知　持続時間
#define IMP_DET_T_WIDTH 30 //閾値の幅

//検知の対応番号
#define DISTANCE_DET 0
#define GRAY_DET 1
#define IMPACT_DET 2
#define STEP_DET 3

//検知の対応
#define DISTANCE_DET_THRESHOLD 0
#define GRAY_DET_THRESHOLD 0
#define IMPACT_DET_THRESHOLD 0
#define STEP_DET_THRESHOLD 0

//姿勢
#define BALANCE_ON 1
#define BALANCE_OFF 0

//尻尾の角度
#define TAIL_ANGLE_STAND_UP  75 /* 完全停止時の角度[度] */
#define TAIL_ANGLE_DRIVE      3 /* バランス走行時の角度[度] */

#define LIGHT_WHITE  69         /* 白色の光センサ値 @試走会1 かなこう*/
#define LIGHT_BLACK  2          /* 黒色の光センサ値 */
#define TARGET_VAL_LINETRACE (LIGHT_WHITE + LIGHT_BLACK)/2 //ライントレース走行の目標反射光

//フォワード値の定義
#define NORMAL 80
#define HIGH 100
#define LOW 60
#define NORMAL_N -80
#define HIGH_N -100
#define LOW_N -60
#define STOP 0

#define TIRE_RADIUS 5 /* タイヤの半径[cm] */

// デストラクタ問題の回避
// https://github.com/ETrobocon/etroboEV3/wiki/problem_and_coping
void *__dso_handle = 0;

// using宣言
using Hardware::ColorSensorTASKS;
using Hardware::GyroSensorTASKS;
using Hardware::MotorTASKS;
using Hardware::MotorRaSensor;
using Hardware::BatterySensor;
using Scenario::SectionLineTracer;
using Scenario::SectionScenarioTracer;
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

static RobotControl::PwmVoltageCorrection       *gPwmVolCorr; //PWM 電圧補正

static RobotControl::RobotController      *gRobotCtrl; //走行体制御
static RobotControl::TailController      *gTailCtrl; //尻尾制御

// オブジェクトの定義:ハードウェアパッケージ
static Hardware::SensorManager            *gSensorManager; //センサ管理
static Hardware::BatterySensor            *gBatterySensor; //バッテリセンサ
ColorSensorTASKS   gColorSensorTASKS(PORT_3); //カラーセンサ
GyroSensorTASKS    gGyroSensorTASKS(PORT_4); //
MotorTASKS         gLeftWheel(PORT_C);
MotorTASKS         gRightWheel(PORT_B);
MotorTASKS         gTailMotor(PORT_A);
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
static SectionLineTracer     gSection_1(NORMAL, TAIL_ANGLE_DRIVE, BALANCE_ON, DISTANCE_DET, 300, TARGET_VAL_LINETRACE); //フォワード値, 尻尾の角度, 姿勢, 使用する検知, 検知の閾値, 反射光の閾値
static SectionScenarioTracer gSection_2(NORMAL_N, TAIL_ANGLE_DRIVE, BALANCE_ON, DISTANCE_DET, -100, 0); //フォワード値, 尻尾の角度, 姿勢, 使用する検知, 検知の閾値, ターン値
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

static int gGrayDetDuration = 20;
static int gGrayDetWidth = 0;
//
static int gActDuration = 15; //段差検知
static int gTireRadius = TIRE_RADIUS;

static FILE     *BtFile = NULL;     /* Bluetoothファイルハンドル */
static int      bt_cmd = 0;     /* Bluetoothコマンド 1:リモートスタート */

/**
 * EV3システム生成
 */
static void user_system_create() {
    // [TODO] タッチセンサの初期化に2msのdelayがあるため、ここで待つ
    tslp_tsk(2);

    // オブジェクトの作成
    gBatterySensor = new Hardware::BatterySensor();
    gSensorManager = new Hardware::SensorManager(gBatterySensor,
                                                 gColorSensorTASKS,
                                                 gGyroSensorTASKS,
                                                 gLWheelRaSensor,
                                                 gRWheelRaSensor,
                                                 gTailRaSensor);

    gDistDet       = new Detection::DistanceDetection(gTireRadius);
    gGrayDet       = new Detection::GrayDetection(gGrayDetDuration, gGrayDetWidth);
    gImpactDet     = new Detection::ImpactDetection(gImpactDetTimeThreshold, gImpactDetTimeWidth);
    gStepDet       = new Detection::StepDetection(gActDuration);
    gDetManager    = new Detection::DetectionManager(gSensorManager,
                                                     gDistDet,
                                                     gGrayDet,
                                                     gStepDet,
                                                     gImpactDet);

   gPwmVolCorr = new RobotControl::PwmVoltageCorrection(gPwmRefVoltage,
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
   gTailCtrl  = new RobotControl::TailController(gPidTail, gSensorManager); //尻尾制御

   gRobotCtrl = new RobotControl::RobotController(gBalanceCtrl, gLineTrCtrl, gTailCtrl,
                                                  gPwmVolCorr,
                                                  gLeftWheel,
                                                  gRightWheel,
                                                  gTailMotor
                                                ); //走行体制御

    gSectManager = new Scenario::SectionManager(gSection,
                                              //(int)ARRAY_LENGTH(gSection),
                                              gRobotCtrl,
                                              gDetManager);

    // シナリオを構築する
    //for (uint32_t i = 0; i < (sizeof(gScenes)/sizeof(gScenes[0])); i++) {
    //    gScenario->add(&gScenes[i]);
    //}

    /* Open Bluetooth file */
    BtFile = ev3_serial_open_file(EV3_SERIAL_BT);
    //assert(BtFile != NULL);

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

    fclose(BtFile);
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

    if(BtFile != NULL){
      /* Bluetooth通信タスクの起動 */
      act_tsk(BT_TASK);
    }

    // 周期ハンドラ開始
    ev3_sta_cyc(EV3_CYC_TRACER);

    slp_tsk();  // バックボタンが押されるまで待つ

    // 周期ハンドラ停止
    ev3_stp_cyc(EV3_CYC_TRACER);

    if(BtFile != NULL){
      //Bluetooth 処理停止
      ter_tsk(BT_TASK);
    }

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
        if(BtFile != NULL){
          fprintf(BtFile, "SectionManager foward = %d, tailAngle = %d, balance = %d, detection = %d, detectionThreshold = %d, originalVal = %d\n
          gRobotCtrl wheelPwm[0] = %d, wheelPwm[1] = %d, tailMotorPwm = %d, corrleftWheelPwm = %d, corrRightWheelPwm = %d, corrTailMotorPwm = %d\n",
          gSectManager->mDbg[0], gSectManager->mDbg[1], gSectManager->mDbg[2], gSectManager->mDbg[3], gSectManager->mDbg[4], gSectManager->mDbg[5],
          gRobotCtrl->mDbg[0], gRobotCtrl->mDbg[1], gRobotCtrl->mDbg[2], gRobotCtrl->mDbg[3], gRobotCtrl->mDbg[4], gRobotCtrl->mDbg[5]);
        }
        gSectManager -> Run();  // 倒立走行
    }

    ext_tsk();
}

//*****************************************************************************
// 関数名 : bt_task
// 引数 : unused
// 返り値 : なし
// 概要 : Bluetooth通信によるリモートスタート。 Tera Termなどのターミナルソフトから、
//       ASCIIコードで1を送信すると、リモートスタートする。
//*****************************************************************************
void bt_task(intptr_t unused)
{
  while(1)
    {
      uint8_t c = fgetc(BtFile); /* 受信 */
      switch(c)
        {
        case '1':
          bt_cmd = 1;
          break;
        default:
          break;
        }
      fputc(c, BtFile); /* エコーバック */
    }
}
