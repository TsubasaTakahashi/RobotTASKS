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
		explicit BalanceController();

	private:
		int 左モータのPWM値;

		int 右モータのPWM値;

		PID制御 pID制御;
		ハード::ジャイロセンサ ジャイロセンサ;
		ハード::センサ管理 センサ管理;
		ハード::モータ 右モータ;
		ハード::モータ 左モータ;
		ハード::モータ モータ;
		ハード::センサ管理 センサ管理;

	public:
		int 左モータのPWM値を取得する();

		int 右モータのPWM値を取得する();

		void 左右モータのPWM値を算出する(int フォワード値, int ターン値);

};

}  // namespace 走行体制御
#endif
