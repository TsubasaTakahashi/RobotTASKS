#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

#include "SectionManager.h"

#define FIRST_SECTION 0      //最初の区間
#define LAST_SECTION 1       //最後の区間

//区間情報の中身
#define FORWARD_AT_SI 0               //フォワード値
#define TAIL_ANGLE_AT_SI 1            //尻尾の角度
#define BALANCE_AT_SI 2               //姿勢
#define USED_SENSOR_AT_SI 3           //使用する検知
#define SENSOR_THRESHOLD_AT_SI 4      //検査の閾値

namespace Scenario
{

//区間情報を得る



/*
*メソッド：int JudgeSectionTransition()
*　　区間遷移判定を行う。
*　　区間情報クラス"SectionInfo"より得た「使用する検知」と「検知の閾値」を用いる。
*　　「使用する検知」を「検知の閾値」を引数に検知管理クラス"DetectionManager"より
*　　呼び出して、TRUEが返ってきたら次の区間へ遷移する。
*/

int SectionManager::JudgeSectionTransition()    //区間遷移判定をする
{
	//今が最後の区間でなく
	//「使用する検知」をもとに呼び出した「検知」がTRUEを返したら（遷移判定）
	//「次の区間へ遷移する」を返す。
	//それ以外なら何もしない。
	return 0;
}

/*
*メソッド：void ChengeSectionRunning()
*　　区間に応じた走行をする。
*　　区間情報クラス"SectionInfo"より得た「フォワード値」、「尻尾の角度」、「姿勢」を
*　　引数に走行制御クラス"RobotController"を呼び出す。
*/

void SectionManager::ChengeSectionRunning()    //区間に応じた走行をする
{
	//「現在の区間情報」に対応して
	//「フォワード値」、「尻尾の角度」、「姿勢」を
}
}  // namespace Scenario
