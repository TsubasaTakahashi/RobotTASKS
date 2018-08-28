#ifndef Scenario_SectionManager_H
#define Scenario_SectionManager_H

#define FIRST_SECTION 0      //最初の区間
#define LAST_SECTION 1       //最後の区間

//区間情報の中身
#define FORWARD_AT_SI 0               //フォワード値
#define TAIL_ANGLE_AT_SI 1            //尻尾の角度
#define BALANCE_AT_SI 2               //姿勢
#define USED_SENSOR_AT_SI 3           //使用する検知
#define SENSOR_THRESHOLD_AT_SI 4      //検査の閾値
#define ORIGINAL_VAL 5								//ライントレース走行区間、指定値走行区間の独自の属性値

//検知の対応
#define DISTANCE_DET 0
#define GRAY_DET 1
#define IMPACT_DET 2
#define STEP_DET 3

//属性値の数を規定
#define SEC_ATRB_VAL 6 //走行区間の属性値の数

#include <typeinfo>
#include "RobotController.h"    //"走行体制御/走行制御.h"
#include "DetectionManager.h"   //検知管理
#include "SectionInfo.h" //区間情報
#include "SectionLineTracer.h" //ライントレース走行区間
#include "SectionScenarioTracer.h" //指定値走行区間
#include <stdlib.h>

namespace Scenario
{
class SectionManager
{
	//コンストラクタ
public:
	explicit SectionManager(
		SectionInfo* sectionInfo,   //現在の区間情報
		RobotControl::RobotController* robotCtrl,
		Detection::DetectionManager* detManager
	);

	int mDbg[6];

private:
	int mSectionStatus;          //区間状態
	SectionInfo* mSectionInfo;   //現在の区間情報
	RobotControl::RobotController* mRobotCtrller;
	Detection::DetectionManager* mDetManager;


private:
	void JudgeSectionTransition(int detType, int detThreshold);    //区間遷移判定をする

public:
	void Run();     //区間に応じた走行をする

};

}  // namespace シナリオ
#endif
