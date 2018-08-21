#include "LineTracerController.h"

namespace RobotControl
{
	LineTracerContoroller(PidController* pidCtrl
								Hardware::SensorManager* sensorManager)
							:mLineTracerPidCtrl(pidCtrl),
							mSensorManager(sensorManager){

							};

	int LineTracerContoroller::AjustTurnVal(int brightnessThreshold)
	{
		int turnVal = 0;
		int currentBrightness = 0;

		currentBrightness = mSensorManager.getBrightness();
		turnVal = mTailPidCtrl.CalcControlVal(currentBrightness, brightnessThreshold);

		return turnVal;
	}
}  // namespace 走行体制御
