#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

#include "PidController.h"

namespace RobotControl
{

	PidController::PidController(double Pparameter,
												 			double Iparameter,
												 			double Dparameter,
												 			double PidGain,
												 			double PidOffset)
	:
	mPparameter(Pparameter),
	mIparameter(Iparameter),
	mDparameter(Dparameter),
	mPidGain(PidGain),
	mPidOffset(PidOffset)
	{
	}

	int PidController::CalcControlVal(int iCurrentVal, int iTargetVal)
	{
		/* PID制御からPWM値を求める */
		double dbCorrectVal = 0.0;
		int iCorrectVal = 0;

		static double dbRefIntegral = 0.0;
		double dbRefP = 0.0;
		double dbRefI = 0.0;
		double dbRefD = 0.0;

	  mBeforeLastDiffVal = mLastDiffVal; /* 過去の反射光値の取得 */

	  mLastDiffVal = iCurrentVal - iTargetVal; /* 現在の反射光値の取得 */

	  dbRefIntegral += ((mBeforeLastDiffVal + mLastDiffVal) / 2.0) * mDeltaT; /* 積分値の取得 */

	  dbRefP = mPparameter * mLastDiffVal; /* p制御値の取得 */

	  dbRefI = mIparameter * dbRefIntegral; /* i制御値の取得 */

	  dbRefD = mDparameter * ((mBeforeLastDiffVal - mLastDiffVal) / mDeltaT); /* d制御値の取得 */

	  dbCorrectVal = dbRefP + dbRefI + dbRefD;

	  iCorrectVal = (int)(mPidGain * (dbCorrectVal) + mPidOffset);

		return iCorrectVal;

	}
}  // namespace 走行体制御
