#pragma once

#include"DxLib.h"
#include"Suken.h"
#include"key.h"

#define HOLDTIME 60

class CKey{
public:
	bool Pushed(int KeyCode,SoundType soundType);//�����āC�������u�Ԃ�true��Ԃ�

	bool Hold(int KeyCode,int Interval,SoundType soundType);

	void Awake();
private:
	int flag[1000];//0:������ĂȂ� 1:�����Ă� 2:(�U�O�t���[���ȏ�)���������Ă�
	
	void PlayPushSound(int keyCode,int SoundType);

	struct{
		int decide;
		int select;
		int cancell;
	}sound;

	int frame;
	int tempframe;
};