#pragma once

#include"DxLib.h"
#include"Suken.h"

#include"mouse.h"
#include"key.h"

class CMenu{
public:
	void Awake();
	void Init(LoopCase NowCase);
	void Draw();
	void SubDraw(int RestPlace);

	void ResetButtonSwitch();

	void Select();

	int SelectedCase();

	bool Opened();
	bool Closed();

	LoopCase GetTempCase();
	int GetFrame();

private:
	int menuSelect;
	int menuGazou[10];

	int subMenuPic;
	int subMenuSelect;

	int selectSpotPic;

	int frame;
	int tempF;

	LoopCase tempCase;

	bool buttonSwitch;//メニューが開いていない（メニューを開くボタンがある）ならfalse

	int confirmPic;

	int buttonPic[2];

	CMouse MenuMouse[10];
	CKey MenuKey;
};