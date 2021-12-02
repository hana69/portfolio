#pragma once

#include"DxLib.h"
#include"General.h"

static struct {
	const int BACK;
	const int DELETE_KEY;
	const int ENTER;
	const int L_SHIFT;
	const int R_SHIFT;
	const int SPACE;
	const int ESC;
	const int LEFT;
	const int UP;
	const int RIGHT;
	const int DOWN;
	const int A;
	const int Z;
	const int X;
	const int C;
	const int S;
	const int D;
} KEYNAME={
	KEY_INPUT_BACK,
	KEY_INPUT_DELETE,
	KEY_INPUT_RETURN,
	KEY_INPUT_LSHIFT,
	KEY_INPUT_RSHIFT,
	KEY_INPUT_SPACE,
	KEY_INPUT_ESCAPE,
	KEY_INPUT_LEFT,
	KEY_INPUT_UP,
	KEY_INPUT_RIGHT,
	KEY_INPUT_DOWN,
	KEY_INPUT_A,
	KEY_INPUT_Z,
	KEY_INPUT_X,
	KEY_INPUT_C,
	KEY_INPUT_S,
	KEY_INPUT_D
};

#define HOLDTIME 60

class CKey{
public:
	enum SoundType{
		NOT_PLAY,
		DECIDE_SOUND,
		BACK_SOUND,
		SELECT_SOUND
	};
	void Awake();

	bool Pushing(int _keyCode);
	bool Pushed( int _keyCode ,SoundType _soundType=NOT_PLAY);//�����āC�������u�Ԃ�true��Ԃ�
	bool Hold( int _keyCode , int _interval=10,SoundType _soundType=NOT_PLAY);//Interval�t���[������true��Ԃ�

private:
	int flag[1000];//0:������ĂȂ� 1:�����Ă� 2:(�U�O�t���[���ȏ�)���������Ă�
	
	void PlayReleaseSound(SoundType);

	struct{
		int decide;
		int select;
		int cancell;
	}sound;

	int frame[1000];
	int tempframe;
};

static CKey Key;

////�I��p�֐�////

////�ϐ��̃A�h���X�Ƃ��̕ϐ�����肤��ŏ��ƍő�̒l��n����
////���͈̔͂ō��E�L�[�őI���ł���悤��
static void NumSelect_LR(int *n,int min,int max){
	if(Key.Pushed(KEYNAME.RIGHT,CKey::SELECT_SOUND)){
		(*n)++;
		if((*n)>max){
			*n=min;
		}
	}
	if(Key.Pushed(KEYNAME.LEFT,CKey::SELECT_SOUND)){
		(*n)--;
		if((*n)<min){
			(*n)=max;
		}
	}
}

static void NumSelect_UD(int *n,int min,int max){
	if(Key.Pushed(KEYNAME.DOWN,CKey::SELECT_SOUND)){
		(*n)++;
		if((*n)>max){
			*n=min;
		}
	}
	if(Key.Pushed(KEYNAME.UP,CKey::SELECT_SOUND)){
		(*n)--;
		if((*n)<min){
			(*n)=max;
		}
	}
}

static void NumSelect_LR(bool *n){
	if(Key.Pushed(KEYNAME.RIGHT,CKey::SELECT_SOUND)){
		if((*n)==true){
			(*n)=false;
		}
	}
	if(Key.Pushed(KEYNAME.LEFT,CKey::SELECT_SOUND)){
		if((*n)==false){
			(*n)=true;
		}
	}
}

