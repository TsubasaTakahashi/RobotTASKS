#include "DetectionManager.h"

namespace Detection
{
	DetectionManager::DetectionManager(Hardware::SensorManager* sensorManager,
								DistanceDetection* distanceDetection,
								GrayDetection* grayDetection,
								StepDetection* stepDetection,
								ImpactDetection* impactDetection)
								:mSensorManager(sensorManager),
								mDistanceDetection(distanceDetection),
								mGrayDetection(grayDetection),
								mStepDetection(stepDetection),
								mImpactDetection(impactDetection)
								{

								}

	bool DetectionManager::GrayDetect(int threshold)
	{
		int brightness = 0;
		bool detection = false;

		brightness = mSensorManager->getBrightness();

		detection = mGrayDetection->Detect(threshold, brightness);

		return detection;
	}

	bool DetectionManager::StepDetect(bool* detection, int threshold)
	{
		int* wheelMotorRa;

		wheelMotorRa = (int* )malloc(sizeof(int) * 2);
		mSensorManager->getWheelMotorRa(wheelMotorRa);

		int leftWheelEnc = wheelMotorRa[0]; // 左モータ回転角度
    int rightWheelEnc  = wheelMotorRa[1]; // 右モータ回転角度

		mStepDetection->Detect(detection, threshold, leftWheelEnc, rightWheelEnc);

		free(wheelMotorRa);
	}

	bool DetectionManager::DistanceDetect(int threshold)
	{
		int* wheelMotorRa;
		bool detection = false;

		wheelMotorRa = (int* )malloc(sizeof(int)*2);
		mSensorManager->getWheelMotorRa(int* wheelMotorRa);

		int leftWheelEnc = wheelMotorRa[0]; // 左モータ回転角度
    int rightWheelEnc  = wheelMotorRa[1]; // 右モータ回転角度

		detection = mDistanceDetection->Detect(threshold, leftWheelEnc, rightWheelEnc);

		free(wheelMotorRa);
		return detection;
	}

	bool DetectionManager::ImpactDetect(int threshold)
	{
		bool detection = false;
		int robotAv = 0;

		robotAv = mSensorManager->getRobotAv();
		detection = mImpactDetection->Detect(threshold, robotAv);

		return detection;
	}

}  // namespace 検知
