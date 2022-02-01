#pragma once

#include"worldManager.h"
#include"ArmManager.h"
#include"DungeonManager.h"
#include"Title.h"
#include"BattleManager.h"

class CMain{
public:
	CMain();
	void GameLoop();
	void Awake();
private:
	int frame,tempframe;
	
	void SetSelectSkill();//どの種類のどのレベルにどの技が入るか設定
	enum{
		TITLE,
		SELECT_SKILL,
		SELECT_BATTLE,
		BATTLE,
		MY_VILLAGE,
		DUNGEON
	}scene;
	CTitle Title;

	int backPic;
	int titleBGM;

	void SelectSkill();
	void SelectBattle();

	void SetAlly(int);//レベルに応じて味方のステータスを決定
	void SetEnemies(int);//レベルに応じて敵を追加
	enum{
		M_A,
		BUFF,
		BST_RECOVER,
		P_A
	}selectingSkillType;

	FILE* saveData;
	int battleLevelLimit;
	int nowSkillLevel[P_A+1];
	
	
	CSkillManager Skills[P_A+1][10];
	CSkillManager UseSkills[2];
	CMessageBox SkillMessage;

	CWorldManager World;
	CDungeonManager Dungeon;
	CKey Key;

	CMe Me;
	CGirl Girl;

	FILE* pa_fp;
	CPhysicAtack ZANGEKI;
	CPhysicAtack KYUGEKI;
	CPhysicAtack TOSSIN;
	CPhysicAtack MOUSINGEKI;

	FILE* ma_fp;
	CMajicAtack ORIA,RAZ_ORIA,ORIEL,RAZ_ORIEL,ORUBERIA,RAZ_ORUBERIA;
	CMajicAtack RIZEK,RAZ_RIZEK,RIZARK,RAZ_RIZARK,RIZERUKARU,RAZ_RIZERUKARU;
	CMajicAtack ZAHA,RAZ_ZAHA,ZAFIRA,RAZ_ZAFIRA,ZAFIRAM,RAZ_ZAFIRAM;
	CMajicAtack SADAL,RAZ_SADAL,SADALT,RAZ_SADALT,SADALTIO,RAZ_SADALTIO;
	CMajicAtack TIMYAKU_MEIDOU;
	CMajicAtack DANKAI;

	FILE* buff_fp;
	CBuff GEWALT,ERTRAGEN,WEISEN,SIGKEIT,BEEILEN;
	CBuff SCHWACH,KROKANT, LUGE, SCHARF,LANGSAM;

	FILE* recover_fp;
	CRecover ERHOLUNG,RAZ_ERHOLUNG;
	CRecover TIEROA,RAZ_TIERON;
	CRecover KARUTIROA,KARUTIROA_RAZEL;
	
	FILE* bst_fp;
	CBadStatus KONSUIHADOU; 
	CBadStatus MOUDOKUHADOU;
	CBadStatus MAHUUHADOU;
	CBadStatus KONSUISYOUHA; 
	CBadStatus MOUDOKUSYOUHA;
	CBadStatus MAHUUSYOUHA;

	FILE* bst_recover_fp;
	CBstRecover PRIOA,PRIOA_RAZEL;
	CBstRecover TORMIA,TORMIA_RAZEL;
	CBstRecover PETOROIA,PETOROIA_RAZEL;

	//CBattle Battle;

	CBattleManager Battles;
	
};