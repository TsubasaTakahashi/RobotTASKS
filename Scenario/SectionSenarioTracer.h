#ifndef Scenario_SectionSenarioTracer_H
#define Scenario_SectionSenarioTracer_H

namespace Scenario
{
  class SectionSenarioTracer : public SectionInfo
  {
  public:                          //コンストラクタ
    explicit SectionSenarioTracer
    (
      int TurnValue;               //ターン値
    );

  ~SectionSenarioTracer(void);    //デストラクタ

  //メンバ変数宣言
  private:
    int mTurnValue;              //ターン値

  //メンバ関数宣言
 public:
   void GetRobotAttributeValue(int* RobotAttributeValue);     //走行の属性値を取得する
  }
}
