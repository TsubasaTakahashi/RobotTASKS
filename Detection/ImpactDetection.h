/****************************/
/*	概要：衝撃検知クラス	*/
/*	作成者：島川			*/
/*	作成日：2018/08/25		*/
/*	修正日：2018/08/25		*/
/****************************/
#pragma once
#include <vector>

using namespace std;

#ifndef Detection_ImpactDetection_H
#define Detection_ImpactDetection_H

namespace Detection
{
	class ImpactDetection
	{
		private:
			int iImpactDetectionDuration;		/*	衝撃検知の持続時間		*/
			int iWidth;							/*	衝撃検知の閾値の幅		*/
			vector<int> iaRobotAngularVelocity;	/*	今までの走行体の角速度	*/
			const int iDefalutCounterValue = 0;	/*	カウンターの初期値	*/
			unsigned int uiSampleNumber;		/*	サンプル点数			*/

			int Count(const int &Threshold);	/*	カウントする	*/

		public:
			int iCount;	/*	ログ用のカウント値	*/

			ImpactDetection(const int &Duration, const int &Width);													/*	コンストラクタ	*/
			~ImpactDetection(void);																					/*	デストラクタ	*/
			bool Detect(const int &Threshold, const unsigned int &SampleNumber, const int &RobotAngularVelocity);	/*	検知する		*/
	};
}  /* namespace DETECTION	*/
#endif
