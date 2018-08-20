#ifndef Scenario_SectionLineTracer_H
#define Scenario_SectionLineTracer_H

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

namespace Scenario
{
  class SectionLineTracer : public SectionInfo
  {
  public:                         //コンストラクタ
    explicit SectionLineTracer
    (
      int ReflectedThreshold;     //反射光の閾値
    );

  ~SectionLineTracer(void);      //デストラクタ

  //メンバ変数宣言
  private:
    int mReflectedThreshold;     //ターン値

  //メンバ関数宣言
 public:
   void GetRobotAttributeValue(int* RobotAttributeValue);     //走行の属性値を取得する
  }
}
