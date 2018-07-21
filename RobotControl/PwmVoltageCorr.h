#ifndef 走行体制御_P_W_M電圧補正_H
#define 走行体制御_P_W_M電圧補正_H

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

#include "ハード/モータ.h"
#include "ハード/バッテリセンサ.h"
#include "ハード/センサ管理.h"
#include "走行体制御/const int.h"

namespace 走行体制御
{
class PWM電圧補正
{
private:
	const int 基準電圧;

	ハード::モータ モータ;
	ハード::バッテリセンサ バッテリセンサ;
	ハード::モータ モータ[3];
	ハード::モータ 右モータ;
	ハード::モータ 尻尾モータ;
	ハード::センサ管理 センサ管理;

public:
	void PWM値を補正して渡す(int 補正前PWM値);

};

}  // namespace 走行体制御
#endif
