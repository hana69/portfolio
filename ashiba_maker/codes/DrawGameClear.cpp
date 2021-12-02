#include"DrawGameClear.h"

CGameClearMenu::CGameClearMenu()
	:x(WINDOW_WIDTH / 2 - 100), y(WINDOW_HEIGHT / 2 - 75)
{
	mouse[0].SetRange(x + 20, y + 124, x + 89, y + 134);
	mouse[1].SetRange(x + 111, y + 124, x + 193, y + 134);
	gameClearGraph[0] = LoadGraph("noseResource/GameClear.png");
	gameClearGraph[1] = LoadGraph("noseResource/GameClear_NextStage.png");
	gameClearGraph[2] = LoadGraph("noseResource/GameClear_ReturnToTitle.png");
};

GameClearMenuState CGameClearMenu::Update() {
	for (int i = 0; i < 2; i++) {
		if (mouse[i].Insided()) {
			DrawGraph(x, y, gameClearGraph[i + 1], true);
			break;
		}
		else {
			DrawGraph(x, y, gameClearGraph[0], true);
		}
	}
	if (mouse[0].Insided()) {
		if (mouse[0].LeftPushed()) {
			return NEXT_STAGE;
		}
	}
	else if (mouse[1].LeftPushed()) {
		if(mouse[1].Insided()) {
			return CLEARED_RETURN_TO_TITLE;
		}
	}
	return CLEARED_NO_ACTION;
}