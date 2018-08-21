#ifndef Scenario_SectionManager_H
#define Scenario_SectionManager_H

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

#include "RobotController.h"    //"走行体制御/走行制御.h"
#include "DetectionManager.h"   //検知管理

#define NUMBER_OF_DATA 5       //区間数（TBD）

namespace Scenario
{
class SectionManager
{
	//コンストラクタ
public:
	explicit SectionManager(
		int mSectionStatus,                         //区間状態
		SectionInfo* mSectionInfo[NUMBER_OF_DATA]   //現在の区間情報
	);

~SectionManager(void)          //デストラクタ

private:
	int mSectionStatus;                          //区間状態
	SectionInfo* mSectionInfo[NUMBER_OF_DATA];   //現在の区間情報

  //いらない？↓
	//検知::衝撃検知 衝撃検知;
	//検知::距離検知 距離検知;
	//検知::灰色検知 灰色検知;
	//検知::段差検知 段差検知;
	//走行体制御::走行制御 走行制御;
	//検知::検知管理 検知管理;

private:
	int JudgeSectionTransition();    //区間遷移判定をする

public:
	void ChengeSectionRunning();     //区間に応じた走行をする

};

}  // namespace シナリオ
#endif
