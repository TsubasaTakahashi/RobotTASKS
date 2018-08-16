#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

#include "DistanceDetection.h"

namespace Detection
{
	DistanceDetection(int tireRadius)
			:mTireRadius(tireRadius){}

	int DistanceDetection::CalcDistance(int lWheelMotorRa, int rWheelMotorRa)
	{
		int avWheelMotorRa = 0;
		double dbDistance = 0.0;

		avWheelMotorRa = ((lWheelMotorRa - mLWheelMotorRaOffset) + (rWheelMotorRa - mRWheelMotorRaOffset)) / 2;
		dbDistance = (double)mTireRadius * (int)avWheelMotorRa * M_PI / 180.0;

		return (int)avWheelMotorRa;
	}

	void DistanceDetection::SetStartWheelCount(int lWheelMotorRa, int rWheelMotorRa)
	{
		mLWheelMotorRaOffset = lWheelMotorRa;
		mRWheelMotorRaOffset = rWheelMotorRa;
	}

	bool DistanceDetection::DoDetection(int threshold, int lWheelMotorRa, int rWheelMotorRa)
	{
		int distance;

		if(mReset == 0){ //初期タイヤ位置セット
			SetStartWheelCount(lWheelMotorRa, rWheelMotorRa);
			mReset = 1;
		}

		distance = DistanceDetection::CalcDistance(lWheelMotorRa, rWheelMotorRa);

		if(distance => threshold){
			mReset = 0;
			return true;
		}
		else{
			return false;
		}
	}
}  // namespace 検知
