#include"DrawGameOver.h"

CGameOverMenu::CGameOverMenu()
	:x(WINDOW_WIDTH / 2 - 100), y(WINDOW_HEIGHT / 2 - 75)
{
	mouse[0].SetRange(x + 22, y + 123, x + 69, y + 134);
	mouse[1].SetRange(x + 111, y + 124, x + 193, y + 134);
	gameOverGraph[0] = LoadGraph("noseResource/GameOver.png");
	gameOverGraph[1] = LoadGraph("noseResource/GameOver_Restart.png");
	gameOverGraph[2] = LoadGraph("noseResource/GameOver_Title.png");
};

GameOverMenuState CGameOverMenu::Update() {
	for (int i = 0; i < 2; i++) {
		if (mouse[i].Insided()) {
			DrawGraph(x, y, gameOverGraph[i+1], true);
			break;
		}
		else {
			DrawGraph(x, y, gameOverGraph[0], true);
		}
	}

	if (mouse[0].Insided()) {
		if (mouse[0].LeftPushed()) {
			return RETRY;
		}
	}
	else if (mouse[1].Insided()) {
		if (mouse[1].LeftPushed()) {
			return RETURN_TO_TITLE;
		}
	}
	return NO_ACTION;
}