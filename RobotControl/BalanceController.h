#ifndef 走行体制御_姿勢制御_H
#define 走行体制御_姿勢制御_H

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

#include "ハード/ジャイロセンサ.h"
#include "ハード/センサ管理.h"
#include "ハード/モータ.h"
#include "走行体制御/PID制御.h"

namespace 走行体制御
{
class 姿勢制御
{
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
