#pragma once
#include"DxLib.h"
#include"Suken.h"
#include"Key.h"
class CTitle{
public:
	CTitle();
	enum Scene{
		TITLE,
		HTP
	}scene;

	void Awake();
	
	void Draw();
	bool GetEnd();
private :
	void TitleDraw();
	void HTPDraw();

	int titleGraph[2];
	int haikeiPic;
	

	bool end;
};