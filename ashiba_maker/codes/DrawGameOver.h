#pragma once
#include"mouse.h"
#include"General.h"

enum GameOverMenuState {
	NO_ACTION,
	RETRY,
	RETURN_TO_TITLE
};


class CGameOverMenu {
public:
	CGameOverMenu();
	GameOverMenuState Update();
private:
	int x, y;
	CMouse mouse[2];
	int gameOverGraph[3];
};