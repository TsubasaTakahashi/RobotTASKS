#include "TailContoroller.h"

namespace RobotControl
{
  TailController(PidController* pidCtrl
                Hardware::SensorManager* sensorManager)
              :mPidCtrl(pidCtrl),
              mSensorManager(sensorManager){

              };

  int TailContoroller::AjustTailAngle(int targetTailAng)
  {
    int tailPwm = 0;
    int currentTailAng = 0;

    currentTailAng = mSensorManager.getTailMotorRa();
    tailPwm = mTailPidCtrl.CalcControlVal(currentTailAng, targetTailAng);

    return tailPwm;
  }
}  // namespace 走行体制御
