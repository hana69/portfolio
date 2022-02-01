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
		int Random;//サイコロが回ってる（？）時の目
		int Num;//出た目

		int debugmode;//デバッグ用の機能
};