#include "PidController.h"

namespace RobotControl
{

	PidController::PidController(double pParameter,
												 			double iParameter,
												 			double dParameter,
												 			double pidGain,
												 			double pidOffset,
														  double deltaT)
	:
				mPparameter(pParameter),
				mIparameter(iParameter),
				mDparameter(dParameter),
				mPidGain(pidGain),
				mPidOffset(pidOffset),
				mDeltaT(deltaT)
				{
				}

	int PidController::CalcControlVal(int iCurrentVal, int iTargetVal)
	{
		/* PID制御からPWM値を求める */
		double dbCorrectVal = 0.0;
		int iCorrectVal = 0;

		double dbRefP = 0.0;
		double dbRefI = 0.0;
		double dbRefD = 0.0;

	  mBeforeLastDiffVal = mLastDiffVal; /* 過去の反射光値の取得 */

	  mLastDiffVal = iCurrentVal - iTargetVal; /* 現在の反射光値の取得 */

	  mCumulativeSum += ((mBeforeLastDiffVal + mLastDiffVal) / 2.0) * mDeltaT; /* 積分値の取得 */

	  dbRefP = mPparameter * mLastDiffVal; /* p制御値の取得 */

	  dbRefI = mIparameter * mCumulativeSum; /* i制御値の取得 */

	  dbRefD = mDparameter * ((mBeforeLastDiffVal - mLastDiffVal) / mDeltaT); /* d制御値の取得 */

	  dbCorrectVal = dbRefP + dbRefI + dbRefD;

	  iCorrectVal = (int)(mPidGain * (dbCorrectVal) + mPidOffset);

		return iCorrectVal;

	}
}  // namespace 走行体制御
