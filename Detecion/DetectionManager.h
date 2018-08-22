#ifndef Detection_DetectionManager_H
#define Detection_DetectionManager_H

#include "SensorManager.h"
#include "DistanceDetection.h"
#include "GrayDetection.h"
#include "StepDetection.h"
#include "ImpactDetection.h"

namespace Detection
{
class DetectionManager
{
	public:
		explicit SensorManager(SensorManager* sensorManager,
													DistanceDetection* distanceDetection,
													GrayDetection* grayDetection,
													StepDetection* stepDetection,
													ImpactDetection* impactDetection);
	private:
		SensorManager* mSensorManager;
		DistanceDetection* mDistanceDetection;
		GrayDetection* mGrayDetection;
		StepDetection* mStepDetection;
		ImpactDetection* mImpactDetection;

	public:
		bool GrayDetect(int threshold);

		bool StepDetect(bool* detection, int threshold);

		bool DistanceDetect(int threshold);

		bool ImpactDetect(int threshold);

	};

}  // namespace 検知
#endif
