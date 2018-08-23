#ifndef Detection_ImpactDetection_H
#define Detection_ImpactDetection_H

namespace Detection
{
class ImpactDetection
{

	public:
		ImpactDetection(int timeThreshold, int timeWidth);

		~ImpactDetection(void);

	private:
		int* mRobotAv;
		int mTimeThreshold;
		int mActnNum;

		int CountActNum(int threshold, int robotAv);

	public:
		bool Detect(int threshold, int robotAv);

};

}  // namespace 検知
#endif
