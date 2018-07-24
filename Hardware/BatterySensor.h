#ifndef Hardware_BatterySensor_H
#define Hardware_BatterySensor_H

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

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
