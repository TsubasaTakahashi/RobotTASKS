/****************************/
/*	概要：灰色検知クラス	*/
/*	作成者：島川			*/
/*	作成日：2018/08/14		*/
/*	修正日：2018/08/25		*/
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
		iAverage = iAverage / uiSampleNumber;

		return iAverage;
	}

	/****************************************************/
	/*	反射光の平均値が閾値内にあるかをカウントする	*/
	/*	引数：											*/
	/*		Threshold：灰色検知の閾値					*/
	/****************************************************/
	int GrayDetection::Count(const int &Threshold)
	{
		int iAverage = CalculateAverage();
		static int iCounter = iDefalutCounterValue;

		if ((iAverage <= (Threshold + iWidth))			/*	反射光の平均値が、	*/
			&& (iAverage >= (Threshold - iWidth))) {	/*	閾値の範囲内なら、	*/
			iCounter++;									/*	カウントする。		*/
		}
		else {											/*	そうでないなら、			*/
			iCounter = iDefalutCounterValue;			/*	カウントを初期値に戻す。	*/
		}

		return iCounter;
	}

	/****************************************/
	/*	コンストラクタ						*/
	/*	引数：								*/
	/*		Duration：灰色検知の持続時間	*/
	/*		Width：閾値の幅					*/
	/****************************************/
	GrayDetection::GrayDetection(const int &Duration, const int &Width)
	{
		iGrayDetectionDuration = Duration;
		iWidth = Width;
	}

	/********************************************************************/
	/*	検知する(その1)													*/
	/*	判定法：														*/
	/*		・取得した反射光が指定した個数格納されたらカウントをする。	*/
	/*		・反射光は順次更新されていく。								*/
	/*		・カウントが持続時間以上になったらtrueを返す。				*/
	/*	引数：															*/
	/*		Threshold：灰色検知の閾値									*/
	/*		ReflectLight：取得した反射光								*/
	/********************************************************************/
	bool GrayDetection::Detect2(const int &Threshold, const unsigned int &SampleNumber, const int &ReflectLight)
	{
		uiSampleNumber = SampleNumber;

		/*	反射光を配列に格納していく	*/
		if (iaReflectLight.size() < uiSampleNumber) {
			iaReflectLight.push_back(ReflectLight);
		}

		/*	反射光を更新していく	*/
		else if (iaReflectLight.size() == uiSampleNumber) {
			iaReflectLight.erase(iaReflectLight.begin());
			iaReflectLight.push_back(ReflectLight);
		}

		/*	灰色検知を行う	*/
		if (iaReflectLight.size() == uiSampleNumber) {
			if (Count(Threshold) >= iGrayDetectionDuration) {
				return true;
			}
		}

		return false;
	}

	/************************************************************/
	/*	検知する(その2)											*/
	/*	判定法：												*/
	/*		・取得した反射光が閾値内ならカウントアップする。	*/
	/*		・閾値外ならカウントを0にする。						*/
	/*		・カウントが持続時間以上になったらtrueを返す。		*/
	/*	引数：													*/
	/*		Threshold：灰色検知の閾値							*/
	/*		ReflectLight：取得した反射光						*/
	/************************************************************/
	bool GrayDetection::Detect(const int &Threshold, const int &ReflectLight)
	{
		static int iCounter = iDefalutCounterValue;

		if (ReflectLight <= (Threshold + iWidth)	/*	取得した反射光値が		*/
			&& (ReflectLight >= (Threshold))) {		/*	閾値の範囲内ならば、	*/
			iCounter++;								/*	カウントアップする。	*/
		}
		else {										/*	閾値の範囲外なら、	*/
			iCounter = iDefalutCounterValue;		/*	カウントを0に戻す。	*/
		}

		if (iCounter >= iGrayDetectionDuration) {	/*	カウントが持続時間以上になれば、	*/
			return true;							/*	trueを返す。						*/
		}

		return false;
	}
}
