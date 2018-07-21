#ifndef ハード_モータ_H
#define ハード_モータ_H

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

#include "走行体制御/const int.h"
#include "走行体制御/PWM左右モータ個体差補正.h"
#include "走行体制御/PWM電圧補正.h"

namespace ハード
{
class モータ
{
private:
	走行体制御::const int PWM値の上限値;

	走行体制御::const int PWM値の下限値;

	走行体制御::PWM左右モータ個体差補正 pWM左右モータ個体差補正;
	走行体制御::PWM左右モータ個体差補正 pWM左右モータ個体差補正;
	モータ モータ;
	走行体制御::PWM電圧補正 PWM取得;

public:
	void モータのPWM値を設定する(int PWM値);

};

}  // namespace ハード
#endif
