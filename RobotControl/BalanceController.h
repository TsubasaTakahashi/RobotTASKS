#ifndef RobotControl_BalanceController_H
#define RobotControl_BalanceController_H

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

#include "SensorManager.h" //"ハード/センサ管理.h"
#include "BalancerCpp.h"

namespace RobotControl
{
class BalanceController
{
	public:
		explicit BalanceController(SensorManager* sensorManager,
															Balancer*	balancer);

	private:
		int mLeftWheelPwm;
		int mRightWheelPwm;

		SensorManager* mSensorManager;
		Balancer*	mBalancer;

	public:
		void GetWheelPwm(int* wheelPwm);

		void CalcWheelPwm(int forward, int turn);

};

}  // namespace 走行体制御
#endif
