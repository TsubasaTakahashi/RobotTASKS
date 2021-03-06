#ifndef Hardware_GyroSensorTASKS_H
#define Hardware_GyroSensorTASKS_H

#include "ev3api.h"
#include "Sensor.h"
using namespace ev3api;

namespace Hardware
{
class GyroSensorTASKS: public Sensor
{
	public:
		/**
		* ジャイロセンサオフセット初期値
		*/
		static const int16_t DEFAULT_OFFSET = 0;

		/**
		* コンストラクタ<br>
		* ジャイロセンサの角位置を0リセットする
		* @param port ジャイロセンサ接続ポート
		* @return -
		*/
		explicit GyroSensorTASKS(ePortS port);

		/**
		* 角速度に対するオフセットを設定する<br>
		* オフセット値 = 角速度 0[deg/sec] のときのセンサ値
		* @param offset オフセット値 (0-1023)
		* @return -
		*/
		void setOffset(int16_t offset);

		/**
		* ジャイロセンサの角位置を0リセットする
		* @param -
		* @return -
		*/
		void reset(void);

		/**
		* オフセット付き角速度取得
		* @param -
		* @return 角速度 [deg/sec]
		*/
		int16_t getAnglerVelocity(void) const;

	private:
		int16_t mOffset;

};

}  // namespace ハード
#endif
