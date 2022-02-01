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
	void Draw(int _nowHP,int _nowMP,BadStatus);//�X�L���ꗗ�I�Ȃ��̂�\��
	bool Selected(int _nowHP,int _nowMP,BadStatus);//�X�L���ꗗ����X�L�����I�΂ꂽ����true
	
	void LearnNewSkill(CSkill*);//�V�����X�L�����K��
	void DeleteSkill();

	int GetSkillNum();//���݂̃X�L����

	bool SelectingUseAble();
	bool UseAble(int _num);

	bool SkillValid(CSkill*);

	CSkill* Selecting();//���ݑI�𒆂̃X�L���P

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
	bool useAble[10];//�X�L�����g���邩�ǂ���
	enum {
		BECAUSE_TOUSYOU,
		BECAUSE_MAHUU,
		BECAUSE_SHORTAGE
	}nonAbleCase[10];
	
	int skillNum;
	bool selectable;

	CMenuBox Skills;
};