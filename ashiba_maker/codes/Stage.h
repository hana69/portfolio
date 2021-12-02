#pragma once
class CActionField;
class CScaffoldMaker;

class Stage{
public:
	Stage(int _stageNum,int _finalStageNum);
	~Stage();
	void Update();
	bool SelectedReturnTitle();
	bool SelectedGoToNextStage();
private:
	void Scroll();
	void DrawBack(int rightEdge);
	int scroll;
	int backGraph;
	CActionField *field;
	CScaffoldMaker *maker;
};
