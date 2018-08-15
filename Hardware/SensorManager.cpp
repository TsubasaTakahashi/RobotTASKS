#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

#include "SensorManager.h"

namespace Hardware
{

	SensorManager(BatterySensor* batterySensor,
								ColorSensor*  colorSensor,
								GyroSensor* gyroSensor,
								MotorRaSensor& lWheelRaSensor,
								MotorRaSensor& rWheelRaSensor,
								MotorRaSensor& tailRaSensor)
				:mBatterySensor(batterySensor),
				 mColorSensor(colorSensor),
				 mGyroSensor(gyroSensor),
				 mLWheelRaSensor(lWheelRaSensor),
				 mRWheelRaSensor(rWheelRaSensor),
				 mTailRaSensor(tailRaSensor) {

				 }

	int SensorManager::getBrightness()
	{
		return (int)mColorSensor.getBrightness();
	}

	void SensorManager::getTireMotorRa(int* tireMotorRa)
	{
		tireMotorRa[0] = mLWheelRaSensor.getCount();
		tireMotorRa[1] = mRWheelRaSensor.getCount();
	}

	int SensorManager::getTailMotorRa()
	{
		return (int)mTailRaSensor.getCount();
	}

	int SensorManager::getRobotAv()
	{
		return (int)mGyroSensor.getAnglerVelocity();
	}

	int SensorManager::getBatteryVoltage()
	{
		return (int)mBatterySensor.getBatteryVoltage();
	}

}  // namespace ハード
