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

		mDbg_0 = angle;
		mDbg_1 = wheelMotorRa[0];
		mDbg_2 = wheelMotorRa[1];
		mDbg_3 = battery;
		mDbg_4 = mLeftWheelPwm;
		mDbg_5 = mRightWheelPwm;

		free(wheelMotorRa);
	}

	void BalanceController::init() {
    int offset = mSensorManager->getRobotAv();  // ジャイロセンサ値

    // モータエンコーダをリセットする
    //mLeftWheel.reset();
    //mRightWheel.reset();

    // 倒立振子制御初期化
    mBalancer->init(offset);
}

}  // namespace 走行体制御
