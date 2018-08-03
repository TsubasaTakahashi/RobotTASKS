#ifndef シナリオ_シナリオ_H
#define シナリオ_シナリオ_H

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

#include "走行体制御/走行制御.h"
#include "検知/衝撃検知.h"
#include "検知/距離検知.h"
#include "検知/灰色検知.h"
#include "検知/段差検知.h"
#include "検知/検知管理.h"

namespace シナリオ
{
class シナリオ
{
private:
	int シナリオ状態;

	検知::衝撃検知 衝撃検知;
	検知::距離検知 距離検知;
	検知::灰色検知 灰色検知;
	検知::段差検知 段差検知;
	走行体制御::走行制御 走行制御;
	検知::検知管理 検知管理;

private:
	int シナリオ遷移判定をする();

public:
	void シナリオを選択する();

};

}  // namespace シナリオ
#endif
