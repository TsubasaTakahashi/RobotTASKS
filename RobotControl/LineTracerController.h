#ifndef RobotControl_LineTracerController_H
#define RobotControl_LineTracerController_H

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

#include "SensorManager.h"//"ハード/センサ管理.h"
#include "PidController.h"

namespace RobotControl
{
class LineTracerContoroller
{
	public:
		explicit LineTracerContoroller(PidController* pidCtrl
														Hardware::SensorManager* sensorManager);

	private:
		PidController* mLineTracerPidCtrl;
		Hardware::SensorManager* mSensorManager;

	public:
		int AjustTurnVal(int brightnessThreshold);

};

}  // namespace 走行体制御
#endif
