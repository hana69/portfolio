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

	CSkill* allyUseSkill[2];//�I������āA�g���ł��낤�X�L��
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
		}allySkillTarget[2];//�I�������X�L�����_������
	
	CSkill* enemyUseSkill[6];//�G���g���X�L��
	SkillTarget enemySkillTarget[6];

	void Battle();
		void JudgeOrder();//�s����������
		bool BstEffect();//�łȂǂ̃_���[�W,���荬���̎��R��������@���炩�̏�Ԉُ킪�������ꍇ��true
			void BstDrawDamage();//��Ԉُ�̃_���[�W�`��
		void MovementInfuluence();//���肵���s���𔽉f
			void SkillInfuluence(CSkill*,CAlly*);
			void SkillInfuluence(CSkill*,CEnemy*);
				void SkillUseMessage(CSkill* ,std::string _userName);
				void SkillUseFailedMessage(CSkill* ,CEnemy* _enemy);
				void GiveDamage(CSkill*,CAlly*,CEnemy*);//��������G�ɍU��
				void GiveDamage(CSkill*,CEnemy*,CAlly*);//�G���疡���ɍU��
					void DamageMessage(std::string _targetName,int _damage);//�_���[�W���󂯂����̃��b�Z�[�W
				void GiveBuff(CSkill*,SkillTarget);//�o�t�̌��ʂ𔽉f
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
		void DrawDamage(SkillTarget);//�_���[�W�𐔎��ŕ\��
		void ResetAllySelect();//�����̑I�񂾋Z�Ȃǂ����Z�b�g
	
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

	bool battleEndFlag;//�G��|������������true

	bool skillSuccessFlag;//�X�L���������Əo���Ă���true�i�G�̂݁j

	int firstEnemyNum;//�o�����̓G�̐�
	int enemyNum;//���݂̓G�̐�

	int nowTargetNum;//���݃^�[�Q�b�g�A�C�R����\�����Ă���̂��E���牽�Ԗڂ�

	int frame,tempframe;

	int targetPic;
	int cursorPic;
	int haikeiPic;

	CMessageBox Message;

	CMenuBox confirm;

	CMenuBox fight_escape;
	CMenuBox skill_item_gard;
};