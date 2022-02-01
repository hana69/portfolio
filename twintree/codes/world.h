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
	void Draw();				//背景画像と選択画面を表示
	
	WorldName GoingPlace();	//行こうとした場所のwNameを返す

	std::string GetName();

	void AddNewConnectPlace(WorldName);

	bool GoneDungeon(){
		return dungeonFlag;
	};
	

	virtual void StartUp();
private:
	static const int CONNECT_MAX=12;
	WorldName connect[CONNECT_MAX];//現在の場所から行ける場所　最大１２個
	int connectNum;//現在の場所から行ける場所の数
	
	std::string name;	//場所の名前

	struct{
		std::string filename;
		int background;
	}graph;//画像に関する色々
protected:
	WorldName wName;//プログラム上で識別するための名前
	
	bool goingFlag;//他の場所に行こうとした時true
	bool dungeonFlag;//※門のみ//外に出ようとしたときtrue
	CMenuBox ConnectMenu;//それぞれの場所からいける他の場所のメニュー
	CMenuBox MovementMenu;//それぞれの場所で出来る行動のメニュー
	CMessageBox Message;//画面下に表示するメッセージ
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

	CArmManager MyArms; //武器は家に置いてあるもの
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