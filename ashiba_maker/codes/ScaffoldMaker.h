#pragma once
#include"Scaffold.h"
#include"mouse.h"

///////マウスドラッグ時の足場描画に使用///////////
static int PlusMinus(int _x) {
	if (_x < 0) {
		return -1;
	}
	else if (_x == 0) {
		return 0;
	}
	else {
		return 1;
	}
};
///////////////////////////////////////////////

class MPGage;

class CSelectableObj {
public:
	CSelectableObj();
	void SetType(ScaffoldType _type) { type = _type; };//配列のコンストラクタが呼び出せないので応急処置
	void Draw(int _costNum);
	void DrawSelecting();
	void SetPosition(int, int);
	void Select(ScaffoldType*, int _point);
	ScaffoldType Type() { return type; };
private:
	static int selecting, pointing;
	ScaffoldType type;
	int x, y;
	CMouse Mouse;
};

class CScaffoldSelector {
public:
	CScaffoldSelector(int _x1, int _y1, int _x2, int _y2);
	void Update(int _point,int _needPoint);
	ScaffoldType SelectingType() { return selectingType; };
	
private:
	
	void Draw(int _point,int _needPoint);

	int x1, y1, x2, y2;
	bool init;//最初はfalse,Init呼出し後true
	ScaffoldType selectingType;
	
	CSelectableObj selectableObj[4];
};

class CScaffoldMaker {
public:
	CScaffoldMaker();
	~CScaffoldMaker();
	void Update();
	void OnlyDraw();
	void AddCoin();

	void Reset();

	bool DrawFinished();
	ScaffoldType DrawnType() { return drawnType; };
	int DrawnSpotX() { return drawnSpotX; };
	int DrawnSpotY() { return drawnSpotY; };
	//NecessaryInfoToMake DrawnScaffold() { return writingObj; };
private:
	void Draw();
	ScaffoldType drawnType;
	int drawnSpotX,
		drawnSpotY;

	CScaffoldSelector selector;
	MPGage* mpGage;

	const int x1, x2, y1, y2;
	const int drawAreaGraph;

	bool drawFinished;

	int writingWidth;
	bool writed;

	int point;
	int needPoint;

	CMouse Mouse;
};

