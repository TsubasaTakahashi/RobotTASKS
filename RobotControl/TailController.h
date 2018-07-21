#ifndef 走行体制御_尻尾制御_H
#define 走行体制御_尻尾制御_H

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

#include "ハード/モータ.h"
#include "ハード/センサ管理.h"
#include "走行体制御/PID制御.h"
#include "走行体制御/PWM電圧補正.h"

namespace 走行体制御
{
class 尻尾制御
{
private:
	PID制御 尻尾PID制御;
	PWM電圧補正 尻尾PWM電圧補正;
	ハード::モータ 尻尾モータ;
	ハード::モータ モータ;
	ハード::モータ モータ;
	ハード::センサ管理 センサ管理;

public:
	void 尻尾の角度を調整する(int 目標角度);

};

}  // namespace 走行体制御
#endif
