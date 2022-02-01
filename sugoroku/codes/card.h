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
	
	int Get(CardType NewCard,int turn);//新しくカードをゲットする
	
	bool Selected(int turn);//カードを選び終わった時にtrue

	int ConfirmIsEnded(ConfirmCase Case);

	void Draw(int player,LoopCase loopCase=EFFECT);

	string GetName(CardType type);

	CardType GetSelectingCardType();

	CCard();
private:
	//class CRelease{
	//public:
	//	int Confirm();//カードを捨てるかどうか確認
	//	
	//	bool Selected(CCard &Card_p);//enterか左クリックでtrue
	//	
	//	int Case;

	//	int confirmPic[2];//確認する時表示する画像

	//	CKey RKey;
	//} Release;

	bool endFlag;//Getで使用中 Getし終わったらtrue
	bool changeFlag;//Getで使用中　「いれかえる」選択後true

	struct{
		int picture;
		int selectSpotPic;//現在の選択場所を示すための画像　青緑（半透過）の長方形
		string selectSpot;
		CMouse Mouse[2];
	}confirm[CONFIRMCASE_MAX];

	void Effect(CardType CardType);

	CardType cardType[SPOTMAX];//[場所]にあるカードの種類

	int selectSpot;//現在選択されている場所
	int selectSpotPic;

	CardType usedCardType;
	CardType newCardType;
	CardType releasedCardType;
	CardType tempType;//cardTypeが書き換えられる前の情報を一時的に保存

	CKey CardKey;
	CMouse CardMouse[SPOTMAX];
};