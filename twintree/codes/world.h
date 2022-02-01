#pragma once
#include"MenuBox.h"
#include"MessageBox.h"
#include"ArmManager.h"

enum WorldName{
	NO_WORLD,
	HOUSE,
	KAJIYA,
	GATE,
	WORLD_MAX
};

class CWorld{
public:
	CWorld(const TCHAR* _name);
	
	virtual void main();
	void Draw();				//�w�i�摜�ƑI����ʂ�\��
	
	WorldName GoingPlace();	//�s�����Ƃ����ꏊ��wName��Ԃ�

	std::string GetName();

	void AddNewConnectPlace(WorldName);

	bool GoneDungeon(){
		return dungeonFlag;
	};
	

	virtual void StartUp();
private:
	static const int CONNECT_MAX=12;
	WorldName connect[CONNECT_MAX];//���݂̏ꏊ����s����ꏊ�@�ő�P�Q��
	int connectNum;//���݂̏ꏊ����s����ꏊ�̐�
	
	std::string name;	//�ꏊ�̖��O

	struct{
		std::string filename;
		int background;
	}graph;//�摜�Ɋւ���F�X
protected:
	WorldName wName;//�v���O������Ŏ��ʂ��邽�߂̖��O
	
	bool goingFlag;//���̏ꏊ�ɍs�����Ƃ�����true
	bool dungeonFlag;//����̂�//�O�ɏo�悤�Ƃ����Ƃ�true
	CMenuBox ConnectMenu;//���ꂼ��̏ꏊ���炢���鑼�̏ꏊ�̃��j���[
	CMenuBox MovementMenu;//���ꂼ��̏ꏊ�ŏo����s���̃��j���[
	CMessageBox Message;//��ʉ��ɕ\�����郁�b�Z�[�W
};

class CHouse : public CWorld{
public:
	CHouse();
	void main();
	void StartUp();
private:
	enum Scene{
		SELECT,
		GO_OUT,
		SHOW_ARMS,
		SHOW_ITEM,
		SAVE,
	}scene;

	CArmManager MyArms; //����͉Ƃɒu���Ă������
};

class CArmShop : public CWorld{
public:
	CArmShop();
	void main();
	void StartUp();
private:
	enum Scene{
		SELECT,
		GO_OUT,
		MAKE_ARM,
		BUY_ARM,
		SELL_ARM,
	}scene;
};

class CGate: public CWorld{
public:
	CGate();
	void main();
	void StartUp();

	void AddNewDungeon();

private:
	enum Scene{
		SELECT,
		GO_QUEST,
		GO_OUT
	}scene;

	CMenuBox SelectDungeon;
};