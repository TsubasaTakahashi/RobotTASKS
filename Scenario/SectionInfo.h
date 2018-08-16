/*

*/
#ifndef Scenario_SectionInfo_H   //Japanese -> English
#define Scenario_SectionInfo_H   //Japanese -> English

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

namespace Scenario              //Japanese -> English
{
class SectionInfo               //Japanese -> English
{
	//コンストラクタ
	public
	 explicit SectionInfo();　　　//引数いるなら何か書く

　~SectionInfo(void)    　　　　//デストラクタ

//メンバ変数宣言
private:
	int m_Forward;         //フォワード値

	int m_TailAngle;       //尻尾の角度

	int m_Balance;         //姿勢

	int m_UsedSensor;      //使用する検知

	int m_SensorThreshold; //検査の閾値

	//区間情報 区間情報;
	//区間情報 区間情報;

public:
	void 走行の属性値を取得する(int* 走行体の属性値);

};

}  // namespace シナリオ
#endif
