#include "ColorSensorTASKS.h"

namespace Hardware
{

//=============================================================================
// Constructor
ColorSensorTASKS::ColorSensorTASKS(ePortS port)
:Sensor(port, COLOR_SENSOR)
{
    (void)ev3_color_sensor_get_reflect(getPort());
}

//=============================================================================
// Destructor
ColorSensorTASKS::~ColorSensorTASKS(void)
{
    //uart_sensor_config(getPort(), -1);
}


//=============================================================================
// Get ambient value in the ambient sensor modes.
uint8_t ColorSensorTASKS::getAmbient() const
{
    return ev3_color_sensor_get_ambient(getPort());
}

//=============================================================================
// Get brightness in the light sensor modes.
int8_t ColorSensorTASKS::getBrightness(void) const
{
    return ev3_color_sensor_get_reflect(getPort());
}

}  // namespace ハード
