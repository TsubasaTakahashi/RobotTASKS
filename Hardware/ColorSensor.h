#ifndef ハード_カラーセンサ_H
#define ハード_カラーセンサ_H

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

#include "ハード/センサ管理.h"

namespace ハード
{
class カラーセンサ : public センサ管理
{
private:
	カラーセンサ カラーセンサ;

public:
	int センサ値を取得する();

};

}  // namespace ハード
#endif
