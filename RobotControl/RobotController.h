#ifndef RobotControl_RobotController_H
#define RobotControl_RobotController_H

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

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
		explicit RobotController();
		
	private:
		PWM電圧補正 タイヤPWM補正;
		姿勢制御 姿勢制御;
		尻尾制御 尻尾制御;
		ライントレース制御 ライントレース制御;
		ライントレース制御 ライントレース制御;
		PWM左右モータ個体差補正 PWM左右モータ個体差補正;

	public:
		void 指定値走行する(int フォワード値, int ターン値, int 尻尾の角度, boolean 姿勢);

		void ライントレース走行する(int フォワード値, int 反射光の閾値, int 尻尾の角度, boolean 姿勢);

};

}  // namespace 走行体制御
#endif
