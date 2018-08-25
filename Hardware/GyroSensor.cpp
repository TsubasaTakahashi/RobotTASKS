#include "GyroSensor.h"

namespace Hardware
{
//=============================================================================
// Constructor
GyroSensor::GyroSensor(ePortS port)
:
Sensor(port, GYRO_SENSOR),
mOffset(DEFAULT_OFFSET)
{
	ev3api::ev3_gyro_sensor_reset(getPort());
	(void)ev3api::ev3_gyro_sensor_get_rate(getPort());
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
	ev3api::ev3_gyro_sensor_reset(getPort());
}

//=============================================================================
// get anguler velocity [deg/sec]
int16_t GyroSensor::getAnglerVelocity(void) const
{
	return ev3api::ev3_gyro_sensor_get_rate(getPort()) - mOffset;
}

}  // namespace ハード
