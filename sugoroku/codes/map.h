#pragma once

#include "DxLib.h"
#include "Suken.h"
#include"mouse.h"
#include"key.h"

class CMap{
	public:
		void Awake();
		void Draw();

		void DrawMini();//ミニマップ

		void Select();	
		bool EndSelect();

		void Init();//マップを読み込む

		void Look();//マップ見渡し
		void Back();//
		void SetScroll(int X , int Y);

		int GetPlaceType(int Num);
		int GetPlaceX(int Num);
		int GetPlaceY(int Num);
		int GetScrollChangeX();
		int GetScrollChangeY();
		int GetGoal();

	private:
		int mapNum;//選択したマップの番号

		int mapPic[10];	//マップの画像
		int mapdata[10];//マップデータ保存用

		int haikeiPic[10];
		int haikeiNum;
		
		struct{
			int R,G,B,A;
			int mapcolor;
		}Data[200][200];//マップチップ用
		
		int goal;

		int placeX[100],placeY[100];//マスの座標
		int placeType[100];	//マスの種類 GetColorで色の情報が入ってる	
		int placePic[100];//マスの画像　

		int scrollx,scrolly;//スクロール用

		int tempScrollx,tempScrolly;//スクロール一時保存

		bool ScrollCase;	//マップ見渡しか否か

		enum BottanName{
			UP,DOWN,ENTER,DRUG,MAX
		};

		CMouse MapMouse[MAX];

		CKey MapKey;
};