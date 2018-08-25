#include "SensorManager.h"

namespace Hardware
{

	SensorManager(BatterySensor* batterySensor,
								ColorSensor&  colorSensor,
								GyroSensor& gyroSensor,
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
		return mColorSensor.getBrightness();
	}

	void SensorManager::getWheelMotorRa(int* wheelMotorRa)
	{
		wheelMotorRa[0] = mLWheelRaSensor.getCount();
		wheelMotorRa[1] = mRWheelRaSensor.getCount();
	}

	int SensorManager::getTailMotorRa()
	{
		return mTailRaSensor.getCount();
	}

	int SensorManager::getRobotAv()
	{
		return mGyroSensor.getAnglerVelocity();
	}

	int SensorManager::getBatteryVoltage()
	{
		return mBatterySensor->getBatteryVoltage();
	}

}  // namespace ハード
