#ifndef 検知_検知管理_H
#define 検知_検知管理_H

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

#include "ハード/センサ管理.h"
#include "ハード/モータ.h"
#include "走行体制御/姿勢制御.h"
#include "検知/距離検知.h"
#include "検知/灰色検知.h"
#include "検知/段差検知.h"
#include "検知/衝撃検知.h"

namespace 検知
{
class 検知管理 : public ハード::センサ管理, public 走行体制御::姿勢制御
{
private:
	ハード::センサ管理 センサ管理[];
	ハード::モータ 右モータ;
	ハード::モータ 左モータ;
	距離検知 距離検知;
	灰色検知 灰色検知;
	検知管理 検知管理;
	段差検知 段差検知;
	衝撃検知 衝撃検知;
	ハード::センサ管理 センサ管理;

public:
	boolean 灰色検知する(int 閾値);

	boolean 段差検知する(int 閾値);

	boolean 距離検知する(int 閾値);

	boolean 衝撃検知する(int 閾値);

	void 属性値を初期化する();

};

}  // namespace 検知
#endif
