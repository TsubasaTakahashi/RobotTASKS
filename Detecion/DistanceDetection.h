#ifndef Detection_DistanceDetection_H
#define Detection_DistanceDetection_H

#define _USE_MATH_DEFINES
#include <math.h>

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

namespace Detection
{
class DistanceDetection
{
	public:
		explicit DistanceDetection(int tireRadius);

	private:
		int mLWheelMotorRaOffset = 0; //検知開始時の左モータの回転角度
		int mRWheelMotorRaOffset = 0; //検知開始時の右モータの回転角度;

		int mTireRadius;
		int mReset = 0;

		int CalcDistance(int lWheelMotorRa, int rWheelMotorRa);
		void SetStartWheelCount(int lWheelMotorRa, int rWheelMotorRa);

	public:
		bool DoDetection(int threshold, int lWheelMotorRa, int rWheelMotorRa);

};

}  // namespace 検知
#endif
