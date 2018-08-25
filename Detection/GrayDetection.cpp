/****************************/
/*	�T�v�F�D�F���m�N���X	*/
/*	�쐬�ҁF����			*/
/*	�쐬���F2018/08/14		*/
/*	�C�����F2018/08/25		*/
/****************************/
#pragma once
#include "GrayDetection.h"

namespace Detection
{
	/********************************/
	/*	���ˌ��̕��ϒl���v�Z����	*/
	/********************************/
	int GrayDetection::CalculateAverage(void)
	{
		/*	���ˌ��̕��ϒl���v�Z����	*/
		for (const auto &i : iaReflectLight) {
			iAverage = iAverage + i;
		}
		iAverage = iAverage / uiSampleNumber;

		return iAverage;
	}

	/****************************************************/
	/*	���ˌ��̕��ϒl��臒l���ɂ��邩���J�E���g����	*/
	/****************************************************/
	int GrayDetection::Count(const int &iGrayDetectionThreshold)
	{
		int iAverage = CalculateAverage();
		static int iCounter = iDefalutCounterValue;

		if ((iAverage >= (iGrayDetectionThreshold - iWidth))		/*	���ˌ��̕��ϒl���A	*/
			&& (iAverage <= (iGrayDetectionThreshold + iWidth))) {	/*	臒l�͈͓̔��Ȃ��A	*/
			iCounter++;												/*	�J�E���g�����B		*/
		}
		else {														/*	�����łȂ��Ȃ��A		*/
			iCounter = iDefalutCounterValue;						/*	�J�E���g�������l�ɖ߂�	*/
		}

		return iCounter;
	}

	/********************/
	/*	�R���X�g���N�^	*/
	/********************/
	GrayDetection::GrayDetection(const int &Duration, const int &Width)
	{
		iGrayDetectionDuration = Duration;
		iWidth = Width;
	}

	/********************************************************************/
	/*	�D�F���m������(����1)											*/
	/*	�����@�F														*/
	/*		�E�擾�������ˌ����w�肵�����i�[���ꂽ���J�E���g�������B	*/
	/*		�E���ˌ��͏����X�V�����Ă����B								*/
	/*		�E�J�E���g���������Ԉȏ��ɂȂ�����true���Ԃ��B				*/
	/*	�����F															*/
	/*		iGrayDetectionThreshold�F�D�F���m��臒l						*/
	/*		iReflectLight�F�擾�������ˌ�								*/
	/********************************************************************/
	bool GrayDetection::DetectGrayLine(const int &Threshold, const unsigned int &SampleNumber, int &ReflectLight)
	{
		uiSampleNumber = SampleNumber;

		/*	���ˌ����z���Ɋi�[���Ă���	*/
		if (iaReflectLight.size() < uiSampleNumber) {
			iaReflectLight.push_back(ReflectLight);
		}

		/*	���ˌ����X�V���Ă���	*/
		else if (iaReflectLight.size() == uiSampleNumber) {
			iaReflectLight.erase(iaReflectLight.begin());
			iaReflectLight.push_back(ReflectLight);
		}

		/*	�D�F���m���s��	*/
		if (iaReflectLight.size() == uiSampleNumber) {
			if (Count(Threshold) == iGrayDetectionDuration) {
				return true;
			}
		}

		return false;
	}

	/************************************************************/
	/*	�D�F���m������(����2)									*/
	/*	�����@�F												*/
	/*		�E�擾�������ˌ���臒l���Ȃ��J�E���g�A�b�v�����B	*/
	/*		�E臒l�O�Ȃ��J�E���g��0�ɂ����B						*/
	/*		�E�J�E���g���������Ԉȏ��ɂȂ�����true���Ԃ��B		*/
	/*	�����F													*/
	/*		Threshold�F�D�F���m��臒l							*/
	/*		ReflectLight�F�擾�������ˌ�						*/
	/************************************************************/
	bool GrayDetection::DetectGrayLine2(const int &Threshold, const int &ReflectLight)
	{
		static int iCounter = iDefalutCounterValue;

		if (ReflectLight <= (Threshold + iWidth)
			&& (ReflectLight >= (Threshold - iWidth))) {
			iCounter++;
		}
		else {
			iCounter = iDefalutCounterValue;
		}
		iCount = iCounter;

		if (iCounter >= iGrayDetectionDuration) {
			return true;
		}

		return false;
	}
}
