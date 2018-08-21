#ifndef RobotControl_PwmVoltageCorr_H
#define RobotControl_PwmVoltageCorr_H

#include "SensorManager.h"

namespace RobotControl
{
class PwmVolCorr
{
	public:
		explicit PwmVolCorr(int refVoltage,
												Hardware::SensorManager* sensorManager);

		~PwmVolCorr(void);

	private:
		int mRefVoltage;

		Hardware::SensorManager* mSensorManager;

	public:
		void PwmVolCorr(int nCorrPWM);

};

}  // namespace 走行体制御
#endif
