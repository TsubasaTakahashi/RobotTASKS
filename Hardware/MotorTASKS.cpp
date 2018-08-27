#include "MotorTASKS.h"

namespace Hardware
{

// Constructor
MotorTASKS::MotorTASKS(ePortM port, bool brake, motor_type_t type)
:mPort(static_cast<motor_port_t>(port)),
 mBrake(brake),
 mPWM(0),
 mType(type)
{
    ev3_motor_config(getPort(), type);
}

// Destructor
MotorTASKS::~MotorTASKS(void)
{
    ev3_motor_stop(mPort, true); // set brake to stop the motor immidiately
}

void MotorTASKS::setPWM(int pwm)
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

void MotorTASKS::setBrake(bool brake)
{
    mBrake = brake;
    setPWM(mPWM);
}

}  // namespace ハード
