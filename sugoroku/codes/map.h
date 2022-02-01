#pragma once

#include "DxLib.h"
#include "Suken.h"
#include"mouse.h"
#include"key.h"

class CMap{
	public:
		void Awake();
		void Draw();

		void DrawMini();//�~�j�}�b�v

		void Select();	
		bool EndSelect();

		void Init();//�}�b�v��ǂݍ���

		void Look();//�}�b�v���n��
		void Back();//
		void SetScroll(int X , int Y);

		int GetPlaceType(int Num);
		int GetPlaceX(int Num);
		int GetPlaceY(int Num);
		int GetScrollChangeX();
		int GetScrollChangeY();
		int GetGoal();

	private:
		int mapNum;//�I�������}�b�v�̔ԍ�

		int mapPic[10];	//�}�b�v�̉摜
		int mapdata[10];//�}�b�v�f�[�^�ۑ��p

		int haikeiPic[10];
		int haikeiNum;
		
		struct{
			int R,G,B,A;
			int mapcolor;
		}Data[200][200];//�}�b�v�`�b�v�p
		
		int goal;

		int placeX[100],placeY[100];//�}�X�̍��W
		int placeType[100];	//�}�X�̎�� GetColor�ŐF�̏�񂪓����Ă�	
		int placePic[100];//�}�X�̉摜�@

		int scrollx,scrolly;//�X�N���[���p

		int tempScrollx,tempScrolly;//�X�N���[���ꎞ�ۑ�

		bool ScrollCase;	//�}�b�v���n�����ۂ�

		enum BottanName{
			UP,DOWN,ENTER,DRUG,MAX
		};

		CMouse MapMouse[MAX];

		CKey MapKey;
};