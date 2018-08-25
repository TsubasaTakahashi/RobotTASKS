#include "SectionLineTracer.h"

namespace Scenario
{

    SectionLineTracer::SectionLineTracer(
     int Forward,             //フォワード値＿引数
     int TailAngle,           //尻尾の角度＿引数
     int Balance,             //姿勢＿引数
     int UsedSensor,          //使用する検知＿引数
     int SensorThreshold,      //検査の閾値＿引数
     int ReflectedThreshold     //反射光の閾値
         ):mForward(Forward),
         mTailAngle(TailAngle),
         mBalance(Balance),
         mUsedSensor(UsedSensor),
         mSensorThreshold(SensorThreshold),
         mReflectedThreshold(ReflectedThreshold)
         {

         }

void SectionLineTracer::GetRobotAttributeValue(int* RobotAttributeValue)
  {
    RobotAttributeValue[0] = mForward;
    RobotAttributeValue[1] = mTailAngle;
    RobotAttributeValue[2] = mBalance;
    RobotAttributeValue[3] = mUsedSensor;
    RobotAttributeValue[4] = mSensorThreshold;
    RobotAttributeValue[5] = mReflectedThreshold;
  }
}  // namespace シナリオ
