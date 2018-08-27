#include "BatterySensor.h"

namespace Hardware
{
int BatterySensor::getBatteryVoltage()
{
	return ev3_battery_voltage_mV();
}
}  // namespace ハード
