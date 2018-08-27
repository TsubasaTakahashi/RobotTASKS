#include "SensorManager.h"

namespace Hardware
{

	SensorManager::SensorManager(BatterySensor* batterySensor,
								ColorSensorTASKS&  colorSensor,
								GyroSensorTASKS& gyroSensor,
								MotorRaSensor& lWheelRaSensor,
								MotorRaSensor& rWheelRaSensor,
								MotorRaSensor& tailRaSensor)
				:mBatterySensor(batterySensor),
				 mColorSensorTASKS(colorSensor),
				 mGyroSensorTASKS(gyroSensor),
				 mLWheelRaSensor(lWheelRaSensor),
				 mRWheelRaSensor(rWheelRaSensor),
				 mTailRaSensor(tailRaSensor) {

				 }

	int SensorManager::getBrightness()
	{
		return mColorSensorTASKS.getBrightness();
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
		return mGyroSensorTASKS.getAnglerVelocity();
	}

	int SensorManager::getBatteryVoltage()
	{
		return mBatterySensor->getBatteryVoltage();
	}

}  // namespace ハード
