#pragma once


#include"Suken.h"
#include"DxLib.h"
#include"MenuBox.h"

class CArmManager{
	class CArm{
	public:
		CArm();
		CArm(FILE* _armData);
		void DrawInfo();
	
		std::string GetName();
		int GetAtk();
		int GetDff();
		Element GetElement();

		void operator = (CArm* _arm);
		std::string name;
		int atk;
		int dff;
		Element element;
	};
	FILE* arm_fp;
	
	CArm FIRST_WOOD,
		 JAPANESE_DICTIONARY,
		 HONOO_NO_KEN;

public:

	CArmManager();

	void Awake();

	void AddArm(CArm* _newArm);					//新しい武器をhavingArmに追加する
	void DeleteArm(int _x,int _y);	//指定した位置のhavingArmを消す

	bool ReturnSelected();//「もどる」が選択された時にtrue
	
	void Draw();		//装備の一覧を表示する
	void DrawInfo(int _x,int _y);//指定された箇所の装備の情報を表示する
	void DrawInfo();	//現在選択中の装備の情報を表示する
private:

	CArm havingArm[3][10];	//このクラスに含まれる装備の情報
	int havingArmNum;		//含まれている装備の数

	int armInfoPic;

	CMenuBox ArmMenu;		//武器一覧を表示させるためのMenu

};