#pragma once

#include"DxLib.h"
#include"Suken.h"
#include<string>
#include"key.h"
#include"mouse.h"

using namespace std;

class CCard{
public:
	void Awake();

	void Init();

	void SetUsedCardType();

	CardType NewCardType();
	CardType ReleasedCardType();

	void Effect();

	void Lost();

	bool PiCheck();
	bool EndFlag(){
		return endFlag;	
	};

	CardType UsedCardType();

	string NewCardName();
	string ReleaseCardName();

	CardType GetHavingCardType(int spot);
	
	int Get(CardType NewCard,int turn);//�V�����J�[�h���Q�b�g����
	
	bool Selected(int turn);//�J�[�h��I�яI���������true

	int ConfirmIsEnded(ConfirmCase Case);

	void Draw(int player,LoopCase loopCase=EFFECT);

	string GetName(CardType type);

	CardType GetSelectingCardType();

	CCard();
private:
	//class CRelease{
	//public:
	//	int Confirm();//�J�[�h���̂Ă邩�ǂ����m�F
	//	
	//	bool Selected(CCard &Card_p);//enter�����N���b�N��true
	//	
	//	int Case;

	//	int confirmPic[2];//�m�F���鎞�\������摜

	//	CKey RKey;
	//} Release;

	bool endFlag;//Get�Ŏg�p�� Get���I�������true
	bool changeFlag;//Get�Ŏg�p���@�u���ꂩ����v�I����true

	struct{
		int picture;
		int selectSpotPic;//���݂̑I���ꏊ���������߂̉摜�@�΁i�����߁j�̒����`
		string selectSpot;
		CMouse Mouse[2];
	}confirm[CONFIRMCASE_MAX];

	void Effect(CardType CardType);

	CardType cardType[SPOTMAX];//[�ꏊ]�ɂ���J�[�h�̎��

	int selectSpot;//���ݑI������Ă���ꏊ
	int selectSpotPic;

	CardType usedCardType;
	CardType newCardType;
	CardType releasedCardType;
	CardType tempType;//cardType��������������O�̏����ꎞ�I�ɕۑ�

	CKey CardKey;
	CMouse CardMouse[SPOTMAX];
};