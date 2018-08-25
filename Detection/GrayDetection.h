/****************************/
/*	�T�v�F�D�F���m�N���X	*/
/*	�쐬�ҁF����			*/
/*	�쐬���F2018/08/14		*/
/*	�C�����F2018/08/25		*/
/****************************/
#pragma once
#include <vector>

using namespace std;

namespace Detection
{
	class GrayDetection
	{
	private:
		int iGrayDetectionDuration;			/*	�D�F���m�̎�������	*/
		int iWidth;							/*	�D�F���m��臒l�̕�	*/
		vector<int> iaReflectLight;			/*	���܂ł̔��ˌ�		*/
		const int iDefalutCounterValue = 0;	/*	�J�E���^�[�̏����l	*/
		unsigned int uiSampleNumber;		/*	�T���v���_��		*/
		int iAverage = 0;					/*	���ϒl				*/

		int CalculateAverage(void);						/*	���ϒl���v�Z����	*/
		int Count(const int &iGrayDetectionThreshold);	/*	�J�E���g����		*/

	public:
		int iCount;	/*	���O�p�̃J�E���g�l	*/

		GrayDetection(const int &Duration, const int &Width);											/*	�R���X�g���N�^	*/
		bool DetectGrayLine(const int &Threshold, const unsigned int &SampleNumber, int &ReflectLight);	/*	�D�F���m(����1)	*/
		bool DetectGrayLine2(const int &Threshold, const int &ReflectLight);							/*	�D�F���m(����2)	*/
	};
}  /* namespace DETECTION	*/
