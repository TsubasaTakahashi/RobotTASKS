/************************************/
/*	概要：灰色検知クラスのヘッダ	*/
/*	作成者：島川					*/
/*	作成日：2018/08/14				*/
/*	修正日：2018/08/16				*/
/************************************/
#pragma once
#include <vector>

using namespace std;

namespace Detection
{
	class GrayDetection
	{
		private:
			vector<int> iaReflectLight;				/*	今までの反射光		*/
			const unsigned int iSampleNumber = 25;	/*	サンプル点数		*/
			const int iGrayDetectionDuration = 200;	/*	灰色検知の持続時間	*/
			const int iWidth = 15;					/*	灰色検知の閾値の幅	*/
			int iAverage = 0;						/*	平均値				*/
			const int iDefalutCounterValue = 0;		/*	カウンターの初期値	*/

			int CalculateAverage(void);							/*	平均値を計算する	*/
			int Count(const int &iGrayDetectionThreshold);		/*	カウントする		*/

		public:
			bool Detect(const int &iGrayDetectionThreshold, int &iReflectLight);	/*	灰色検知(その1)	*/
			bool Detect2(const int &iGrayDetectionThreshold, int &iReflectLight);	/*	灰色検知(その2)	*/
	};
}  /* namespace DETECTION	*/
