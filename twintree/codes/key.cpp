#include"key.h"

void CKey::Awake(){
	
	for(int i=0;i<1000;i++){
		flag[i] = 0;
		frame[i] = 0;
	}

	tempframe=0;

	sound.cancell = LoadSoundMem("nosegazou/modoru.mp3");
	sound.decide =  LoadSoundMem("nosegazou/kettei.mp3");
	sound.select =  LoadSoundMem("nosegazou/erabu.mp3");

}
bool CKey::Pushing(int _keyCode){
	return CheckHitKey(_keyCode);
}
bool CKey::Pushed(int _keyCode , bool _soundFlag){

	if( CheckHitKey(_keyCode) && flag[_keyCode] != 1 && flag[_keyCode] != 2 ){
		flag[_keyCode] = 1;
	}

	if(!CheckHitKey(_keyCode) && flag[_keyCode]==1 ){
		flag[_keyCode] = 0;
		if(_soundFlag == true){
			PlayReleaseSound(_keyCode);
		}
		return true;
	}

	return false;
}

bool CKey::Hold(int _keyCode,int _interval,bool soundFlag){

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
		PlayReleaseSound(_keyCode);
		return true;
	}
	return false;
}

void CKey::PlayReleaseSound(int _keyCode){
	
	if(_keyCode == KEYNAME.ENTER){
		PlaySoundMem(sound.decide , DX_PLAYTYPE_BACK);
	}else 
	if( _keyCode == KEYNAME.UP		||
		_keyCode == KEYNAME.DOWN	|| 
		_keyCode == KEYNAME.LEFT	|| 
		_keyCode == KEYNAME.RIGHT
	){
		PlaySoundMem(sound.select , DX_PLAYTYPE_BACK);
	}

	if(_keyCode==KEYNAME.BACK){
		PlaySoundMem(sound.cancell , DX_PLAYTYPE_BACK);
	}

}