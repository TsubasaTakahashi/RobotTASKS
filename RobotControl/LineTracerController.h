#ifndef RobotControl_LineTracerController_H
#define RobotControl_LineTracerController_H

#include "SensorManager.h"//"ハード/センサ管理.h"
#include "PidController.h"

namespace RobotControl
{
class LineTracerController
{
	public:
		explicit LineTracerController(PidController* pidCtrl,
														Hardware::SensorManager* sensorManager);

	private:
		PidController* mLineTracerPidCtrl;
		Hardware::SensorManager* mSensorManager;



	public:
		int AjustTurnVal(int brightnessThreshold);

		int mDbg_0;
		int mDbg_1;
		int mDbg_2;
		int mDbg_3;
		int mDbg_4;
		int mDbg_5;
		int mDbg_6;

};

}  // namespace 走行体制御
#endif
