#include "BatterySensor.h"

using namespace ev3api;

namespace Hardware
{
int BatterySensor::getBatteryVoltage()
{
	return ev3_battery_voltage_mV();
}
}  // namespace ハード
