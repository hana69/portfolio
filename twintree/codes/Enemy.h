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
		void TurnInit();//ターン開始時の初期化

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

		void Draw();//positionは右から何番目かを表す　最大５

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

		bool AtackGiven(CSkill*);//攻撃技が外れたらfalse
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
		
		int rank[SPEED+1];//バフのかかり具合
		 
		BadStatus nowBst;//現在の状態異常
		int bstTurn;//状態異常が継続しているターン数
		BadStatus recoveredBst;//今治った状態異常

		bool live;
		bool thisTurnDeath;

		int damage;
		int recoverAmount;//回復量

		int per[ELEMENT_MAX];//属性毎の,ダメージを受ける割合
		int bstPer[MAHUU+1];//状態異常になる確率

		bool damageGiven;//自分への攻撃が当たっていたらtrue
		
		int usePercent[10];//それぞれのスキルを使用する可能性
		CSkillManager Skills;
		int usedSkillNum;
	};

static FILE* enemy_fp=fopen( "noseResource/enemyData.txt" , "r" );
//※mainのawakeでfclose

static CEnemy
	REDRAMP(enemy_fp),
	YELLOWRAMP(enemy_fp),
	BLUERAMP(enemy_fp),
	PURPLERAMP(enemy_fp),
	BLACK_FIRERAMP(enemy_fp),
	WHITE_THUNDERRAMP(enemy_fp);

