#ifndef 走行体制御_ライントレース制御_H
#define 走行体制御_ライントレース制御_H

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

#include "ハード/カラーセンサ.h"
#include "ハード/センサ管理.h"
#include "走行体制御/走行制御.h"
#include "走行体制御/PID制御.h"

namespace 走行体制御
{
class ライントレース制御
{
private:
	走行制御 走行制御;
	ハード::カラーセンサ 反射光取得;
	PID制御 走行PID制御;
	ハード::カラーセンサ カラーセンサ;
	ハード::センサ管理 センサ管理;
	ライントレース制御 ライントレース制御;

public:
	int ターン値を調整する(int 反射光の閾値);

};

}  // namespace 走行体制御
#endif
