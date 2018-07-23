#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

#include "GyroSensor.h"
using namespace ev3api;

namespace Hardware
{
//=============================================================================
// Constructor
GyroSensor::GyroSensor(ePortS port)
:
Sensor(port, GYRO_SENSOR),
mOffset(DEFAULT_OFFSET)
{
	ev3_gyro_sensor_reset(getPort());
	(void)ev3_gyro_sensor_get_rate(getPort());
}

//=============================================================================
// set sensor offset data at 0 [deg/sec]
void GyroSensor::setOffset(int16_t offset)
{
	mOffset = offset;
}

//=============================================================================
// Reset gyro sensor.
void GyroSensor::reset(void)
{
	ev3_gyro_sensor_reset(getPort());
}

//=============================================================================
// get anguler velocity [deg/sec]
int16_t GyroSensor::getAnglerVelocity(void) const
{
	return ev3_gyro_sensor_get_rate(getPort()) - mOffset;
}

//=============================================================================
// get angule [deg]
int16_t GyroSensor::getAngle(void) const
{
	return ev3_gyro_sensor_get_angle(getPort());
}

}  // namespace ハード
