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
	 	 	 int SensorThreshold      //検査の閾値＿引数
		 );

	virtual ~SectionInfo(void);   //デストラクタ

	//メンバ変数宣言
	private:
		int mForward;              //フォワード値
		int mTailAngle;            //尻尾の角度
		int mBalance;              //姿勢
		int mUsedSensor;           //使用する検知
		int mSensorThreshold;      //検査の閾値

		//区間情報 区間情報;
		//区間情報 区間情報;

	public:
		virtual void GetRobotAttributeValue(int* RobotAttributeValue);     //走行の属性値を取得する

	};

}  // namespace シナリオ
#endif
