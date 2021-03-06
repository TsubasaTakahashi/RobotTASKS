#include "TailController.h"

namespace RobotControl
{
  TailController::TailController(PidController* pidCtrl,
                Hardware::SensorManager* sensorManager)
              :mTailPidCtrl(pidCtrl),
              mSensorManager(sensorManager){

              };

  int TailController::AjustTailAngle(int targetTailAng)
  {
    int tailPwm = 0;
    int currentTailAng = 0;

    currentTailAng = mSensorManager -> getTailMotorRa();
    tailPwm = mTailPidCtrl -> CalcControlVal(currentTailAng, targetTailAng);

    return tailPwm;
  }
}  // namespace 走行体制御
