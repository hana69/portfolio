#pragma once

#include"Enemy.h"
#include"key.h"
#include"Ally.h"
#include"MenuBox.h"
#include"MessageBox.h"

class CBattle{
public:
	CBattle();
	CBattle(CAlly *_me_p,CAlly *_girl_p);

	void Init();
	void main();

	void AddEnemy(CEnemy*);

	void StartBattle();
	bool Ended();
private:
	CBuff NOT_USED;

	void SetPosition();

	void EnemyDraw();
	void AllyDraw();

	void DecideAlly();
		void DecideAllySkillTarget();
			void SelectEnemy();
			void DrawEnemyTargetIcon(int _position);
			void DrawAllyTargetIcon(int _position);
			void FinishSelect();
		void Escape();
			bool Escapable();

	void DecideEnemy(int _num);
		void DecideEnemySkillTarget(int _num);

	CAlly *ally[2];
	CEnemy enemy[6];

	CSkill* allyUseSkill[2];//選択されて、使うであろうスキル
	enum SkillTarget{
			ENEMY_ONE_ST,
			ENEMY_TWO_ST,
			ENEMY_THREE_ST,
			ENEMY_FOUR_ST,
			ENEMY_FIBE_ST,
			ENEMY_ALL_ST,
			ALLY_ME_ST,
			ALLY_GIRL_ST,
			ALLY_ALL_ST
		}allySkillTarget[2];//選択したスキルが狙う相手
	
	CSkill* enemyUseSkill[6];//敵が使うスキル
	SkillTarget enemySkillTarget[6];

	void Battle();
		void JudgeOrder();//行動順を決定
		bool BstEffect();//毒などのダメージ,眠り混乱の自然治癒判定　何らかの状態異常があった場合はtrue
			void BstDrawDamage();//状態異常のダメージ描画
		void MovementInfuluence();//決定した行動を反映
			void SkillInfuluence(CSkill*,CAlly*);
			void SkillInfuluence(CSkill*,CEnemy*);
				void SkillUseMessage(CSkill* ,std::string _userName);
				void SkillUseFailedMessage(CSkill* ,CEnemy* _enemy);
				void GiveDamage(CSkill*,CAlly*,CEnemy*);//味方から敵に攻撃
				void GiveDamage(CSkill*,CEnemy*,CAlly*);//敵から味方に攻撃
					void DamageMessage(std::string _targetName,int _damage);//ダメージを受けた時のメッセージ
				void GiveBuff(CSkill*,SkillTarget);//バフの効果を反映
					void BuffMessage(const char*,CSkill* _skill );
					void BuffFailedMessage(const char*,CSkill*);
				void GiveRecover(CSkill*,CEnemy*,SkillTarget);
				void GiveRecover(CSkill*,CAlly*,SkillTarget);
					void RecoverMessage(const char*,CSkill*);
				void GiveBst(CSkill*,SkillTarget);
					void BstMessage(const char*,CSkill*);
				void GiveBstRecover(CSkill*,SkillTarget);
					void BstRecoverMessage(const char*,BadStatus _recoveredBst, CSkill*);
				void SkillFailedMessage(const char*);
				void SkillAvoidedMessage(const char*);
		void DrawDamage(SkillTarget);//ダメージを数字で表示
		void ResetAllySelect();//味方の選んだ技などをリセット
	
	enum MyTurn{
		ME,GIRL,
		NOT_MY_TURN
	}myTurn;
	enum{
		GETTING_READY,
		DECIDE_MOVEMENT_ALLY,
		DECIDE_MOVEMENT_ENEMY,
		BATTLE,
		RESULT,
	}scene;
	enum{
		BST_EFFECT,
		DECIDE_MOVEMENT,
		MOVEMENT_INFULUENCE
	}battleScene;
	enum{
		FIGHT_ESCAPE,
		ESCAPE,
		ESCAPE_SUCCESS,
		SKILL_ITEM_GARD,
		SKILL_SELECT,
		TARGET_SELECT,
		ITEM_SELECT,
	}allySelectScene;

	enum Order{
		ALLY_ME,
		ALLY_GIRL,
		ENEMY_ONE,
		ENEMY_TWO,
		ENEMY_THREE,
		ENEMY_FOUR,
		ENEMY_FIBE,
	}order[7];
	int orderMax;

	int movingNum;

	bool battleEndFlag;//敵を倒すか逃げたらtrue

	bool skillSuccessFlag;//スキルがちゃんと出せてたらtrue（敵のみ）

	int firstEnemyNum;//出現時の敵の数
	int enemyNum;//現在の敵の数

	int nowTargetNum;//現在ターゲットアイコンを表示しているのが右から何番目か

	int frame,tempframe;

	int targetPic;
	int cursorPic;
	int haikeiPic;

	CMessageBox Message;

	CMenuBox confirm;

	CMenuBox fight_escape;
	CMenuBox skill_item_gard;
};