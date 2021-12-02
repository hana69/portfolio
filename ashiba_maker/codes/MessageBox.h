#pragma once

#include "Dxlib.h"
#include "General.h"
#include <string>
 
class CMessageBox{
public:
	CMessageBox(int _x , int _y , int _width , int _height);

	void Draw();
	void Call(const char*);//���łɂ��镶�͂��������Ă���\��
	void Add(const char*);//���łɂ��镶�͂ɒǉ�����`�ŕ\��
	void Delete();//���͂�����

	void StartNewLine();//���s
	
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