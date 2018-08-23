#ifndef Hardware_MotorRaSensor_H
#define Hardware_MotorRaSensor_H

#include "Port.h"
#include "ev3api.h"

namespace Hardware
{
class MotorRaSensor
{
	public:

		explicit MotorRaSensor(ePortM port, motor_type_t type = LARGE_MOTOR);

		~MotorRaSensor(void);

		/**
		 * モータリセット<br>
		 * モータ停止および角位置の0リセット、オフセット初期化を行う
		 * @param -
		 * @return -
		 */
		inline void reset(void)
		{
			ev3_motor_stop(mPort, true); // need to set brake to stop the motor immidiately
			ev3_motor_reset_counts(mPort);
			mOffset = 0;
		}

		/**
		* オフセット付き角位置取得
		* @param -
		* @return モータ角位置 [deg]
		*/
		inline int32_t getCount(void) const { return ev3_motor_get_counts(mPort) - mOffset; }

	protected:
		/**
		* モータ接続ポート取得
		* @param -
		* @return モータ接続ポート
		*/
		inline motor_port_t getPort(void) const { return mPort; }

	private:
		motor_port_t mPort;
		//bool mBrake;
		motor_type_t mType;
		//int mPWM;
		int32_t mOffset;
};

}  // namespace ハード
#endif
