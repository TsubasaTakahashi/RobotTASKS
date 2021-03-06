#ifndef RobotControl_PidController_H
#define RobotControl_PidController_H

namespace RobotControl
{
class PidController
{
	public:
		explicit PidController(double pParameter,
													 double iParameter,
												   double dParameter,
												   double pidGain,
												   double pidOffset,
												   double deltaT);

	private:
		double mPparameter;
		double mIparameter;
		double mDparameter;

		int mLastDiffVal;
		int mBeforeLastDiffVal;
		double mCumulativeSum;

		double mPidGain; /* PID調整用のゲイン */
		double mPidOffset; /* PID調整用のオフセット */
		double mDeltaT; /* ループタスクの1回の処理時間 */

	public:
		int CalcControlVal(int iCurrentVal, int iTargetVal);

		int mDbg_0;
		int mDbg_1;
		int mDbg_2;
		int mDbg_3;
		int mDbg_4;
		int mDbg_5;
		int mDbg_6;
		int mDbg_7;
};

}  // namespace 走行体制御
#endif
