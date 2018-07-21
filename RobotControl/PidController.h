#ifndef 走行体制御_P_I_D制御_H
#define 走行体制御_P_I_D制御_H

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

#include "ハード/ジャイロセンサ.h"

namespace 走行体制御
{
class PID制御
{
private:
	double Pパラメータ;

	double Iパラメータ;

	double Dパラメータ;

	int 前回の値;

	int 前々回の値;

	int 累積値;

	ハード::ジャイロセンサ ジャイロセンサ;

public:
	int 制御量を計算する(int 現在の値, int 目標値);

};

}  // namespace 走行体制御
#endif
