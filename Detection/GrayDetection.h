/****************************/
/*	概要：灰色検知クラス	*/
/*	作成者：島川			*/
/*	作成日：2018/08/14		*/
/*	修正日：2018/08/25		*/
/****************************/
#pragma once
#include <vector>

using namespace std;

namespace Detection
{
	class GrayDetection
	{
	private:
		int iGrayDetectionDuration;			/*	灰色検知の持続時間	*/
		int iWidth;							/*	灰色検知の閾値の幅	*/
		vector<int> iaReflectLight;			/*	今までの反射光		*/
		const int iDefalutCounterValue = 0;	/*	カウンターの初期値	*/
		unsigned int uiSampleNumber;		/*	サンプル点数		*/
		int iAverage = 0;					/*	平均値				*/

		int CalculateAverage(void);			/*	平均値を計算する	*/
		int Count(const int &Threshold);	/*	カウントする		*/

	public:
		GrayDetection(const int &Duration, const int &Width);											/*	コンストラクタ	*/
		bool Detect(const int &Threshold, const unsigned int &SampleNumber, const int &ReflectLight);	/*	検知する(その1)	*/
		bool Detect2(const int &Threshold, const int &ReflectLight);									/*	検知する(その2)	*/
	};
}  /* namespace DETECTION	*/
