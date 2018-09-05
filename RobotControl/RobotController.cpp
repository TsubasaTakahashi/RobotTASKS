#include "RobotController.h"

namespace RobotControl
{
  RobotController::RobotController(BalanceController* balanceCtrl,
                          LineTracerController* lineTrCtrl,
                          TailController* tailCtrl,
                          PwmVoltageCorrection* pwmVolCorr,
                          Hardware::MotorTASKS& leftWheel,
                          Hardware::MotorTASKS& rightWheel,
                          Hardware::MotorTASKS& tailMotor)
                          :mBalanceCtrl(balanceCtrl),
                          mLineTrCtrl(lineTrCtrl),
                          mTailCtrl(tailCtrl),
                          mPwmVolCorr(pwmVolCorr),
                          mLeftWheel(leftWheel),
                          mRightWheel(rightWheel),
                          mTailMotor(tailMotor),
                          mIsInitialized(false)
  {

  }

  void RobotController::RunSpecifiedVal(int foward, int turn, int tailAngle, int balance){
  //  if (mIsInitialized == false) {
    //    mBalanceCtrl->init();
      //  mIsInitialized = true;
    //}

    int* wheelPwm;
    int tailMotorPwm = 0;
    int corrleftWheelPwm = 0;
    int corrRightWheelPwm = 0;
    int corrTailMotorPwm = 0;


    wheelPwm = (int *)malloc(sizeof(int) * 2);
    if(balance == 1){ // 姿勢ON
      mBalanceCtrl -> CalcWheelPwm(foward, turn); //姿勢制御の補正もいれてPWM値を算出する
      mBalanceCtrl -> GetWheelPwm(wheelPwm);
    }
    else{
      //foward, turnから PWM 値を計算する
      //尻尾走行に切り替えるとき
    }

    tailMotorPwm = mTailCtrl -> AjustTailAngle(tailAngle);

    //PWM電圧補正
    corrleftWheelPwm  = mPwmVolCorr -> PwmVoltageCorrect(wheelPwm[0]);
    corrRightWheelPwm = mPwmVolCorr -> PwmVoltageCorrect(wheelPwm[1]);
    corrTailMotorPwm  = mPwmVolCorr -> PwmVoltageCorrect(tailMotorPwm);

    mLeftWheel.setPWM(corrleftWheelPwm);
    mRightWheel.setPWM(corrRightWheelPwm);
    mTailMotor.setPWM(corrTailMotorPwm);

    mDbg_0 = wheelPwm[0];
    mDbg_1 = wheelPwm[1];
    mDbg_2 = tailMotorPwm;
    mDbg_3 = corrleftWheelPwm;
    mDbg_4 = corrRightWheelPwm;
    mDbg_5 = corrTailMotorPwm;

    free(wheelPwm);
  }


  void RobotController::RunLineTracer(int foward, int brightnessThreshold, int tailAngle, int balance)
  {
    //if (mIsInitialized == false) {
      //  mBalanceCtrl->init();
      //  mIsInitialized = true;
    //}

    int turn = 0;
    int tailMotorPwm = 0;
    int corrleftWheelPwm = 0;
    int corrRightWheelPwm = 0;
    int corrTailMotorPwm = 0;
    int* wheelPwm;

    mDbg_6 = foward;
    mDbg_7 = brightnessThreshold;
    mDbg_8 = tailAngle;
    mDbg_9 = balance;

    turn = mLineTrCtrl -> AjustTurnVal(brightnessThreshold);

    mDbg_10 = turn;
    wheelPwm = (int *)malloc(sizeof(int) * 2);
    if(balance == 1){ //姿勢ON
      mBalanceCtrl -> CalcWheelPwm(foward, turn); //姿勢制御の補正もいれてPWM値を算出する
      mBalanceCtrl -> GetWheelPwm(wheelPwm);
    }
    else{
      //foward, turnから PWM 値を計算する
      //尻尾走行に切り替えるとき
    }

    tailMotorPwm = mTailCtrl -> AjustTailAngle(tailAngle);

    //PWM電圧補正
    corrleftWheelPwm  = mPwmVolCorr -> PwmVoltageCorrect(wheelPwm[0]);
    corrRightWheelPwm = mPwmVolCorr -> PwmVoltageCorrect(wheelPwm[1]);
    corrTailMotorPwm  = mPwmVolCorr -> PwmVoltageCorrect(tailMotorPwm);

    mLeftWheel.setPWM(corrleftWheelPwm);
    mRightWheel.setPWM(corrRightWheelPwm);
    mTailMotor.setPWM(corrTailMotorPwm);

    mDbg_0 = wheelPwm[0];
    mDbg_1 = wheelPwm[1];
    mDbg_2 = tailMotorPwm;
    mDbg_3 = corrleftWheelPwm;
    mDbg_4 = corrRightWheelPwm;
    mDbg_5 = corrTailMotorPwm;
    //mDbg_10 = turn;


    free(wheelPwm);

  }
}  // namespace 走行体制御
