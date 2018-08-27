#include "RobotController.h"

namespace RobotControl
{
  RobotController::RobotController(BalanceController* balanceCtrl,
                          LineTracerController* lineTrCtrl,
                          TailController* tailCtrl,
                          PwmVoltageCorrection* pwmVolCorr,
                          Hardware::Motor& leftWheel,
                          Hardware::Motor& rightWheel,
                          Hardware::Motor& tailMotor)
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
    int* wheelPwm;
    int tailMotorPwm = 0;
    int corrleftWheelPwm = 0;
    int corrRightWheelPwm = 0;
    int corrTailMotorPwm = 0;


    wheelPwm = (int *)malloc(sizeof(int) * 2);
    if(balance == true){
      mBalanceCtrl -> CalcWheelPwm(foward, turn); //姿勢制御の補正もいれてPWM値を算出する
      mBalanceCtrl -> GetWheelPwm(wheelPwm);
    }
    else{
      //foward, turnから PWM 値を計算する
    }

    tailMotorPwm = mTailCtrl -> AjustTailAngle(tailAngle);

    //PWM電圧補正
    corrleftWheelPwm  = mPwmVolCorr -> PwmVoltageCorrect(wheelPwm[0]);
    corrRightWheelPwm = mPwmVolCorr -> PwmVoltageCorrect(wheelPwm[1]);
    corrTailMotorPwm  = mPwmVolCorr -> PwmVoltageCorrect(tailMotorPwm);

    mLeftWheel.setPWM(corrleftWheelPwm);
    mRightWheel.setPWM(corrRightWheelPwm);
    mTailMotor.setPWM(corrTailMotorPwm);
    free(wheelPwm);
  }


  void RobotController::RunLineTracer(int foward, int brightnessThreshold, int tailAngle, bool balance)
  {
    int turn = 0;
    int tailMotorPwm = 0;
    int corrleftWheelPwm = 0;
    int corrRightWheelPwm = 0;
    int corrTailMotorPwm = 0;
    int* wheelPwm;

    turn = mLineTrCtrl -> AjustTurnVal(brightnessThreshold);

    wheelPwm = (int *)malloc(sizeof(int) * 2);
    if(balance == true){
      mBalanceCtrl -> CalcWheelPwm(foward, turn); //姿勢制御の補正もいれてPWM値を算出する
      mBalanceCtrl -> GetWheelPwm(wheelPwm);
    }
    else{
      //foward, turnから PWM 値を計算する
    }

    tailMotorPwm = mTailCtrl -> AjustTailAngle(tailAngle);

    //PWM電圧補正
    corrleftWheelPwm  = mPwmVolCorr -> PwmVoltageCorrect(wheelPwm[0]);
    corrRightWheelPwm = mPwmVolCorr -> PwmVoltageCorrect(wheelPwm[1]);
    corrTailMotorPwm  = mPwmVolCorr -> PwmVoltageCorrect(tailMotorPwm);

    mLeftWheel.setPWM(corrleftWheelPwm);
    mRightWheel.setPWM(corrRightWheelPwm);
    mTailMotor.setPWM(corrTailMotorPwm);
    free(wheelPwm);

  }
}  // namespace 走行体制御
