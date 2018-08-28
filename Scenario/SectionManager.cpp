#include "SectionManager.h"

namespace Scenario
{

//区間情報を得る

	SectionManager::SectionManager(
		SectionInfo* sectionInfo,   //現在の区間情報
		RobotControl::RobotController* robotCtrl,
		Detection::DetectionManager* detManager
	):mSectionStatus(0),
	mSectionInfo(sectionInfo),
	mRobotCtrller(robotCtrl),
	mDetManager(detManager)
	{

	}

	/*
	*メソッド：int JudgeSectionTransition()
	*　　区間遷移判定を行う。
	*　　区間情報クラス"SectionInfo"より得た「使用する検知」と「検知の閾値」を用いる。
	*　　「使用する検知」を「検知の閾値」を引数に検知管理クラス"DetectionManager"より
	*　　呼び出して、TRUEが返ってきたら次の区間へ遷移する。
	*/

	void SectionManager::JudgeSectionTransition(int detType, int detThreshold)    //区間遷移判定をする
	{
		//今が最後の区間でなく
		//「使用する検知」をもとに呼び出した「検知」がTRUEを返したら（遷移判定）
		//「次の区間へ遷移する」を返す。
		//それ以外なら何もしない。
		if(detType == IMPACT_DET){
			bool sectionTransition[2] = {false};

			mDetManager -> StepDetect(sectionTransition, detThreshold);

			if((sectionTransition[0] == true) && (sectionTransition[1] == true)){ //検知がされた場合区間を遷移させる
				mSectionStatus++;
			}
		}
		else
		{
			bool sectionTransition = false; //シナリオ遷移判定

			if(detType == DISTANCE_DET){
				sectionTransition = mDetManager -> DistanceDetect(detThreshold);
			}
			else
			if(detType == GRAY_DET){
				sectionTransition = mDetManager -> GrayDetect(detThreshold);
			}
			else
			if(detType == IMPACT_DET){
				sectionTransition = mDetManager -> ImpactDetect(detThreshold);
			}


			if(sectionTransition == true){ //検知がされた場合区間を遷移させる
				mSectionStatus++;
			}
		}
	}

	/*
	*メソッド：void ChengeSectionRunning()
	*　　区間に応じた走行をする。
	*　　区間情報クラス"SectionInfo"より得た「フォワード値」、「尻尾の角度」、「姿勢」を
	*　　引数に走行制御クラス"RobotController"を呼び出す。
	*/

	void SectionManager::Run()    //区間に応じた走行をする
	{
		//「現在の区間情報」に対応して
		//「フォワード値」、「尻尾の角度」、「姿勢」を
		int* sectionVal; //区間情報の属性値を格納する
		int foward = 0;               //フォワード値
		int tailAngle = 0;           //尻尾の角度
		int balance = 0;               //姿勢
		int detection = 0;           //使用する検知
		int detectionThreshold = 0;      //検査の閾値
		int originalVal = 0; //ライントレース走行区間: 反射光の閾値, 指定値走行区間: ターン値

		sectionVal = (int* )malloc(sizeof(int) * SEC_ATRB_VAL);

		mSectionInfo[mSectionStatus].GetRobotAttributeValue(sectionVal); //区間情報から属性値を取得する

		foward = sectionVal[FORWARD_AT_SI];
		tailAngle = sectionVal[TAIL_ANGLE_AT_SI];
		balance = sectionVal[BALANCE_AT_SI];
		detection = sectionVal[USED_SENSOR_AT_SI];
		detectionThreshold = sectionVal[SENSOR_THRESHOLD_AT_SI];
		originalVal = sectionVal[ORIGINAL_VAL];

		SectionManager::JudgeSectionTransition(detection, detectionThreshold);

		if(typeid(mSectionInfo[mSectionStatus]) == typeid(SectionLineTracer)){
			mRobotCtrller -> RunLineTracer(foward, originalVal, tailAngle, balance);
		}
		else if(typeid(mSectionInfo[mSectionStatus]) == typeid(SectionScenarioTracer)){
			mRobotCtrller -> RunSpecifiedVal(foward, originalVal, tailAngle, balance);
		}

		mDbg[0] = foward;
		mDbg[1] = tailAngle;
		mDbg[2] = balance;
		mDbg[3] = detection;
		mDbg[4] = detectionThreshold;
		mDbg[5] = originalVal;

		free(sectionVal);

	}
}  // namespace Scenario
