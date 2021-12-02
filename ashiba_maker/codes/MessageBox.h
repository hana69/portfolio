#pragma once

#include "Dxlib.h"
#include "General.h"
#include <string>
 
class CMessageBox{
public:
	CMessageBox(int _x , int _y , int _width , int _height);

	void Draw();
	void Call(const char*);//すでにある文章を消去してから表示
	void Add(const char*);//すでにある文章に追加する形で表示
	void Delete();//文章を消去

	void StartNewLine();//改行
	
	void SetLimitX(int _x);
	void SetLimitY(int _y);

private:
	bool active;
	
	std::string message[100];

	int limitX,limitY;

	int lineNum;

	int x,y;
	int width,height;
	
};