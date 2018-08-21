#ifndef RobotControl_TailController_H
#define RobotControl_TailCont_H

#include "SensorManager.h"//"ハード/センサ管理.h"
#include "PidController.h"

namespace RobotControl
{
class TailContoroller
{
	public:
		explicit TailContoroller(PidController* pidCtrl
														Hardware::SensorManager* sensorManager);

	private:
		PidController* mTailPidCtrl;
		Hardware::SensorManager* mSensorManager;

	public:
		int AjustTailAngle(int targetTailAng);

};

}  // namespace 走行体制御
#endif
