#pragma once

#include"DxLib.h"
#include"Suken.h"

class CSkill{
public:
	enum SkillType{
		PHYSIC_ATK,
		MAJIC_ATK,
		BUFF,
		RECOVER,
		BAD_STATUS,
		BST_RECOVER
	};
	enum TargetType{
		ENEMY,
		ENEMY_ALL,
		ALLY,
		ALLY_ALL
	};
	enum BuffType{
		PA_BUFF,
		PG_BUFF,
		MA_BUFF,
		MG_BUFF,
		SPD_BUFF
	};
	enum BstRecoverType{
		ALL,
		ELEMENT,
		NOT_ELE
	};
	enum SkillResult{
		FAILED=-1,
		AVOIDED,
		SUCCESSED
	};

	CSkill();
	CSkill(const char*);
	CSkill(const char* _name,const char* _hurigana,const char* _explain,TargetType _targetType,int _consumeP);
	CSkill(const char* _name,const char* _hurigana,const char* _explain,TargetType _targetType,int _consumeP,BadStatus,int _bstPer);
	
	std::string GetName();
	std::string GetHurigana();
	std::string GetExplain();
	int GetConsumePoint();
	TargetType 	GetTargetType();

	virtual std::string Message();
	virtual BuffType GetBuffType();
	virtual BstRecoverType GetBstRecoverType();
	virtual Element GetElement();

	virtual int GetAmount();
	virtual SkillType GetSkillType()=0;

	BadStatus GetBstType();
	int GetBstPer();

	virtual int GetHitPer();

	bool UseSuccess(int _nowPoint);

	bool GetValid();
protected:
	TargetType targetType;
	std::string name;
	std::string hurigana;
	std::string explain;

	bool valid;

	int consumePoint;

	BadStatus bstType;//��Ԉُ�̎��
	int bstPer;//��Ԉُ�t����
};

class CPhysicAtack :public CSkill{
public:
	CPhysicAtack(FILE* _fp);
	int GetAmount();//�_���[�W�̗�
	SkillType GetSkillType();
	Element GetElement();
	int GetHitPer();
private:
	int damage;//�^����_���[�W 
	Element element;//����

	int hitPer;//������
};

class CMajicAtack :public CSkill{
public:
	CMajicAtack(FILE* _fp);
	int GetAmount();//�_���[�W�̗�
	SkillType GetSkillType();
	Element GetElement();
	int GetHitPer();
private:
	int damage;//�^����_���[�W
	Element element;//����

	int hitPer;//������
};

class CBuff :public CSkill{
public:
	
	CBuff(FILE*);
	CBuff(const char* _name,const char* _hurigana,const char* _explain,const char* message,int _amount,BuffType,TargetType,int _consumeP );

	int GetAmount();//�X�e�[�^�X�ω��̗�
	
	int GetConsumePoint();
	SkillType GetSkillType();
	BuffType GetBuffType();
	std::string Message();
private:
	int amount;//�ω��ʁ@�X�e�[�^�X�ቺ�Ȃ�}�C�i�X
	BuffType type;
	std::string message;
};

class CRecover:public CSkill{
public:
	CRecover(FILE*);
	int GetAmount();//�񕜗�
	int GetConsumePoint();

	SkillType GetSkillType();

	std::string Message();
private:
	int amount;
	std::string message;
};

class CBadStatus:public CSkill{
public:
	CBadStatus(FILE*);
	SkillType GetSkillType();
private:
};

class CBstRecover:public CSkill{
public:
	CBstRecover(FILE*);
	SkillType GetSkillType();
	BstRecoverType GetBstRecoverType();
private:
	BstRecoverType type;
};

static std::string TargetTypeString[CSkill::ALLY_ALL+1]={
	"�G���",
	"�G�S��",
	"�������",
	"�����S��"
};
static std::string BuffTypeString[CSkill::SPD_BUFF+1]={
	"���U",
	"���h",
	"���U",
	"���h",
	"�f����"
};
static std::string bstRecoverString[CSkill::NOT_ELE+1]={
	"�S��",
	"�����n",
	"�񑮐��n"
};