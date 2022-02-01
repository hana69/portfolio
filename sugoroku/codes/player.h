#pragma once

#include "DxLib.h"
#include "Suken.h"
#include "mouse.h"
#include "player.h"
#include "key.h"
#include"card.h"

class CPlayer{
	public:

		void Move( int Num , int Frame , int Time ,int Max, int debugmode);
		void Draw( int scroolX,int scrollY);
		void DrawMini(int frame);
		void Effect(int type,bool piValid , int time,int turn);

		void JudgeGoal(int goal);

		void GetAndReleaseCard(CardType Type,int time,int turn);

		bool PiGot();
		bool PiLost();

		int place;//���}�X�ڂɂ��邩
		int x;//�v���C���[�̂����W
		int y;//�v���C���[�̂����W
		Status status;//�v���C���[�̏�ԁi���x�݂Ȃ�)

		int cardGetType;//�e�L�X�g��\�������邽�߁A�J�[�h�̎�ɓ������ۑ����Ă���
		bool effectEnded;
		int tempTime;

		int playerPic;//�v���C���[�̉摜
		int miniPic[2];//�~�j�}�b�v�ɕ\������摜

		int overNum;//�S�[���𒴂������̖ڂ̐�
		bool overFlag;//���̃^�[���ɃS�[���𒴂���Ȃ�true
		bool returnFlag;//�߂��Ă���Ȃ�true

		bool moveEndFlag;

		bool goaled;

		bool piGetFlag;
		bool piLostFlag;

		CCard Card;

		int ranking;

		int cardUseCount;
		int returnStartCount;
		int moveNumCount;

		int bonusPoint[5];
		int totalPoint;

		struct{
			int move;
			int go_three;
			int return_three;
			int stop;
			int return_start;
			int yasumi;
		}sound;
	private:
		
};

class CPlayerManager{
	public:	
		int GetPiNum();

		void Awake();

		void Init(int firatX,int firstY);

		void SetPlace(int Num,int X, int Y );

		void CardEffect(CardType Type,int frame,LoopCase Case,int goal,int debugmode);//�J�[�h�̌��ʂ̓v���C���[�ɔ��f�����̂�playermanager�ŊǗ�

		void PlayerSelect();//�I�΂ꂽ�v���C���[��select.player�ɕۑ�

		void SetSpotNum(int turnPlayer);//���̃v���C���[��I�ԂƂ��ɁA�����������R�l�ɂ���

		struct{
			int player;//�I�΂ꂽ�v���C���[
			int spot;//���I��ł���ꏊ
			bool endFlag;//�I�����I����Ă����true
			int selectSpotPic;//�I���ꏊ�������΂̎l�p�`
			int spotNum[10];//���̏ꏊ�ɂǂ̃v���C���[�����蓖�Ă��Ă��邩�@���Ƃ��΃v���C���[�P�����̃v���C���[��I�ԏꍇ[0]=2,[1]=3,[2]=4�ƂȂ�
			CKey Key;
			CMouse Mouse[10];
		}select;

		bool cardSelectedFlag;

		int EndNumSelect();

		void SetTurn();
	
		bool CardIsUsed();

		void Manage(LoopCase Case , int PlaceType , int frame,int time,int DiceNum,int PlaceMax,int debugmode);
		void Draw(int ScrollX , int ScrollY );
		void DrawMini(int ScrollX , int ScrollY,int frame);
		void PlayNumSelect(int frame);
		
		void CardDraw();

		int GetTurn();
		int GetX(int Num);
		int GetY(int Num);
		int GetStatus(int Num);
		int GetPlace(int Num);
		int GetCardEffect();

		bool Get_go_or_return();

		CardType GetUsedCardNum();

		bool CardConfirm();

		bool EffectEnded();

		bool Goaled();

		void DrawNowPlace(int goal);

		void SetRanking(int goal);
		void DrawRanking(int time);

	private:
		
		CardType stoleCard;

		int turn;//�ǂ̃v���C���[���s�����邩
		int playerMax;//�v���C�l��
		int interval;

		void Loop();

		void SetBonusPoint();

		bool cardUsedFlag;//���̃^�[���ɃJ�[�h���g���Ă�����true
		bool cardConfirm;//�J�[�h���g�����̊m�F����true
		bool cardEffect;//�J�[�h�̌��ʂ𔽉f���Ă���Ԃ�true

		int cursorPic;//�v���C���[�̏�ɂ���O�p�̉摜

		bool go_or_return;//10�i�ށH�J�[�h�Ői�񂾂��߂��������L�������Ă��� �i�񂾂�true�@((Txt�ŕ������������߂ɕK�v
		bool canUse;//�J�[�h�������邩�ǂ����@false�Ȃ�g���Ȃ� �ޓ��J�[�h�œ��ރJ�[�h���Ȃ��ꍇ�ȂǂɎg�p

		int temptime;

		int tempRank;

		bool piValid;
		int nowPiRank;

		int drawingLine;
		int nowRanking;
		bool rankPlusFlag;
		
		int resultPic[4];

		int pointPlusSound;

		CMouse PMouse[4];
		CPlayer player[4];
		CKey PKey;
};