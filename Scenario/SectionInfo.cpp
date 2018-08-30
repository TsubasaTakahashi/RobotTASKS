#include "SectionInfo.h"

namespace Scenario
{

    SectionInfo::SectionInfo(
     int Forward,             //フォワード値＿引数
     int TailAngle,           //尻尾の角度＿引数
     int Balance,             //姿勢＿引数
     int UsedSensor,          //使用する検知＿引数
     int SensorThreshold,      //検査の閾値＿引数
     //しかたなしの改変
     int SenarioOrLine, //0:ライントレース 1:シナリオトレース
     int SuperRefThre, //ライントレース走行の目標反射光
     int SuperTurnValue //指定値走行のターン値
         ):mForward(Forward),
         mTailAngle(TailAngle),
         mBalance(Balance),
         mUsedSensor(UsedSensor),
         mSensorThreshold(SensorThreshold),
         mSenarioOrLine(SenarioOrLine), //0:ライントレース 1:シナリオトレース
         mSuperRefThre(SuperRefThre), //ライントレース走行の目標反射光
         mSuperTurnValue(SuperTurnValue) //指定値走行のターン値
         {

         }

  void SectionInfo::GetRobotAttributeValue(int* RobotAttributeValue)
  {
    RobotAttributeValue[0] = mForward;
    RobotAttributeValue[1] = mTailAngle;
    RobotAttributeValue[2] = mBalance;
    RobotAttributeValue[3] = mUsedSensor;
    RobotAttributeValue[4] = mSensorThreshold;
    //しかたなしの改変
    RobotAttributeValue[5] = mSenarioOrLine;
    RobotAttributeValue[6] = mSuperRefThre;
    RobotAttributeValue[7] = mSuperTurnValue;
  }
}  // namespace シナリオ
