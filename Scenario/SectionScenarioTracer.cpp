#include "SectionScenarioTracer.h"

namespace Scenario
{

    SectionScenarioTracer::SectionScenarioTracer(
     int Forward,             //フォワード値＿引数
     int TailAngle,           //尻尾の角度＿引数
     int Balance,             //姿勢＿引数
     int UsedSensor,          //使用する検知＿引数
     int SensorThreshold,      //検査の閾値＿引数
     int TurnValue     //反射光の閾値
         ):mForward(Forward),
         mTailAngle(TailAngle),
         mBalance(Balance),
         mUsedSensor(UsedSensor),
         mSensorThreshold(SensorThreshold),
         mTurnValue(TurnValue)
         {

         }

  virtual void SectionScenarioTracer::GetRobotAttributeValue(int* RobotAttributeValue)
  {
    RobotAttributeValue[0] = mForward;
    RobotAttributeValue[1] = mTailAngle;
    RobotAttributeValue[2] = mBalance;
    RobotAttributeValue[3] = mUsedSensor;
    RobotAttributeValue[4] = mSensorThreshold;
    RobotAttributeValue[5] = mTurnValue;
  }
}  // namespace シナリオ
