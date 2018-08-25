#ifndef Hardware_ColorSensor_H
#define Hardware_ColorSensor_H

#include "ev3api.h"
//using namespace ev3api;

namespace Hardware
{
class ColorSensor: public Sensor
{
	public:
		/**
		* コンストラクタ
		* @param port カラーセンサポート番号
		* @return -
		*/
		explicit ColorSensor(ePortS port);

		/**
		* デストラクタ
		* @param -
		* @return -
		*/
		virtual ~ColorSensor(void);

		/**
		* 環境光の強さを測定する
		* @param -
		* @return 環境光の強さ（0〜100）
		*/
		uint8_t getAmbient(void) const;

		/**
		* 反射光の強さを測定する
		* @param -
		* @return 反射光の強さ (0-100)
		*/
		int8_t getBrightness(void) const;
};

}  // namespace ハード
#endif
