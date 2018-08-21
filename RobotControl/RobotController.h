#ifndef RobotControl_RobotController_H
#define RobotControl_RobotController_H

#include "PwmVoltageCorr.h" //"走行体制御/PWM電圧補正.h"
#include "AttitudeController.h" //"走行体制御/姿勢制御.h"
#include "TailController.h" //"走行体制御/尻尾制御.h"
#include "LineTracerController.h" //"走行体制御/ライントレース制御.h"
#include "Motor.h" //"ハード/PWM左右モータ個体差補正.h"

namespace RobotControl
{
class RobotController
{
	public:
		explicit RobotController(BalanceController* balanceCtrl,
														LineTracerController* lineTrCtrl,
														TailContoroller* tailCtrl,
														PwmVoltageCorr* pwmVolCorr,
														Motor& leftWheel,
														Motor& rightWheel,
														Motor& tailMotor);

	private:
		BalanceController* mBalanceCtrl;
		LineTracerController* mLineTrCtrl;
		TailContoroller* mTailCtrl;
		PwmVoltageCorr* mPwmVolCorr;
		Hardware::Motor& mLeftWheel;
		Hardware::Motor& mRightWheel;
		Hardware::Motor& mTailMotor;

	public:
		void RunSpecifiedVal(int foward, int turn, int tailAngle, bool balance);

		void RunLineTracer(int foward, int brightnessThreshold, int tailAngle, bool balance);

};

}  // namespace 走行体制御
#endif
