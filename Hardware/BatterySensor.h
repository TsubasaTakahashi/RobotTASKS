#ifndef Hardware_BatterySensor_H
#define Hardware_BatterySensor_H

#include "ev3api.h"

namespace Hardware
{
class BatterySensor
{
	public:
		explicit BatterySensor(void);

		int getBatteryVoltage();

};

}  // namespace ハード
#endif
