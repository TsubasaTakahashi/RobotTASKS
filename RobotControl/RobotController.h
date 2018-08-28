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
