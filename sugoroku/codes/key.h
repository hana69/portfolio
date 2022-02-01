#pragma once

#include"DxLib.h"
#include"Suken.h"
#include"key.h"

#define HOLDTIME 60

class CKey{
public:
	bool Pushed(int KeyCode,SoundType soundType);//押して，離した瞬間にtrueを返す

	bool Hold(int KeyCode,int Interval,SoundType soundType);

	void Awake();
private:
	int flag[1000];//0:押されてない 1:押してる 2:(６０フレーム以上)押し続けてる
	
	void PlayPushSound(int keyCode,int SoundType);

	struct{
		int decide;
		int select;
		int cancell;
	}sound;

	int frame;
	int tempframe;
};