#pragma once

#include "DxLib.h"
#include "Suken.h"

class CDice{
	public:
		void Awake();

		void DiceDraw(int Case , int frame);
		void ModeSelect();
		void SetNum();

		int GetNum();
		int GetRandom();

		int GetDebugMode();
		void SetDebugMode(int num);
	private:
		int dicePic[10];
		int Random;//�T�C�R��������Ă�i�H�j���̖�
		int Num;//�o����

		int debugmode;//�f�o�b�O�p�̋@�\
};