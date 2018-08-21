#include "Motor.h"

using namespace ev3api;

namespace Hardware
{

// Constructor
Motor::Motor(ePortM port, bool brake, motor_type_t type)
:mPort(static_cast<motor_port_t>(port)),
 mBrake(brake),
 mPWM(0),
 mType(type)
{
    ev3_motor_config(getPort(), type);
}

// Destructor
Motor::~Motor(void)
{
    ev3_motor_stop(mPort, true); // set brake to stop the motor immidiately
}

void Motor::setPWM(int pwm)
{
    mPWM = (pwm>PWM_MAX)? PWM_MAX:((pwm<PWM_MIN)? PWM_MIN:pwm);

    if (mBrake == true && pwm == 0)
    {
        ev3_motor_stop(mPort, true);
    }
    else
    {
        ev3_motor_set_power(mPort, mPWM);
    }
}

void Motor::setBrake(bool brake)
{
    mBrake = brake;
    setPWM(mPWM);
}

}  // namespace ハード
