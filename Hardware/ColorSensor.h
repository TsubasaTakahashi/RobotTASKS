#ifndef Hardware_ColorSensor_H
#define Hardware_ColorSensor_H

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>


namespace Hardware
{
class ColorSensor
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
