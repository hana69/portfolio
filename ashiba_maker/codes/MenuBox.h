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

	void Draw();//Menu�̌Ăяo��
	void Draw(int _x,int _y);
	void AddNewString(const char*);//�g���ɕ\�����镶����ǉ�����
	void AddNewString(const char* _s , int _x , int _y );

	void DeleteString();

	void NonActive(int _num);
	void Active(int _num);

	void ResetSpot();

	bool Selected();//�ǂ����̍��ڂ��I�΂ꂽ�Ƃ���true��Ԃ�
	P SelectSpot(); //���ݑI�΂�Ă���ꏊ��Ԃ�
	std::string SelectingString();//���ݑI�΂�Ă���ꏊ�̕�����Ԃ�
private:
	int scene;

	void DrawFrame();  //�g���̕`��
	void DrawFrame(int,int);  //�g���̕`��
	bool Select();//���ڂ̑I�� �I�����I�������true��Ԃ��B
	
	int x,y;
	int cellX,cellY;		//�ЂƂ̃Z���̑傫��
	int cellXNum,cellYNum;	//�Z���̐�
	
	int color;				//�g���̐F
	int activeColor;		//�I���\�ȂƂ��̕����̐F
	int nonActiveColor;		//�I��s�ȂƂ��̕����̐F

	std::string haikeiFile;	//�w�i�摜�̖��O�i���j
	int haikeiGraph;				//�w�i�摜(��)

	std::string selectFile;
	int selectGraph;
	
	std::string str[100];	//�g���ɕ\�����镶��
	bool active[100];		//���̕������I���\���ǂ���
	int strMax;				//�����̑���

	bool selectable;

	P selectSpot;//���ݑI�𒆂̏ꏊ
};