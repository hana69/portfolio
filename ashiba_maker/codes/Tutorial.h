#pragma once

class CActionField;
class CScaffoldMaker;

class Tutorial {
public:
	Tutorial();
	~Tutorial();
	void Start();
	void Update();
	bool SelectedReturnTitle();
	bool SelectedNextStage();
	bool Explaining(){return explaining;}
	enum class ExplainState{
		FIRST,
		ROAD_IS_BROKEN,
		LETS_CLICK,
		MP_DECREASE,
		SCROLL,
		DISCOVER_COIN,
		MP_GAIN,
		HOLE_AGAIN,
		BUT,
		GO_THROUH_SINGLE_HOLE,
		HAVETO_MAKE,
		WALL_AND_SINGLE_HOLE,
		FALL,
		FILL_SINGLE_HOLE,
		STILL_THERE_IS_WALL,
		HAVETO_ERASE,
		FOUND_STEP,
		VARIOUS_SCAFFOLD,
		CLICK_TO_SELECT,
		SELECT_JUMP,
		HAVETO_JUMP,
		GOAL,
		MENU
	} State() { return state; };
private:
	void StateFunc();
	bool drawFlag;
	void DrawBack();
	void Scroll();
	int scroll;

	CActionField* field;
	CScaffoldMaker* maker;
	int backGraph;

	ExplainState state;

	bool explaining;
	bool meMoveFlag;
	bool scrollFlag;

	static int graph[30];
};