#include "GyroSensorTASKS.h"

namespace Hardware
{
//=============================================================================
// Constructor
GyroSensorTASKS::GyroSensorTASKS(ePortS port)
:
Sensor(port, GYRO_SENSOR),
mOffset(DEFAULT_OFFSET)
{
	ev3_gyro_sensor_reset(getPort());
	(void)ev3_gyro_sensor_get_rate(getPort());
}

//=============================================================================
// set sensor offset data at 0 [deg/sec]
void GyroSensorTASKS::setOffset(int16_t offset)
{
	mOffset = offset;
}

//=============================================================================
// Reset gyro sensor.
void GyroSensorTASKS::reset(void)
{
	ev3_gyro_sensor_reset(getPort());
}

//=============================================================================
// get anguler velocity [deg/sec]
int16_t GyroSensorTASKS::getAnglerVelocity(void) const
{
	return ev3_gyro_sensor_get_rate(getPort()) - mOffset;
}

}  // namespace ハード
