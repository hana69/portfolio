#include"key.h"

void CKey::Awake(){
	tempframe=0;
	frame=0;
	
	flag[KEY_INPUT_BACK]=0;
	flag[KEY_INPUT_RETURN]=0;
	flag[KEY_INPUT_RIGHT]=0;
	flag[KEY_INPUT_LEFT]=0;
	flag[KEY_INPUT_UP]=0;
	flag[KEY_INPUT_DOWN]=0;

	sound.cancell = LoadSoundMem("sugoroku_Resource/modoru.mp3");
	sound.decide =  LoadSoundMem("sugoroku_Resource/kettei.mp3");
	sound.select =  LoadSoundMem("sugoroku_Resource/erabu.mp3");

}

bool CKey::Pushed(int KeyCode,SoundType soundType){

	if( CheckHitKey(KeyCode) && flag[KeyCode] != 1 && flag[KeyCode] != 2 ){
		flag[KeyCode] = 1;
	}

	if(!CheckHitKey(KeyCode) && flag[KeyCode]==1 ){
		flag[KeyCode] = 0;
		PlayPushSound(KeyCode,soundType);
		return true;
	}

	return false;
}

bool CKey::Hold(int KeyCode,int Interval,SoundType soundType){
	
	frame++;
	
	if(CheckHitKey(KeyCode) && flag[KeyCode]==0 ){
		flag[KeyCode] = 1;
		tempframe = frame;
	}

	if(flag[KeyCode] ==1 && frame-tempframe > HOLDTIME){
		flag[KeyCode] = 2;
		tempframe = frame;
	}

	if(!CheckHitKey(KeyCode) && flag[KeyCode]==2 ){
		flag[KeyCode] = 0;
	}

	if(flag[KeyCode]==2 && frame-tempframe > Interval){
		tempframe = frame;
		PlayPushSound(KeyCode,soundType);
		return true;
	}
	return false;
}

void CKey::PlayPushSound(int keyCode,int soundType){
	
	switch(soundType){
	case TITLE_SOUND:
		if(keyCode==KEY_INPUT_RETURN){
			PlaySoundMem(sound.decide,1);
		}
		if(keyCode==KEY_INPUT_UP || keyCode==KEY_INPUT_DOWN || 
			keyCode==KEY_INPUT_RIGHT || keyCode==KEY_INPUT_LEFT){
				PlaySoundMem(sound.select,1);
		}
		if(keyCode==KEY_INPUT_BACK){
			PlaySoundMem(sound.cancell,1);
		}
		break;
	case SUGOROKU_SOUND:
		break;
	case RESULT_SOUND:
		break;
	}

}