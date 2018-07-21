#ifndef 検知_距離検知_H
#define 検知_距離検知_H

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

#include "ハード/モータ.h"
#include "ハード/センサ管理.h"
#include "検知/検知管理.h"

namespace 検知
{
class 距離検知 : public 検知管理
{
private:
	int 検知開始時の左モータの回転角度;

	int 検知開始時の右モータの回転角度;

	ハード::モータ モータ;
	ハード::センサ管理 モータセンサ;

private:
	void 進んだ距離を計算する();

public:
	boolean 検知する(int 閾値, int 右モータの回転角度, int 左モータの回転角度);

	void 属性値を初期化する();

};

}  // namespace 検知
#endif
