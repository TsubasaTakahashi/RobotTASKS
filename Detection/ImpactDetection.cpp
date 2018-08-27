/****************************/
/*	概要：衝撃検知クラス	*/
/*	作成者：島川			*/
/*	作成日：2018/08/25		*/
/*	修正日：2018/08/25		*/
/****************************/
#include "ImpactDetection.h"

namespace Detection
{
	/************************/
	/*	カウントする		*/
	/*	引数：				*/
	/*		Threshold：閾値	*/
	/************************/
	int ImpactDetection::Count(const int &Threshold)
	{
		int iCounter = iDefalutCounterValue;

		for (const auto &i : iaRobotAngularVelocity) {
			if (i <= (Threshold - iWidth)				/*	取得した走行体の角速度が	*/
				|| (i >= (Threshold + iWidth))) {		/*	閾値の範囲内ならば、		*/
				iCounter++;								/*	カウントアップする。		*/
			}
		}

		return iCounter;
	}

	/****************************/
	/*	コンストラクタ			*/
	/*	引数：					*/
	/*		Duration：持続時間	*/
	/*		Width：閾値の幅		*/
	/****************************/
	ImpactDetection::ImpactDetection(const int &Duration, const int &Width)
	{
		iImpactDetectionDuration = Duration;
		iWidth = Width;
	}

	/********************/
	/*	デストラクタ	*/
	/********************/
	ImpactDetection::~ImpactDetection(void)
	{
		iaRobotAngularVelocity.~vector();
	}

	/****************************************************************************/
	/*	検知する																*/
	/*	判定法：																*/
	/*		・取得した走行体の角速度を指定したサンプル点数だけ格納していく。	*/
	/*		・走行体の角速度は順次更新されていく。								*/
	/*		・取得した走行体の角速度が閾値の範囲外になった点数をカウントする。	*/
	/*		・カウントが持続時間以上になったらtrueを返す。						*/
	/*	引数：																	*/
	/*		Threshold：衝撃検知の閾値											*/
	/*		SampleNumber：サンプル点数											*/
	/*		RobotAngularVelocity：取得した走行体の角速度						*/
	/****************************************************************************/
	bool ImpactDetection::Detect(const int &Threshold, const unsigned int &SampleNumber, const int &RobotAngularVelocity)
	{
		uiSampleNumber = SampleNumber;

		/*	走行体の角速度を配列に格納していく	*/
		if (iaRobotAngularVelocity.size() < uiSampleNumber) {
			iaRobotAngularVelocity.push_back(RobotAngularVelocity);
		}

		/*	走行体の角速度を更新していく	*/
		else if (iaRobotAngularVelocity.size() == uiSampleNumber) {
			iaRobotAngularVelocity.erase(iaRobotAngularVelocity.begin());
			iaRobotAngularVelocity.push_back(RobotAngularVelocity);
		}

		/*	衝撃検知を行う	*/
		if (iaRobotAngularVelocity.size() == uiSampleNumber) {
			if (Count(Threshold) >= iImpactDetectionDuration) {
				return true;
			}
		}

		return false;
	}
}
