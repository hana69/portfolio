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

	BadStatus bstType;//状態異常の種類
	int bstPer;//状態異常付着率
};

class CPhysicAtack :public CSkill{
public:
	CPhysicAtack(FILE* _fp);
	int GetAmount();//ダメージの量
	SkillType GetSkillType();
	Element GetElement();
	int GetHitPer();
private:
	int damage;//与えるダメージ 
	Element element;//属性

	int hitPer;//命中率
};

class CMajicAtack :public CSkill{
public:
	CMajicAtack(FILE* _fp);
	int GetAmount();//ダメージの量
	SkillType GetSkillType();
	Element GetElement();
	int GetHitPer();
private:
	int damage;//与えるダメージ
	Element element;//属性

	int hitPer;//命中率
};

class CBuff :public CSkill{
public:
	
	CBuff(FILE*);
	CBuff(const char* _name,const char* _hurigana,const char* _explain,const char* message,int _amount,BuffType,TargetType,int _consumeP );

	int GetAmount();//ステータス変化の量
	
	int GetConsumePoint();
	SkillType GetSkillType();
	BuffType GetBuffType();
	std::string Message();
private:
	int amount;//変化量　ステータス低下ならマイナス
	BuffType type;
	std::string message;
};

class CRecover:public CSkill{
public:
	CRecover(FILE*);
	int GetAmount();//回復量
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
	"敵一体",
	"敵全体",
	"味方一体",
	"味方全体"
};
static std::string BuffTypeString[CSkill::SPD_BUFF+1]={
	"物攻",
	"物防",
	"魔攻",
	"魔防",
	"素早さ"
};
static std::string bstRecoverString[CSkill::NOT_ELE+1]={
	"全部",
	"属性系",
	"非属性系"
};