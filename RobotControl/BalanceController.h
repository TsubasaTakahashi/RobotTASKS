#ifndef RobotControl_BalanceController_H
#define RobotControl_BalanceController_H

#include "SensorManager.h" //"ハード/センサ管理.h"
#include "BalancerCpp.h"
#include <stdlib.h>

namespace RobotControl
{
class BalanceController
{
	public:
		explicit BalanceController(Hardware::SensorManager* sensorManager,
															Balancer*	balancer);

	private:
		Hardware::SensorManager* mSensorManager;
		Balancer*	mBalancer;
		int mLeftWheelPwm;
		int mRightWheelPwm;

	public:
		void GetWheelPwm(int* wheelPwm);

		void CalcWheelPwm(int forward, int turn);

};

}  // namespace 走行体制御
#endif
