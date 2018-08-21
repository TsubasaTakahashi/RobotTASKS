#include "ColorSensor.h"

using namespace ev3api;

namespace Hardware
{

//=============================================================================
// Constructor
ColorSensor::ColorSensor(ePortS port)
:Sensor(port, COLOR_SENSOR)
{
    (void)ev3_color_sensor_get_reflect(getPort());
}

//=============================================================================
// Destructor
ColorSensor::~ColorSensor(void)
{
    //uart_sensor_config(getPort(), -1);
}


//=============================================================================
// Get ambient value in the ambient sensor modes.
uint8_t ColorSensor::getAmbient() const
{
    return ev3_color_sensor_get_ambient(getPort());
}

//=============================================================================
// Get brightness in the light sensor modes.
int8_t ColorSensor::getBrightness(void) const
{
    return ev3_color_sensor_get_reflect(getPort());
}

}  // namespace ハード
