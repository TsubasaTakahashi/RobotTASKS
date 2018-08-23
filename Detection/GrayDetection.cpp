/****************************/
/*	概要：灰色検知クラス	*/
/*	作成者：島川			*/
/*	作成日：2018/08/14		*/
/*	修正日：2018/08/16		*/
/****************************/
#include "GrayDetection.h"

namespace Detection
{
	/********************************/
	/*	反射光の平均値を計算する	*/
	/********************************/
	int GrayDetection::CalculateAverage(void)
	{
		/*	反射光の平均値を計算する	*/
		for (const auto &i : iaReflectLight) {
			iAverage = iAverage + i;
		}
		iAverage = iAverage / iSampleNumber;

		return iAverage;
	}

	/****************************************************/
	/*	反射光の平均値が閾値内にあるかをカウントする	*/
	/****************************************************/
	int GrayDetection::Count(const int &iGrayDetectionThreshold)
	{
		int iAverage = CalculateAverage();
		static int iCounter = iDefalutCounterValue;		/*	カウンター	*/

		if ((iAverage >= (iGrayDetectionThreshold - iWidth))		/*	反射光の平均値が、	*/
			&& (iAverage <= (iGrayDetectionThreshold + iWidth))) {	/*	閾値の範囲内なら、	*/
			iCounter++;												/*	カウントする。		*/
		}

		else {														/*	そうでないなら、		*/
			iCounter = iDefalutCounterValue;						/*	カウントを初期値に戻す	*/
		}

		return iCounter;
	}

	/********************************************************************/
	/*	灰色検知をする(その1)											*/
	/*	判定法：														*/
	/*		・取得した反射光が指定した個数格納されたらカウントをする。	*/
	/*		・反射光は順次更新されていく。								*/
	/*		・カウントが持続時間以上になったらtrueを返す。				*/
	/*	引数：															*/
	/*		iGrayDetectionThreshold：灰色検知の閾値						*/
	/*		iReflectLight：取得した反射光								*/
	/********************************************************************/
	bool GrayDetection::Detect(const int &iGrayDetectionThreshold, int &iReflectLight)
	{
		/*	反射光を配列に格納していく	*/
		if (iaReflectLight.size() < iSampleNumber) {
			iaReflectLight.push_back(iReflectLight);
		}

		/*	反射光を更新していく	*/
		else if (iaReflectLight.size() == iSampleNumber) {
			iaReflectLight.erase(iaReflectLight.begin());
			iaReflectLight.push_back(iReflectLight);
		}

		/*	灰色検知を行う	*/
		if (iaReflectLight.size() == iSampleNumber) {
			if (Count(iGrayDetectionThreshold) == iGrayDetectionDuration) {
				return true;
			}
		}

		return false;
	}

	/************************************************************/
	/*	灰色検知をする(その2)									*/
	/*	判定法：												*/
	/*		・取得した反射光が閾値内ならカウントアップする。	*/
	/*		・閾値外ならカウントを0にする。						*/
	/*		・カウントが持続時間以上になったらtrueを返す。		*/
	/*	引数：													*/
	/*		iGrayDetectionThreshold：灰色検知の閾値				*/
	/*		iReflectLight：取得した反射光						*/
	/************************************************************/
	bool GrayDetection::Detect2(const int &iGrayDetectionThreshold, int &iReflectLight)
	{
		static int iCounter = iDefalutCounterValue;

		if (iReflectLight <= (iGrayDetectionThreshold + iWidth)
			&& (iReflectLight >= (iGrayDetectionThreshold - iWidth))) {
			iCounter++;
		}
		else {
			iCounter = iDefalutCounterValue;
		}

		if (iCounter >= iGrayDetectionDuration) {
			return true;
		}

		return false;
	}
}
