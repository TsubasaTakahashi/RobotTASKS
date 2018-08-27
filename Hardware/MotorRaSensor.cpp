#include "MotorRaSensor.h"

namespace Hardware
{
// Constructor
MotorRaSensor::MotorRaSensor(ePortM port, motor_type_t type)
:mPort(static_cast<motor_port_t>(port)),
 mType(type),
 mOffset(0)
{
	ev3_motor_config(getPort(), type);
}

// Destructor
MotorRaSensor::~MotorRaSensor(void)
{
	ev3_motor_stop(mPort, true); // set brake to stop the motor immidiately
}

//int MotorRaSensor::センサ値を取得する()
//{
	//return 0;
//}
}  // namespace ハード
