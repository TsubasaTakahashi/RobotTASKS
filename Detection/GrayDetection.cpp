/****************************/
/*	概要：灰色検知クラス	*/
/*	作成者：島川			*/
/*	作成日：2018/08/14		*/
/*	修正日：2018/08/25		*/
/****************************/
#pragma once
#include "GrayDetection.h"

namespace DETECTION
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
	/****************************************************/
	int GrayDetection::Count(const int &iGrayDetectionThreshold)
	{
		int iAverage = CalculateAverage();
		static int iCounter = iDefalutCounterValue;

		if ((iAverage >= (iGrayDetectionThreshold - iWidth))		/*	反射光の平均値が、	*/
			&& (iAverage <= (iGrayDetectionThreshold + iWidth))) {	/*	閾値の範囲内なら、	*/
			iCounter++;												/*	カウントする。		*/
		}
		else {														/*	そうでないなら、		*/
			iCounter = iDefalutCounterValue;						/*	カウントを初期値に戻す	*/
		}

		return iCounter;
	}

	/********************/
	/*	コンストラクタ	*/
	/********************/
	GrayDetection::GrayDetection(const int &Duration, const int &Width)
	{
		iGrayDetectionDuration = Duration;
		iWidth = Width;
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
	bool GrayDetection::DetectGrayLine(const int &Threshold, const unsigned int &SampleNumber, int &ReflectLight)
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
			if (Count(Threshold) == iGrayDetectionDuration) {
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
	/*		Threshold：灰色検知の閾値							*/
	/*		ReflectLight：取得した反射光						*/
	/************************************************************/
	bool GrayDetection::DetectGrayLine2(const int &Threshold, const int &ReflectLight)
	{
		static int iCounter = iDefalutCounterValue;

		if (ReflectLight <= (Threshold + iWidth)
			&& (ReflectLight >= (Threshold - iWidth))) {
			iCounter++;
		}
		else {
			iCounter = iDefalutCounterValue;
		}
		iCount = iCounter;

		if (iCounter >= iGrayDetectionDuration) {
			return true;
		}

		return false;
	}
}
