#pragma once

#include"DxLib.h"
#include"Suken.h"
#include"mouse.h"
#include"key.h"

class CTitle{
	public:
		void Awake();
		void Draw(int NowCase,int frame);
		void ModeSelect(int NowCase);
		
		int EndModeSelect();

	private:
		int titlegazou[10];
		int dicePic[10];
		int Case;//¡‘I‘ğ‚³‚ê‚Ä‚é€–Ú
		int frame;

		int num;

		CMouse TMouse[5];
		CKey TKey;
};