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

	bool buttonSwitch;//���j���[���J���Ă��Ȃ��i���j���[���J���{�^��������j�Ȃ�false

	int confirmPic;

	int buttonPic[2];

	CMouse MenuMouse[10];
	CKey MenuKey;
};