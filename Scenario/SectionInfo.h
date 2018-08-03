#ifndef シナリオ_区間情報_H
#define シナリオ_区間情報_H

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

namespace シナリオ
{
class 区間情報
{
private:
	const int フォワード値;

	const int 尻尾の角度;

	int 姿勢;

	int 使用する検知;

	int 検査の閾値;

	区間情報 区間情報;
	区間情報 区間情報;

public:
	void 走行の属性値を取得する(int* 走行体の属性値);

};

}  // namespace シナリオ
#endif
