#pragma once
#include"mouse.h"
#include"General.h"

enum GameClearMenuState {
	CLEARED_NO_ACTION,
	NEXT_STAGE,
	CLEARED_RETURN_TO_TITLE
};


class CGameClearMenu {
public:
	CGameClearMenu();
	GameClearMenuState Update();
private:
	int x, y;
	CMouse mouse[2];
	int gameClearGraph[3];
};
