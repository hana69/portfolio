#include"scaffold.h"

//////////////////CScaffold//////////////////////////
////////コンストラクタ//////////
CScaffold::CScaffold() 
	:type(ScaffoldType::NORMAL),x(0),y(0)
{}

CScaffold::CScaffold(ScaffoldType _type,int _xPlace,int _yPlace)
	:type(_type),x(_xPlace),y(_yPlace)
{}
///////public関数/////////////
void CScaffold::Draw(int _scroll) {
	if (0 < x*50+50-_scroll && x*50-_scroll < WINDOW_WIDTH) {
		DrawGraph(x * 50 - _scroll, y * 50, scaffoldGraph(type), true);
	}
}

void CScaffold::Move(int _limit,bool underSea) {
	if (underSea) {
		y -= 0.1;
	}
	else {
		y -= 0.2;
	}
	if (y < _limit && type!=ScaffoldType::ERASER) {
		y = _limit;
	}
}
//////private関数/////////////

