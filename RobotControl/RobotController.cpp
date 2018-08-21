#include "RobotController.h"

namespace RobotControl
{
  RobotController(BalanceController* balanceCtrl,
                          LineTracerController* lineTrCtrl,
                          TailContoroller* tailCtrl,
                          PwmVoltageCorr* pwmVolCorr,
                          Motor& leftWheel,
                          Motor& rightWheel,
                          Motor& tailMotor)
                          :mBalanceCtrl(balanceCtrl),
                          mLineTrCtrl(lineTrCtrl),
                          mTailCtrl(tailCtrl),
                          mPwmVolCorr(pwmVolCorr),
                          mLeftWheel(leftWheel),
                          mRightWheel(rightWheel),
                          mTailMotor(tailMotor)
  {
  }

  void RobotController::RunSpecifiedVal(int foward, int turn, int tailAngle, bool balance){
    int* leftWheelPwm;
    int* rightWheelPwm;
    int tailMotorPwm = 0;
    int corrleftWheelPwm = 0;
    int corrRightWheelPwm = 0;
    int corrTailMotorPwm = 0;

    if(balance == true){
      mBalanceCtrl.CalcWheelPwm(foward, turn); //姿勢制御の補正もいれてPWM値を算出する
      mBalanceCtrl.GetWheelPwm(leftWheelPwm, rightWheelPwm);
    }
    else{
      //foward, turnから PWM 値を計算する
    }

    tailMotorPwm = mTailCtrl.AjustTailAngle(tailAngle);

    //PWM電圧補正
    corrleftWheelPwm  = mPwmVolCorr.PwmVolCorr(*leftWheelPwm);
    corrRightWheelPwm = mPwmVolCorr.PwmVolCorr(*rightWheelPwm);
    corrTailMotorPwm  = mPwmVolCorr.PwmVolCorr(tailMotorPwm);

    mLeftWheel -> setPWM(corrleftWheelPwm);
    mRightWheel -> setPWM(corrRightWheelPwm);
    mTailMotor -> setPWM(corrTailMotorPwm);
  }

  void RobotController::RunLineTracer(int foward, int brightnessThreshold, int tailAngle, bool balance)
  {
    int turn = 0;
    int* leftWheelPwm;
    int* rightWheelPwm;
    int tailMotorPwm = 0;
    int corrleftWheelPwm = 0;
    int corrRightWheelPwm = 0;
    int corrTailMotorPwm = 0;

    turn = mLineTrCtrl.AjustTurnVal(brightnessThreshold);

    if(balance == true){
      mBalanceCtrl.CalcWheelPwm(foward, turn); //姿勢制御の補正もいれてPWM値を算出する
      mBalanceCtrl.GetWheelPwm(leftWheelPwm, rightWheelPwm);
    }
    else{
      //foward, turnから PWM 値を計算する
    }

    tailMotorPwm = mTailCtrl.AjustTailAngle(tailAngle);

    //PWM電圧補正
    corrleftWheelPwm  = mPwmVolCorr.PwmVolCorr(*leftWheelPwm);
    corrRightWheelPwm = mPwmVolCorr.PwmVolCorr(*rightWheelPwm);
    corrTailMotorPwm  = mPwmVolCorr.PwmVolCorr(tailMotorPwm);

    mLeftWheel -> setPWM(corrleftWheelPwm);
    mRightWheel -> setPWM(corrRightWheelPwm);
    mTailMotor -> setPWM(corrTailMotorPwm);

  }
}  // namespace 走行体制御
