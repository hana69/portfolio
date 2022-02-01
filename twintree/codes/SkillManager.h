#pragma once

#include"Skill.h"
#include"MenuBox.h"


class CSkillManager{
public:
	CSkillManager();
	CSkillManager(int _x,int _y);
	void Init();

	void Selectable();
	void UnSelectable();

	void BstInfuluence(BadStatus _bstType);
	void RecoverBstInfuluence();

	void Draw();
	void Draw(int _x,int _y);
	void Draw(int _nowHP,int _nowMP,BadStatus);//スキル一覧的なものを表示
	bool Selected(int _nowHP,int _nowMP,BadStatus);//スキル一覧からスキルが選ばれた時にtrue
	
	void LearnNewSkill(CSkill*);//新しいスキルを習得
	void DeleteSkill();

	int GetSkillNum();//現在のスキル数

	bool SelectingUseAble();
	bool UseAble(int _num);

	bool SkillValid(CSkill*);

	CSkill* Selecting();//現在選択中のスキル１

	CSkill* GetSkill(int _num);
	CSkill* GetSkill(const char* _name);
	void operator =(CSkillManager);
private:
	void ChangeSkill(CSkill*);
	void SetUseAble(int _nowHP,int _nowMP);
	void DrawConsumePoint();
	void DrawConsumePoint(int,int);
	void DrawConsumePoint(BadStatus _nowBst);

	int x,y;

	CSkill* skill[10];
	bool useAble[10];//スキルが使えるかどうか
	enum {
		BECAUSE_TOUSYOU,
		BECAUSE_MAHUU,
		BECAUSE_SHORTAGE
	}nonAbleCase[10];
	
	int skillNum;
	bool selectable;

	CMenuBox Skills;
};