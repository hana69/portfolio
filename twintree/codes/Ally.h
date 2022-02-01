#pragma once

#include"DxLib.h"
#include"Suken.h"
#include"SkillManager.h"
#include"MenuBox.h"

class CAlly{
public:
	CAlly(const char* _name ,int _hp,int _sp,int _pA,int _pG,int _mA,int _mG,int _speed);
	
	void Init();
	void BattleInit();

	void AddSkill(CSkill*);
	CSkill* SelectingSkill();
	int HavingSkillNum();
	bool SkillWasSelected();
	
	virtual void GiveDamage(CSkill* _givenSkill,int _atk)=0;
	virtual void DrawInfo()=0;
	
	void ConsumeP(CSkill* _usedSkill);

	void Gard();
	void CancellGard();

	void GainExp();

	std::string GetName();
	int GetRank(Parameter);
	int GetStatus(Parameter);//���l
	int RealParameter(Parameter);//���ۂɔ���Ɏg���l
	bool Defending();

	int GetDamage();

	void SkillCopy(CSkillManager*);

	virtual void DrawDamage()=0;
	virtual void DrawBstDamage()=0;

	CSkill::SkillResult GiveBuff(int _num,Parameter);//�\�͒l���オ������true�ő�l�܂ŏオ���Ă��Ă��܂������Ȃ�������false
	CSkill::SkillResult GiveBst(CSkill*);
	CSkill::SkillResult GiveBstRecover(CSkill*);

	BadStatus NowBst();
	bool BstRecover();
	BadStatus RecoveredBst();
	void BstEffect();

	virtual bool AtackGiven(CSkill* _skill)=0;////�U���Z���O�ꂽ��false

	virtual CSkill::SkillResult GiveRecover(CSkill* _givenSkill,int _m_a)=0;
protected:
	void LoadStatusGraph();
	int statusGraph[Parameter::SPEED+1][2];
	void DeleteSkill();

	std::string name;

	bool defensive;

	int hp;
	int hpMax;
	int sp;
	int spMax;
	int status[SPEED+1];
	int level;
	int exp;//���݂̗݌v�o���l
		
	int rank[SPEED+1];//�o�t�̂�����

	BadStatus nowBst;//���݂������Ă����Ԉُ�
	BadStatus recoveredBst;
	int bstTurn;

	int damage;
	int recoverAmount;

	bool damageGiven;//�����ւ̍U�����������Ă�����true

	//static int statusGraph[3][2];

	CSkillManager Skills;
};

class CMe :public CAlly{
public:
	CMe(const char* _name ,int _hp,int _sp,int _pA,int _pG,int _mA,int _mG,int _speed);

	void DrawInfo();
	void GiveDamage(CSkill* _givenSkill,int _atk);
	void DrawDamage();
	void DrawBstDamage();
	CSkill::SkillResult GiveRecover(CSkill*,int);
	bool AtackGiven(CSkill*);
private:
	void DrawStatusGraph();
};

class CGirl :public CAlly{
public:
	CGirl(const char* _name ,int _hp,int _sp,int _pA,int _pG,int _mA,int _mG,int _speed);
	
	void DrawInfo();
	void GiveDamage(CSkill* _givenSkill,int _atk);
	void DrawDamage();
	void DrawBstDamage();
	CSkill::SkillResult GiveRecover(CSkill*,int);
	bool AtackGiven(CSkill*);
private:
	void DrawStatusGraph();
};