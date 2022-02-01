#pragma once

#include"DxLib.h"
#include"Suken.h"
#include"key.h"

#define HOLDTIME 60

class CKey{
public:
	bool Pushed(int KeyCode,SoundType soundType);//‰Ÿ‚µ‚ÄC—£‚µ‚½uŠÔ‚Étrue‚ğ•Ô‚·

	bool Hold(int KeyCode,int Interval,SoundType soundType);

	void Awake();
private:
	int flag[1000];//0:‰Ÿ‚³‚ê‚Ä‚È‚¢ 1:‰Ÿ‚µ‚Ä‚é 2:(‚U‚OƒtƒŒ[ƒ€ˆÈã)‰Ÿ‚µ‘±‚¯‚Ä‚é
	
	void PlayPushSound(int keyCode,int SoundType);

	struct{
		int decide;
		int select;
		int cancell;
	}sound;

	int frame;
	int tempframe;
};