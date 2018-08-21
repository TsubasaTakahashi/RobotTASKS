#ifndef Scenario_SectionManager_H
#define Scenario_SectionManager_H

#include "RobotController.h"    //"走行体制御/走行制御.h"
#include "DetectionManager.h"   //検知管理

namespace Scenario
{
class SectionManager
{
	//コンストラクタ
public:
	explicit SectionManager(
		SectionInfo* sectionInfo,   //現在の区間情報
		RobotController* detManager,
		DetectionManager* robotCtrl
	);

~SectionManager(void)          //デストラクタ

private:
	int mSectionStatus;                          //区間状態
	SectionInfo* mSectionInfo[NUMBER_OF_DATA];   //現在の区間情報

	走行体制御::走行制御 走行制御;

	int numberOfData;


private:
	int JudgeSectionTransition();    //区間遷移判定をする

public:
	void ChengeSectionRunning();     //区間に応じた走行をする

};

}  // namespace シナリオ
#endif
