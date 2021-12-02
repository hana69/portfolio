#include"key.h"

void CKey::Awake(){
	
	for(int i=0;i<1000;i++){
		flag[i] = 0;
		frame[i] = 0;
	}

	tempframe=0;

	/*sound.cancell = LoadSoundMem("noseResource/modoru.mp3");
	sound.decide =  LoadSoundMem("noseResource/kettei.mp3");
	sound.select =  LoadSoundMem("noseResource/erabu.mp3");*/

}
bool CKey::Pushing(int _keyCode){
	return CheckHitKey(_keyCode);
}
bool CKey::Pushed(int _keyCode , SoundType _soundType){

	if( CheckHitKey(_keyCode) && flag[_keyCode] != 1 && flag[_keyCode] != 2 ){
		flag[_keyCode] = 1;
	}

	if(!CheckHitKey(_keyCode) && flag[_keyCode]==1 ){
		flag[_keyCode] = 0;
		if(_soundType != NOT_PLAY){
			PlayReleaseSound(_soundType);
		}
		return true;
	}

	return false;
}

bool CKey::Hold(int _keyCode,int _interval,SoundType _soundType){

	frame[_keyCode]++;
	
	if(CheckHitKey(_keyCode) && flag[_keyCode]==0 ){
		flag[_keyCode] = 1;
		tempframe = frame[_keyCode];
	}

	if(flag[_keyCode] ==1 && frame[_keyCode]-tempframe > _interval*10){
		flag[_keyCode] = 2;
		tempframe = frame[_keyCode];
	}

	if( !CheckHitKey(_keyCode) && flag[_keyCode]!=0 ){
		flag[_keyCode] = 0;
	}

	if(flag[_keyCode]==2 && frame[_keyCode]-tempframe > _interval){
		tempframe = frame[_keyCode];
		PlayReleaseSound(_soundType);
		return true;
	}
	return false;
}

void CKey::PlayReleaseSound(SoundType _soundType){
	
	switch(_soundType){
	case DECIDE_SOUND:
		PlaySoundMem(sound.decide,DX_PLAYTYPE_BACK);
		break;
	case BACK_SOUND:
		PlaySoundMem(sound.cancell,DX_PLAYTYPE_BACK);
		break;
	case SELECT_SOUND:
		PlaySoundMem(sound.select,DX_PLAYTYPE_BACK);

		break;
	}

}