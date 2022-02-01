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

	void AddArm(CArm* _newArm);					//�V���������havingArm�ɒǉ�����
	void DeleteArm(int _x,int _y);	//�w�肵���ʒu��havingArm������

	bool ReturnSelected();//�u���ǂ�v���I�����ꂽ����true
	
	void Draw();		//�����̈ꗗ��\������
	void DrawInfo(int _x,int _y);//�w�肳�ꂽ�ӏ��̑����̏���\������
	void DrawInfo();	//���ݑI�𒆂̑����̏���\������
private:

	CArm havingArm[3][10];	//���̃N���X�Ɋ܂܂�鑕���̏��
	int havingArmNum;		//�܂܂�Ă��鑕���̐�

	int armInfoPic;

	CMenuBox ArmMenu;		//����ꗗ��\�������邽�߂�Menu

};