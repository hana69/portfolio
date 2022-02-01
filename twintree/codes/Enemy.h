#pragma once

#include"Suken.h"
#include"DxLib.h"
#include"SkillManager.h"

class CEnemy{
	public:
		CEnemy();
		CEnemy(CEnemy&);
		CEnemy(FILE* _enemyData,const char* _picName="");

		void Init();
		void TurnInit();//�^�[���J�n���̏�����

		void AddSkill(CSkill* _newSkill,int _per);
		CSkill* UseSkill();

		bool NowSkillUseAble();
		
		void SetPosition(int _p);

		int GetExp();
		std::string GetName();
		bool GetLive();

		int GetRank(Parameter);
		int GetStatus(Parameter);
		int RealParameter(Parameter);

		CSkill::SkillResult GiveBuff(int _num,Parameter);
		void ConsumeP();

		int GetHP();
		int GetSP();

		void Draw();//position�͉E���牽�Ԗڂ���\���@�ő�T

		void GiveDamage( CSkill* _givenSkill,int _atk);
		int GetDamage();
		void DrawDamage();
		void DrawBstDamage();

		CSkill::SkillResult GiveRecover(CSkill*,int m_a);
		CSkill::SkillResult GiveBst(CSkill*);
		CSkill::SkillResult GiveBstRecover(CSkill*);

		BadStatus NowBst();
		bool BstRecover();
		BadStatus RecoveredBst();
		void BstEffect();

		bool AtackGiven(CSkill*);//�U���Z���O�ꂽ��false
	private:
		void DrawHPGage();

		int picture;
		std::string picName;

		std::string name;
		
		int level;
		int hp;
		int hpMax;
		int sp;
		int spMax;
		int status[SPEED+1];
		int exp;

		int position;
		
		int rank[SPEED+1];//�o�t�̂�����
		 
		BadStatus nowBst;//���݂̏�Ԉُ�
		int bstTurn;//��Ԉُ킪�p�����Ă���^�[����
		BadStatus recoveredBst;//����������Ԉُ�

		bool live;
		bool thisTurnDeath;

		int damage;
		int recoverAmount;//�񕜗�

		int per[ELEMENT_MAX];//��������,�_���[�W���󂯂銄��
		int bstPer[MAHUU+1];//��Ԉُ�ɂȂ�m��

		bool damageGiven;//�����ւ̍U�����������Ă�����true
		
		int usePercent[10];//���ꂼ��̃X�L�����g�p����\��
		CSkillManager Skills;
		int usedSkillNum;
	};

static FILE* enemy_fp=fopen( "noseResource/enemyData.txt" , "r" );
//��main��awake��fclose

static CEnemy
	REDRAMP(enemy_fp),
	YELLOWRAMP(enemy_fp),
	BLUERAMP(enemy_fp),
	PURPLERAMP(enemy_fp),
	BLACK_FIRERAMP(enemy_fp),
	WHITE_THUNDERRAMP(enemy_fp);

