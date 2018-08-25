#ifndef Hardware_SensorManager_H
#define Hardware_SensorManager_H

#include "Motor.h"	//"ハード/モータ.h"
#include "ColorSensor.h" //"ハード/カラーセンサ.h"
#include "GyroSensor.h" //#include "ハード/ジャイロセンサ.h"
#include "BatterySensor.h" //"ハード/バッテリセンサ.h"
#include "MotorRaSensor.h" //"ハード/モータ回転角度センサ.h"

namespace Hardware
{
class SensorManager
{
	public:
		explicit SensorManager(BatterySensor* batterySensor,
                           ColorSensor&   colorSensor,
                           GyroSensor&    gyroSensor,
                           MotorRaSensor& lWheelRaSensor,
                           MotorRaSensor& rWheelRaSensor,
                           MotorRaSensor& tailRaSensor);

		~SensorManager(void);

	private:
		BatterySensor* mBatterySensor;
		ColorSensor& mColorSensor;
		GyroSensor& mGyroSensor;
		
		MotorRaSensor& mLWheelRaSensor;
		MotorRaSensor& mRWheelRaSensor;
		MotorRaSensor& mTailRaSensor;

	public:
		int getBrightness(); //反射光を取得する

		void getWheelMotorRa(int* wheelMotorRa); //左右モータの回転角度を取得する

		int getTailMotorRa(); //尻尾モータの回転角度を取得する

		int getRobotAv(); //走行体の角速度を取得する

		int getBatteryVoltage(); //バッテリの電圧を取得する

};

}  // namespace ハード
#endif
