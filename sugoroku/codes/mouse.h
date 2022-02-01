#pragma once

#include "DxLib.h"
#include "Suken.h"

class CMouse{
public:
	void SetFlag();
	void SetRightFlag();

	void Awake(int X1,int Y1,int X2,int Y2);

	bool Insided();

	void SetTemp();

	int GetChangeX();
	int GetChangeY();

	bool GetFlag();

	bool Pushed();
	bool Released();

	bool RightReleased();

	bool RightPushed();

private:
	bool flag;

	bool rightFlag;

	int x,y;

	int tempX,tempY;

	int rangeX1,rangeX2,rangeY1,rangeY2;

};