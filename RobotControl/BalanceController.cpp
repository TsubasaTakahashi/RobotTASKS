#include "BalanceController.h"

namespace RobotControl
{
	BalanceController::BalanceController(Hardware::SensorManager* sensorManager,
									Balancer*	balancer)
		:mSensorManager(sensorManager),
		mBalancer(balancer),
		mLeftWheelPwm(0),
		mRightWheelPwm(0)
		{

		}

	void BalanceController::GetWheelPwm(int* wheelPwm)
	{
		wheelPwm[0] = mLeftWheelPwm;
		wheelPwm[1] = mRightWheelPwm;
	}

	void BalanceController::CalcWheelPwm(int forward, int turn)
	{
		int* wheelMotorRa;
		int angle = mSensorManager->getRobotAv();  // ジャイロセンサ値

		wheelMotorRa = (int* )malloc(sizeof(int)*2);
		mSensorManager->getWheelMotorRa(wheelMotorRa);

		int leftWheelEnc = wheelMotorRa[0]; // 左モータ回転角度
		int rightWheelEnc = wheelMotorRa[1]; // 右モータ回転角度

		mBalancer -> setCommand(forward, turn);

		int battery = mSensorManager->getBatteryVoltage();

		mBalancer -> update(angle, rightWheelEnc, leftWheelEnc, battery);

		// 左右モータのPWM値を算出する
		mLeftWheelPwm = (mBalancer->getPwmLeft());
		mRightWheelPwm = (mBalancer->getPwmRight());

		free(wheelMotorRa);
	}

}  // namespace 走行体制御
