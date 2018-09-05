#ifndef RobotControl_RobotController_H
#define RobotControl_RobotController_H

#include "PwmVoltageCorrection.h" //"走行体制御/PWM電圧補正.h"
#include "BalanceController.h" //"走行体制御/姿勢制御.h"
#include "TailController.h" //"走行体制御/尻尾制御.h"
#include "LineTracerController.h" //"走行体制御/ライントレース制御.h"
#include "MotorTASKS.h" //"ハード/PWM左右モータ個体差補正.h"
#include <stdlib.h>

namespace RobotControl
{
class RobotController
{
	public:
		explicit RobotController(BalanceController* balanceCtrl,
														LineTracerController* lineTrCtrl,
														TailController* tailCtrl,
														PwmVoltageCorrection* pwmVolCorr,
														Hardware::MotorTASKS& leftWheel,
														Hardware::MotorTASKS& rightWheel,
														Hardware::MotorTASKS& tailMotor);

		int mDbg_0;
		int mDbg_1;
		int mDbg_2;
		int mDbg_3;
		int mDbg_4;
		int mDbg_5;
		int mDbg_6;
		int mDbg_7;
		int mDbg_8;
		int mDbg_9;
		int mDbg_10;

	private:
		BalanceController* mBalanceCtrl;
		LineTracerController* mLineTrCtrl;
		TailController* mTailCtrl;
		PwmVoltageCorrection* mPwmVolCorr;
		Hardware::MotorTASKS& mLeftWheel;
		Hardware::MotorTASKS& mRightWheel;
		Hardware::MotorTASKS& mTailMotor;

	public:
		void RunSpecifiedVal(int foward, int turn, int tailAngle, int balance);

		void RunLineTracer(int foward, int brightnessThreshold, int tailAngle, int balance);

};

}  // namespace 走行体制御
#endif
