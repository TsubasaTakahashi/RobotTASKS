#ifndef Scenario_SectionLineTracer_H
#define Scenario_SectionLineTracer_H

#include "SectionInfo.h"

namespace Scenario
{
  class SectionLineTracer : public SectionInfo
  {
  public:                         //コンストラクタ
    explicit SectionLineTracer
    (
      int Forward,             //フォワード値＿引数
      int TailAngle,           //尻尾の角度＿引数
      int Balance,             //姿勢＿引数
      int UsedSensor,          //使用する検知＿引数
      int SensorThreshold,      //検査の閾値＿引数
      int ReflectedThreshold     //反射光の閾値
    );

  virtual ~SectionLineTracer(void);      //デストラクタ

  //メンバ変数宣言
  private:
    int mReflectedThreshold;     //ターン値

  //メンバ関数宣言
 public:
   virtual void GetRobotAttributeValue(int* RobotAttributeValue);     //走行の属性値を取得する
  }
}
