#ifndef ハード_センサ管理_H
#define ハード_センサ管理_H

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

#include "ハード/モータ.h"
#include "ハード/カラーセンサ.h"
#include "ハード/ジャイロセンサ.h"
#include "ハード/バッテリセンサ.h"
#include "ハード/モータ回転角度センサ.h"

namespace ハード
{
class センサ管理 : public モータ
{
private:
	カラーセンサ カラーセンサ;
	カラーセンサ カラーセンサ;
	ジャイロセンサ ジャイロセンサ;
	バッテリセンサ バッテリセンサ;
	モータ回転角度センサ モータ回転角度センサ[3];
	バッテリセンサ バッテリセンサ;
	センサ管理 センサ管理;

public:
	int 反射光を取得する();

	int 右モータの回転角度を取得する();

	int 左モータの回転角度を取得する();

	int 尻尾モータの回転角度を取得する();

	int 走行体の角速度を取得する();

	int バッテリの電圧を取得する();

};

}  // namespace ハード
#endif
