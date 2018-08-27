#ifndef RobotControl_RobotController_H
#define RobotControl_RobotController_H

#include "PwmVoltageCorrection.h" //"走行体制御/PWM電圧補正.h"
#include "BalanceController.h" //"走行体制御/姿勢制御.h"
#include "TailController.h" //"走行体制御/尻尾制御.h"
#include "LineTracerController.h" //"走行体制御/ライントレース制御.h"
#include "Motor.h" //"ハード/PWM左右モータ個体差補正.h"
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
														Hardware::Motor& leftWheel,
														Hardware::Motor& rightWheel,
														Hardware::Motor& tailMotor);

	private:
		BalanceController* mBalanceCtrl;
		LineTracerController* mLineTrCtrl;
		TailController* mTailCtrl;
		PwmVoltageCorrection* mPwmVolCorr;
		Hardware::Motor& mLeftWheel;
		Hardware::Motor& mRightWheel;
		Hardware::Motor& mTailMotor;

	public:
		void RunSpecifiedVal(int foward, int turn, int tailAngle, bool balance);

		void RunLineTracer(int foward, int brightnessThreshold, int tailAngle, bool balance);

};

}  // namespace 走行体制御
#endif
