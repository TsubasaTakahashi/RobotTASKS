#ifndef Hardware_MotorTASKS_H
#define Hardware_MotorTASKS_H

#include "Port.h"
#include "ev3api.h"

namespace Hardware
{
class MotorTASKS
{

	public:
		static const int PWM_MAX = 100;
		static const int PWM_MIN = 100;

		explicit MotorTASKS(ePortM port, bool brake = true, motor_type_t type = LARGE_MOTOR);

		~MotorTASKS(void);

		/**
		* モータリセット<br>
		* モータ停止および角位置の0リセット、オフセット初期化を行う
		* @param -
		* @return -
		*/
		inline void reset(void)
		{
		  ev3_motor_stop(mPort, true); // need to set brake to stop the motor immidiately
		}

		/**
		* モータPWM値設定<br>
		* ブレーキモードでPWM値が0の場合、モータを停止する
		* @param pwm PWM値 (-100 - 100)
		* @return -
		*/
		void setPWM(int pwm);

		/**
		* ブレーキモード設定
		* @param brake true:ブレーキモード/false:フロートモード
		* @return -
		*/
		void setBrake(bool brake);

	protected:
		/**
		* モータ接続ポート取得
		* @param -
		* @return モータ接続ポート
		*/
		inline motor_port_t getPort(void) const { return mPort; }

private:
  motor_port_t mPort;
  bool mBrake;
	int mPWM;
  motor_type_t mType;
  //int32_t mOffset;

};

}  // namespace ハード
#endif
