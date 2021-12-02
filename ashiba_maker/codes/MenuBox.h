#pragma once

#include"Utility"
#include<string>
#include"key.h"
typedef std::pair<int,int>P;

class CMenuBox{
	
public:
	CMenuBox(const char* ,const char*,int _x , int _y , int _cellX , int _cellY,int _cellXNum,int _cellYNum,int _color,int stringColor);
	~CMenuBox();

	void Selectable();
	void UnSelectable();

	void Draw();//Menuの呼び出し
	void Draw(int _x,int _y);
	void AddNewString(const char*);//枠内に表示する文字を追加する
	void AddNewString(const char* _s , int _x , int _y );

	void DeleteString();

	void NonActive(int _num);
	void Active(int _num);

	void ResetSpot();

	bool Selected();//どこかの項目が選ばれたときにtrueを返す
	P SelectSpot(); //現在選ばれている場所を返す
	std::string SelectingString();//現在選ばれている場所の文字を返す
private:
	int scene;

	void DrawFrame();  //枠線の描画
	void DrawFrame(int,int);  //枠線の描画
	bool Select();//項目の選択 選択が終わったらtrueを返す。
	
	int x,y;
	int cellX,cellY;		//ひとつのセルの大きさ
	int cellXNum,cellYNum;	//セルの数
	
	int color;				//枠線の色
	int activeColor;		//選択可能なときの文字の色
	int nonActiveColor;		//選択不可なときの文字の色

	std::string haikeiFile;	//背景画像の名前（仮）
	int haikeiGraph;				//背景画像(仮)

	std::string selectFile;
	int selectGraph;
	
	std::string str[100];	//枠内に表示する文字
	bool active[100];		//その文字が選択可能かどうか
	int strMax;				//文字の総数

	bool selectable;

	P selectSpot;//現在選択中の場所
};