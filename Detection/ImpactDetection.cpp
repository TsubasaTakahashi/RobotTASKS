#include "ImpactDetecton.h"

namespace Detection
{
	ImpactDetection(int timeThreshold, int timeWidth)
									:mTimeThreshold(timeThreshold),
									mActNum(0)
									{
										mRobotAv = (int*)malloc(sizeof(int) * timeWidth);
									}
	~ImpactDetection(void)
	{
		free(mRobotAv);
	}

	bool ImpactDetection::Detect(int threshold, int robotAv)
	{
		mActnNum = ImpactDetection::CountActNum(threshold, robotAv);

		if(mActnNum >= mTimeThreshold){
			mActnNum = 0;
			mRobotAv = {0};
			return true;
		}
		else{
			return false;
		}
	}

	int ImpactDetection::CountActNum(int threshold, int robotAv)
	{
		//TBD
	}
}  // namespace 検知
