#ifndef RobotControl_PidController_H
#define RobotControl_PidController_H

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

namespace RobotControl
{
class PidController
{
	public:
		explicit PidController(double Pparameter,
													 double Iparameter,
												   double Dparameter,
												   double PidGain,
												   double PidOffset);

	private:
		double mPparameter;
		double mIparameter;
		double mDparameter;

		int mLastDiffVal;
		int mBeforeLastDiffVal;
		int mCumulativeSum;

		double mPidGain; /* PID調整用のゲイン */
		double mPidOffset; /* PID調整用のオフセット */
		const double mDeltaT = 0.004; /* ループタスクの1回の処理時間 */

	public:
		int CalcControlVal(int iCurrentVal, int iTargetVal);
};

}  // namespace 走行体制御
#endif
