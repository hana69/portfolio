#pragma once

#include "DxLib.h"
#include "Suken.h"

#include "dice.h"
#include "map.h"
#include "player.h"
#include "title.h"
#include "text.h"
#include "menu.h"
#include"mouse.h"
#include"key.h"

class CMain{
public:
	void GameLoop();
	void Awake();
private:
	void Loop();
	void MenuOpen();
	
	void ChangeCase();
	void BackCase();

	void DrawMiniMap();

	void LoopAwake();

	int SelectMovement();
	int selectSpot;
	int selectPic;
	int selectSpotPic;

	SelectCase selectCase;//
	LoopCase loopCase;//
	MenuCase menuCase;//
	HowToCase howtoCase;
	ResultCase resultCase;
	OptionCase optionCase;

	int frame;//
	int time; //frame���ꎞ�I�ɕۑ����C�L�[����̊Ԋu���m��
	int tempcase;//���j���[���J�����ɒ��O��case���ꎞ�I�ɕۑ�
	int enterTime;//�f�o�b�O�p�ɕϐ������@�ŏI�I�ɂ͒萔

	int whereToReturn;//1�F�^�C�g���@�Q�F���j���[

	int optionWhereReturn;

	int buttonPic[2];//�E���̃{�^���̉摜�@�O�F�����ĂȂ��Ƃ��@�P�F�����Ă鎞

	int howToPic[5];

	int optionPic;
	int selectingOptionSpot;

	bool pointBattle;

	int bgmNum;

	int goalPic;
	int resultPic;

	int loopBGM[5];
	struct{
		int cancel;
		int dice;
		int clear;
	}sound;
	
	int maplookPic;

	CDice Dice;
	CMap Map;
	CTitle Title;
	CTxt Txt;
	CMenu Menu;
	CPlayerManager Player;
	CMouse Mouse[20];
	CKey Key;
};