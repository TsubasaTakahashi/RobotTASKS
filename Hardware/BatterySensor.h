#ifndef Hardware_BatterySensor_H
#define Hardware_BatterySensor_H

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
