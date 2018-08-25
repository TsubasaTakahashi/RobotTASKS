#ifndef Scenario_SectionScenarioTracer_H
#define Scenario_SectionScenarioTracer_H

#include "SectionInfo.h"

namespace Scenario
{
  class SectionScenarioTracer : public SectionInfo
  {
  public:                          //コンストラクタ
    explicit SectionScenarioTracer
    (
      int mForward,             //フォワード値＿引数
      int mTailAngle,           //尻尾の角度＿引数
      int mBalance,             //姿勢＿引数
      int mUsedSensor,          //使用する検知＿引数
      int mSensorThreshold,      //検査の閾値＿引数
      int mTurnValue               //ターン値
    );

  virtual ~SectionScenarioTracer(void);    //デストラクタ

  //メンバ変数宣言
  private:
    int mTurnValue;              //ターン値

  //メンバ関数宣言
 public:
   virtual void GetRobotAttributeValue(int* RobotAttributeValue);     //走行の属性値を取得する
 };
}
#endif