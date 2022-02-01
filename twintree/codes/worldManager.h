#pragma once

#include"Suken.h"
#include"DxLib.h"
#include"world.h"

class CWorldManager{
public:
	CWorldManager();
	void Awake();
	
	bool GetOut();

	void Main();
private:
	CWorld* nowPlace_p;

	CHouse house;
	CArmShop kajiya;
	CGate gate;
};