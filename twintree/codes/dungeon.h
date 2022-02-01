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

	bool Exit();//�_���W��������o���Ƃ���true

	void GetName();

private:
	std::string name;

	int floor;//�K�w��
protected:
	virtual void Explore(); //�I������I�񂾎��̏���

	virtual void SetEnemyNum();//�G�̐������肷��֐�
	virtual void SetEnemyType();//�o�Ă���G�̎�ނ����肷��֐�

	CBattle Battle;
	CMenuBox Road;
	CMessageBox Message;
	bool exitFlag;//�o�悤�Ƃ�����true
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
	void Explore();//����I�񂾎��ɉ����N���邩���肷��
	void SetExploreResult();//���肳�ꂽ���e�����ۂɔ��f������

	void SetEnemyNum();
	void SetEnemyType();

	int frame;
	int tempFrame;
};