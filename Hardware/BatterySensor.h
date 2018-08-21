#ifndef Hardware_BatterySensor_H
#define Hardware_BatterySensor_H

#include "ev3api.h"

namespace Hardware
{
class BatterySensor
{
	explicit BatterySensor(void);

	~BatterySensor(void);

	public:
		int getBatteryVoltage();

};

}  // namespace ハード
#endif
