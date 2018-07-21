#ifndef 検知_灰色検知_H
#define 検知_灰色検知_H

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

#include "ハード/カラーセンサ.h"
#include "ハード/センサ管理.h"
#include "検知/検知管理.h"

namespace 検知
{
class 灰色検知 : public 検知管理
{
private:
	int 反射光[];

	ハード::カラーセンサ カラーセンサ;
	ハード::カラーセンサ カラーセンサ;
	ハード::センサ管理 センサ管理;

public:
	boolean 検知する(int 閾値, int 反射光);

	void 属性値を初期化する();

};

}  // namespace 検知
#endif
