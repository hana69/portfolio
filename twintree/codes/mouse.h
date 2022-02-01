#pragma once

#include"Dxlib.h"
#include "Suken.h"

class CMouse{
public:
	CMouse(int X1,int Y1,int X2,int Y2);//コンストラクタで範囲の指定を行う

	bool LeftReleased();
	bool RightReleased();

	void SetTemp();

	int GetChangeX();
	int GetChangeY();
	bool GetFlag();

private:
	bool Insided();

	bool flag;
	bool rightFlag;

	int x,y;

	int tempX,tempY;

	int rangeX1,rangeX2,rangeY1,rangeY2;

};