#include "LineTracerController.h"

namespace RobotControl
{
	LineTracerController::LineTracerController(PidController* pidCtrl,
								Hardware::SensorManager* sensorManager)
							:mLineTracerPidCtrl(pidCtrl),
							mSensorManager(sensorManager){

							};

	int LineTracerController::AjustTurnVal(int brightnessThreshold)
	{
		int turnVal = 0;
		int currentBrightness = 0;

		currentBrightness = mSensorManager->getBrightness();
		turnVal = mLineTracerPidCtrl->CalcControlVal(currentBrightness, brightnessThreshold);

		int dbg[2] = {0};
		mSensorManager->getWheelMotorRa(dbg);
		mDbg_0 = mSensorManager->getBrightness();
		mDbg_1 = mSensorManager->getTailMotorRa();
		mDbg_2 = mSensorManager->getRobotAv();
		mDbg_3 = mSensorManager->getBatteryVoltage();
		mDbg_4 = dbg[0];
		mDbg_5 = dbg[1];
		mDbg_6 = turnVal;

		return turnVal;
	}
}  // namespace 走行体制御
