#include "DistanceDetection.h"

namespace Detection
{
	DistanceDetection::DistanceDetection(int tireRadius)
			:mTireRadius(tireRadius)
			{

			}

	int DistanceDetection::CalcDistance(int lWheelMotorRa, int rWheelMotorRa)
	{
		int avWheelMotorRa = 0;
		double dbDistance = 0.0;

		avWheelMotorRa = ((lWheelMotorRa - mLWheelMotorRaOffset) + (rWheelMotorRa - mRWheelMotorRaOffset)) / 2;
		dbDistance = (double)mTireRadius * (double)avWheelMotorRa * M_PI / 180.0;

		return (int)dbDistance;
	}

	void DistanceDetection::SetStartWheelCount(int lWheelMotorRa, int rWheelMotorRa)
	{
		mLWheelMotorRaOffset = lWheelMotorRa;
		mRWheelMotorRaOffset = rWheelMotorRa;
	}

	bool DistanceDetection::Detect(int threshold, int lWheelMotorRa, int rWheelMotorRa)
	{
		int distance;

		if(mReset == 0){ //初期タイヤ位置セット
			SetStartWheelCount(lWheelMotorRa, rWheelMotorRa);
			mReset = 1;
		}

		distance = DistanceDetection::CalcDistance(lWheelMotorRa, rWheelMotorRa);

		if(distance >= threshold){
			mReset = 0;
			return true;
		}

		return false;
	}
}  // namespace 検知
