#include "PwmVoltageCorr.h"

namespace RobotControl
{
  PwmVoltageCorr(int refVoltage,
                Hardware::SensorManager sensorManager)
        :mRefVoltage(refVoltage),
        mSensorManager(sensorManager){

        }

  int PwmVoltageCorr::PwmVolCorr(int nCorrPWM)
  {
    int motorVoltage = 0;
    double corrPwm = 0;

    motorVoltage = mSensorManager.getBatteryVoltage();

    corrPwm = (double)nCorrPWM * (double)mRefVoltage / (double)motorVoltage;

    return (int)corrPwm;
  }
}  // namespace 走行体制御
