#ifndef ハード_バッテリセンサ_H
#define ハード_バッテリセンサ_H

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

#include "ハード/モータ.h"
#include "ハード/センサ管理.h"
#include "走行体制御/PWM電圧補正.h"

namespace ハード
{
class バッテリセンサ : public モータ, public センサ管理
{
private:
	走行体制御::PWM電圧補正 pWM電圧補正;

public:
	int センサ値を取得する();

};

}  // namespace ハード
#endif
