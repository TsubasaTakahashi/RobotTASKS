#include "PwmVoltageCorrection.h"

namespace RobotControl
{
  PwmVoltageCorrection::PwmVoltageCorrection(int refVoltage,
                Hardware::SensorManager* sensorManager)
        :mRefVoltage(refVoltage),
        mSensorManager(sensorManager){

        }

  int PwmVoltageCorrection::PwmVoltageCorrect(int nCorrPWM)
  {
    int motorVoltage = 0;
    double corrPwm = 0;

    motorVoltage = mSensorManager.getBatteryVoltage();

    corrPwm = (double)nCorrPWM * (double)mRefVoltage / (double)motorVoltage;

    return (int)corrPwm;
  }
}  // namespace 走行体制御
