#ifndef Scenario_SectionInfo_H   //Japanese -> English
#define Scenario_SectionInfo_H   //Japanese -> English

namespace Scenario              //Japanese -> English
{
class SectionInfo               //Japanese -> English
{
	//コンストラクタ
	public:
		explicit SectionInfo(
			int Forward,             //フォワード値＿引数
			int TailAngle,           //尻尾の角度＿引数
			int Balance,             //姿勢＿引数
			int UsedSensor,          //使用する検知＿引数
			int SensorThreshold,      //検査の閾値＿引数
			//しかたなしの改変
			int SenarioOrLine, //0:ライントレース 1:シナリオトレース
			int SuperRefThre, //ライントレース走行の目標反射光
			int SuperTurnValue //指定値走行のターン値
		);

	//メンバ変数宣言
	protected:
	//public: //デバック用
		int mForward;              //フォワード値
		int mTailAngle;            //尻尾の角度
		int mBalance;              //姿勢
		int mUsedSensor;           //使用する検知
		int mSensorThreshold;      //検査の閾値

		//しかたなしの改変
		int mSenarioOrLine; //0:ライントレース 1:シナリオトレース
		int mSuperRefThre; //ライントレース走行の目標反射光
		int mSuperTurnValue; //指定値走行のターン値

	public:
		//virtual void GetRobotAttributeValue(int* RobotAttributeValue);     //走行の属性値を取得する
		void GetRobotAttributeValue(int* RobotAttributeValue);
	};

}  // namespace シナリオ
#endif
