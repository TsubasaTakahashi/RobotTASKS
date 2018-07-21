#ifndef ハード_ジャイロセンサ_H
#define ハード_ジャイロセンサ_H

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

#include "ハード/センサ管理.h"

namespace ハード
{
class ジャイロセンサ : public センサ管理
{
public:
	int センサ値を取得する();

};

}  // namespace ハード
#endif
