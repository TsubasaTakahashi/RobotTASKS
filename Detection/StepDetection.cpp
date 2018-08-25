#include "StepDetection.h"

namespace Detection
{
	StepDetection(int actDuration)
			:mActDuration(actDuration)
			{

			}

	void StepDetection::CountActNum(int* wheelStopCount, int threshold, int lWheelMotorRa, int rWheelMotorRa)
	{
		int absDiffWheelAngL = 0;
		int absDiffWheelAngR = 0;

		/* 過去と現在のモータの回転数の取得 */
		mMotorAngL[1] = mMotorAngL[0]; /* 過去のモータの回転数の取得 */
		mMotorAngR[1] = mMotorAngR[0];

		mMotorAngL[0] = lWheelMotorRa; /* 現在のモータの回転数の取得 */
		mMotorAngR[0] = rWheelMotorRa;

		absDiffWheelAngL = abs(mMotorAngL[1] - mMotorAngL[0]);
		absDiffWheelAngR = abs(mMotorAngR[1] - mMotorAngR[0]);

		/* 現在の値と過去の値の差の絶対値がスレッショルド以下なら、カウンタを1増やす */
		if(absDiffWheelAngL <= threshold) {
			wheelStopCount[0]++;
		}
		else {
			wheelStopCount[0] = 0;
		}

		if(absDiffWheelAngR <= threshold) {
			wheelStopCount[1]++;
		}
		else {
			wheelStopCount[1] = 0;
		}
	}

	void StepDetection::Detect(bool* detection, int threshold, int lWheelMotorRa, int rWheelMotorRa)
	{
		//属性値を初期化する
		if((detection[0] == true) && (detection[1] == true)){
			mMotorAngL[0] = 0;
			mMotorAngL[1] = 0;
			mWheelStopCount[0] = 0;
			mWheelStopCount[1] = 0;
		}

		CountActNum(mWheelStopCount, threshold, lWheelMotorRa, rWheelMotorRa);

		if(mWheelStopCount[0] == mActDuration) {
			detection[0] = true;
		}
		else{
			detection[0] = false;
		}

		if(mWheelStopCount[1] == mActDuration) {
			detection[1] = true;
		}
		else{
			detection[1] = false;
		}
	}
}  // namespace 検知
