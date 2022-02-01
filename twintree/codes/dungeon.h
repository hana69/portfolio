#pragma once

#include"Suken.h"
#include"DxLib.h"

#include"MenuBox.h"
#include"MessageBox.h"

#include "ArmManager.h"
#include "Battle.h"


class CDungeon{
public:
	CDungeon(const char* _name,int _floor);

	virtual void Main();

	bool Exit();//ダンジョンから出たときにtrue

	void GetName();

private:
	std::string name;

	int floor;//階層数
protected:
	virtual void Explore(); //選択肢を選んだ時の処理

	virtual void SetEnemyNum();//敵の数を決定する関数
	virtual void SetEnemyType();//出てくる敵の種類を決定する関数

	CBattle Battle;
	CMenuBox Road;
	CMessageBox Message;
	bool exitFlag;//出ようとしたらtrue
	int enemyNum;
};

class YAN_VILLAGE :public CDungeon{
public:
	YAN_VILLAGE(const char* _name,int _floor);
	void Main();
private:
	enum{
		SELECT_ROAD,
		BATTLE,
		GET_ITEM
	}scene;

	enum{
		ENEMY,
		ITEM,
		NOTHING,
	}explore_result;
	void Explore();//道を選んだ時に何が起こるか決定する
	void SetExploreResult();//決定された内容を実際に反映させる

	void SetEnemyNum();
	void SetEnemyType();

	int frame;
	int tempFrame;
};