#include"dungeon.h"

////////////////CDungeon///////////////////

//////////////コンストラクタ/////////////////
CDungeon::CDungeon(const char* _name,int _floor)
	:Battle(NULL,NULL),
	 Road("noseResource/battleMenuHaikei.png","noseResource/battleMenuSelect.png",0,0,128,30,1,12,WHITE,RED),
	 Message(0,360,640,120)
{
	name = _name;
	floor = _floor;

	exitFlag = false;
	
}

/////////////パブリック関数////////////
void CDungeon::Main(){}

bool CDungeon::Exit(){
	if(exitFlag==true){
		exitFlag=false;
		return true;
	}
	return false;
}
////////////プライベート関数//////////

///////////プロテクト関数
void CDungeon::Explore(){}

void CDungeon::SetEnemyNum(){}

void CDungeon::SetEnemyType(){}


/////////////////YAN_VILLAGE/////////////////////

//////コンストラクタ/////
YAN_VILLAGE::YAN_VILLAGE(const char* _name,int _floor)
:CDungeon(_name,_floor)
{
	Road.AddNewString("右の道を進む");
	Road.AddNewString("まっすぐ進む");
	Road.AddNewString("左の道を進む");
	scene = SELECT_ROAD;
	explore_result = NOTHING;
}
//////パブリック関数///////
void YAN_VILLAGE::Main(){
	
	
	Message.Draw();
	switch(scene){

	case SELECT_ROAD:
		Message.Call("どの道を進みますか？");
		Road.Draw();
		Explore();
		break;

	case BATTLE:
		Message.Call("敵が現れた！");
		Battle.main();
		if(Battle.Ended()){
			scene = SELECT_ROAD;
		}
		break;

	case GET_ITEM:
		Message.Call("アイテムを手に入れた！");
		if(Key.Pushed(KEYNAME.ENTER)){
			scene = SELECT_ROAD;
		}
		break;
	}

	frame++;
}

//////プライベート関数//////
void YAN_VILLAGE::Explore(){

	int rand;
	rand=0;

	if( Road.Selected() ){
		rand=GetRand(99)+1;

		if(rand<=100){
			explore_result = ENEMY;
		}else if( rand <= 0 ){
			explore_result = ITEM;
		}else {
			explore_result = NOTHING;
		}

		SetExploreResult();
	}
	
}
void YAN_VILLAGE::SetExploreResult(){

	tempFrame = frame;

	
	switch(explore_result){

	case ENEMY:
		scene = BATTLE;
		
		SetEnemyNum();
		SetEnemyType();

		Battle.StartBattle();

		break;

	case ITEM:
		scene = GET_ITEM;
		break;

	case NOTHING:
		scene = SELECT_ROAD;
		break;

	}

}

void YAN_VILLAGE::SetEnemyNum(){
	int rand=0;
	rand = GetRand(99)+1;

	if(rand<=10){
		enemyNum=1;
	}else if(rand<=40){
		enemyNum=2;
	}else if(rand<=70){
		enemyNum=3;
	}else{
		enemyNum=4;
	}

}

void YAN_VILLAGE::SetEnemyType(){
	
	if(enemyNum==1){
		Battle.AddEnemy(&YELLOWRAMP);
	}else{
		int rand=0;
		
		while(enemyNum>0){
			rand=GetRand(1);
			
			switch(rand){
				case 1:
					Battle.AddEnemy(&REDRAMP);
					break;
				case 2:
					break;
			}
			enemyNum--;
		}

	}

}