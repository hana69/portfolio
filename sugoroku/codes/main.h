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
	int time; //frameを一時的に保存し，キー操作の間隔を確保
	int tempcase;//メニューを開く時に直前のcaseを一時的に保存
	int enterTime;//デバッグ用に変数化中　最終的には定数

	int whereToReturn;//1：タイトル　２：メニュー

	int optionWhereReturn;

	int buttonPic[2];//右下のボタンの画像　０：押してないとき　１：押してる時

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