#ifndef Hardware_ColorSensorTASKS_H
#define Hardware_ColorSensorTASKS_H

#include "ev3api.h"
#include "Sensor.h"
using namespace ev3api;

namespace Hardware
{
class ColorSensorTASKS: public Sensor
{
	public:
		/**
		* コンストラクタ
		* @param port カラーセンサポート番号
		* @return -
		*/
		explicit ColorSensorTASKS(ePortS port);

		/**
		* デストラクタ
		* @param -
		* @return -
		*/
		~ColorSensorTASKS(void);

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
