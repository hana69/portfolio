#include<DxLib.h>
#include"StageSelector.h"
#include"General.h"

StageSelector::StageSelector(int _finalStageNum)
	:selectingStageNum(TUTORIAL), 
	nowSelectableStageNumMax(_finalStageNum),
	ver2Graph(LoadGraph("noseResource/ver2.png"))
{
	SetFontSize(68);
	ChangeFontType(DX_FONTTYPE_ANTIALIASING_4X4);
}
void StageSelector::Update() {
	SelectStageByMouse();
	static int explainGraph = LoadGraph("noseResource/title_explain.png");
	DrawGraph(0, 0, explainGraph, true);
	DrawGraph(736, 364, ver2Graph, true);
	/////////////////élã˜Ç…ë´èÍÇÃâÊëúÇï\é¶/////////////////////////////////////
	DrawGraph(0, 0, scaffoldGraph(ScaffoldType::NORMAL), true);
	DrawGraph(WINDOW_WIDTH - 50, 0, scaffoldGraph(ScaffoldType::SPEED_UP), true);
	DrawGraph(0, WINDOW_HEIGHT - 50, scaffoldGraph(ScaffoldType::SPEED_DOWN), true);
	DrawGraph(WINDOW_WIDTH - 50, WINDOW_HEIGHT - 50, scaffoldGraph(ScaffoldType::JUMP), true);
	//////////////////////////////////////////////////////////////////////

	DrawFormatString(580, 510, RED, "%d", selectingStageNum);
	if (selectingStageNum == TUTORIAL) {
		static int tutorial_graph = LoadGraph("noseResource/tutorial_string.png");
		DrawGraph(WINDOW_WIDTH / 2 - 215, 580, tutorial_graph, true);
	}
}

bool StageSelector::SelectFinished() {
	return mouse.LeftReleased();
}

void StageSelector::SelectStageByMouse() {
	static int noWheelingGraph = LoadGraph("noseResource/title_NoAction.png"),
		wheelingGraph = LoadGraph("noseResource/title_Wheeled.png");

	int wheelNum = mouse.Wheel();

	if (wheelNum != 0) {
		DrawGraph(0, 0, wheelingGraph, true);
	}
	else {
		DrawGraph(0, 0, noWheelingGraph, true);
	}

	if (wheelNum < 0) {
		selectingStageNum--;
		if (selectingStageNum < 0) {
			selectingStageNum = 0;
		}
	}
	else if (wheelNum > 0) {
		selectingStageNum++;
		if (selectingStageNum > nowSelectableStageNumMax) {
			selectingStageNum = nowSelectableStageNumMax;
		}
	}
}

