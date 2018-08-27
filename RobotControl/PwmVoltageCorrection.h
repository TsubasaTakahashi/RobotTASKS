#ifndef RobotControl_PwmVoltageCorr_H
#define RobotControl_PwmVoltageCorr_H

#include "SensorManager.h"

namespace RobotControl
{
class PwmVoltageCorrection
{
	public:
		explicit PwmVoltageCorrection(int refVoltage,
												Hardware::SensorManager* sensorManager);

	private:
		int mRefVoltage;

		Hardware::SensorManager* mSensorManager;

	public:
		int PwmVoltageCorrect(int nCorrPWM);

};

}  // namespace 走行体制御
#endif
