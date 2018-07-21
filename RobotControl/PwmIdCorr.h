#ifndef 走行体制御_P_W_M左右モータ個体差補正_H
#define 走行体制御_P_W_M左右モータ個体差補正_H

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

#include "ハード/モータ.h"
#include "ハード/センサ管理.h"
#include "走行体制御/PWM電圧補正.h"

namespace 走行体制御
{
class PWM左右モータ個体差補正
{
private:
	PWM電圧補正 pWM電圧補正;
	PWM電圧補正 左右モータPWM電圧補正[2];
	ハード::モータ 左モータ;
	ハード::センサ管理 センサ管理;
	PWM電圧補正 右PWM電圧補正;

public:
	void 左右モータの個体差を補正してPWM値を渡す(int 補正前左モータPWM値, int 補正前右モータPWM値);

};

}  // namespace 走行体制御
#endif
