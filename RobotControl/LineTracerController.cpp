#include "LineTracerController.h"

namespace RobotControl
{
	LineTracerController::LineTracerController(PidController* pidCtrl
								Hardware::SensorManager* sensorManager)
							:mLineTracerPidCtrl(pidCtrl),
							mSensorManager(sensorManager){

							};

	int LineTracerController::AjustTurnVal(int brightnessThreshold)
	{
		int turnVal = 0;
		int currentBrightness = 0;

		currentBrightness = mSensorManager->getBrightness();
		turnVal = mTailPidCtrl->CalcControlVal(currentBrightness, brightnessThreshold);

		return turnVal;
	}
}  // namespace 走行体制御
