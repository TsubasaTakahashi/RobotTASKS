#ifndef Detection_StepDetection_H
#define Detection_StepDetection_H

namespace Detection
{
class StepDetection
{
	public:
		explicit StepDetection(int actDuration);

	private:
		int mMotorAngL[2] = {0, 0}; //0:Last Value 1:Before Last Value
		int mMotorAngR[2] = {0, 0};
		int mActDuration; //持続時間

		int mWheelStopCount[2] = {0, 0}; // 0:left 1:right

		void CountActNum(int* wheelStopCount int threshold, int lWheelMotorRa, int rWheelMotorRa);

	public:
		void Detect(bool* detection, int threshold, int lWheelMotorRa, int rWheelMotorRa);

};

}  // namespace 検知
#endif
