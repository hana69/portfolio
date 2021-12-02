#pragma once
#include<stdio.h>
class StageSelector;
class Stage;
class Tutorial;

class StageManager {
public:
	StageManager();
	~StageManager();
	void UpDate();
private:
	int finalStageNum;
	FILE* fp;
	StageSelector* stageSelector;
	Stage* stage;
	Tutorial* tutorial;
	bool isTutorial;
	bool stageSelecting;
	int nowPlayingStageNum;
};

//class CMain_S{
//public:
//	CMain_S();
//	void Start(int _stageNum);
//	void Update();
//	bool OperatedReturnTitle() { return returnTitleFlag; };
//private:
//	CActionField* field;
//	CScaffoldMaker scaffoldDrawer;
//	int stageNum;
//
//	CTutorial* tutorial;
//	
//	bool returnTitleFlag;
//
//	int scroll;
//	void Scroll();
//};




