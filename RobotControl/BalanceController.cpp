#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

#include "BalanceController.h"

namespace RobotControl
{
	RobotController(SensorManager* sensorManager,
									Balancer*	balancer)
		:mSensorManager(sensorManager),
		mBalancer(balancer),
		mLeftWheelPwm(0),
		mRightWheelPwm(0)
		{

		}

	int BalanceController::GetWheelPwm(int* wheelPwm)
	{
		int bufWheelPwm[2];
		bufWheelPwm[0] = mLeftWheelPwm;
		bufWheelPwm[1] = mRightWheelPwm;

		wheelPwm = bufWheelPwm;
	}

	void BalanceController::CalcWheelPwm(int forward, int turn)
	{
		int* wheelEnc;
		int angle = mSensorManager.getRobotAv();  // ジャイロセンサ値

		mSensorManager.getWheelMotorRa(int* wheelMotorRa);

    int rightWheelEnc = wheelMotorRa[0]; // 右モータ回転角度
    int leftWheelEnc  = wheelMotorRa[1]; // 左モータ回転角度

    mBalancer -> setCommand(mForward, mTurn);

    int battery = mSensorManager.getBatteryVoltage();

    mBalancer -> update(angle, rightWheelEnc, leftWheelEnc, battery);

    // 左右モータのPWM値を算出する
  	mLeftWheelPwm = (mBalancer->getPwmLeft());
  	mRightWheelPwm = (mBalancer->getPwmRight());
	}

}  // namespace 走行体制御
