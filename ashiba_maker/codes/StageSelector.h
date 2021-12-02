#pragma once
#include"mouse.h"
class StageSelector {
public:
	StageSelector(int _finalStageNum);
	void Update();
	bool SelectFinished();
	int SelectedStage() {
		return selectingStageNum;
	};
private:
	CMouse mouse;
	int ver2Graph;
	void SelectStageByMouse();
	int selectingStageNum;
	int nowSelectableStageNumMax;
};
