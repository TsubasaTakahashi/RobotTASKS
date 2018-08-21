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
		int mCumulativeSum;

		double mPidGain; /* PID調整用のゲイン */
		double mPidOffset; /* PID調整用のオフセット */
		double mDeltaT; /* ループタスクの1回の処理時間 */

	public:
		int CalcControlVal(int iCurrentVal, int iTargetVal);
};

}  // namespace 走行体制御
#endif
