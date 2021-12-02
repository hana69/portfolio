#include"MPgage.h"
#include"DxLib.h"
#include"General.h"

MPGage::MPGage(int _x, int _y)
	:x(_x), y(_y),
	MaxPoint(50)
{}

void MPGage::Update(int _nowPoint,bool _pushing, ScaffoldType _type) {
	DrawBox(x, y-300, x + 30, y, BLACK, true);
	DrawBox(x, y - _nowPoint * 6, x + 30, y, GREEN, true);
	
	if (_pushing) {
		DrawBox(x, y - _nowPoint * 6, x + 30, min(y - _nowPoint * 6 + scaffoldCost[(unsigned)_type]*6,y), RED, true);

	}

	DrawBox(x, y - 300, x + 30, y, WHITE, false);
}