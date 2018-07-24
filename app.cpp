#include "app.h"
#include "Senario.h"
#include "RobotController.h"

// デストラクタ問題の回避
// https://github.com/ETrobocon/etroboEV3/wiki/problem_and_coping
void *__dso_handle=0;

// using宣言
using Hardware::ColorSensor;
using Hardware::GyroSensor;
using Hardware::Motor;
using Hardware::MotorRaSensor;
using Hardware::BatterySensor;

using ev3api::TouchSensor;
using ev3api::Clock;

// Device objects
// オブジェクトを静的に確保する
ColorSensor gColorSensor(PORT_3);
GyroSensor  gGyroSensor(PORT_4);
Motor       gLeftWheel(PORT_C);
Motor       gRightWheel(PORT_B);
Motor       gTailMotor(PORT_A);

Clock       gClock;
TouchSensor gTouchSensor(PORT_1);

// オブジェクトの定義
static RobotControl::AttitudeController   *gAttiCtrl; //姿勢制御
static RobotControl::LineTracerController *gLineTrCtrl; //ライントレース制御
static RobotControl::PidController        *gPidController; //
static RobotControl::PwmIdCorr            *gPwmIdCorr;

//次回はここから

// scene object
static Scene gScenes[] = {
    //{ TURN_LEFT,   1250, 0 },  // 左旋回1.25秒
    //{ GO_STRAIGHT, 5000, 0 },  // 直進5秒
    //{ TURN_LEFT,   1250, 0 },  // 左旋回1.25秒
    { GO_STRAIGHT, 2500, 0 },   // 直進2.5秒
    { GO_BACK, 2500, 0 },   // 後進2.5秒
    { STOP, 2000, 0 },
    { TAIL_DOWN, 500, 0 },
    { BALANCER_OFF, 50, 0 },
    { GO_STRAIGHT, 5000, 0 },
    { BALANCER_ON, 50, 0},
    { TAIL_UP, 500, 0 },
    { GO_BACK, 5000, 0 }
};

/**
 * EV3システム生成
 */
static void user_system_create() {
    // [TODO] タッチセンサの初期化に2msのdelayがあるため、ここで待つ
    tslp_tsk(2);

    // オブジェクトの作成
    gBalancer        = new Balancer();
    gBalancingWalker = new BalancingWalker(gGyroSensor,
                                           gLeftWheel,
                                           gRightWheel,
                                           gTailMotor,
                                           gBalancer);
    gStarter         = new Starter(gTouchSensor);
    gLineMonitor     = new LineMonitor(gColorSensor);
    gScenarioTimer   = new SimpleTimer(gClock);
    gWalkerTimer     = new SimpleTimer(gClock);
    gLineTracer      = new LineTracer(gLineMonitor, gBalancingWalker);
    gScenario        = new Scenario(0);
    gScenarioTracer  = new ScenarioTracer(gBalancingWalker,
                                          gScenario,
                                          gScenarioTimer);
    gRandomWalker    = new RandomWalker(gLineTracer,
                                        gScenarioTracer,
                                        gStarter,
                                        gWalkerTimer);

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
