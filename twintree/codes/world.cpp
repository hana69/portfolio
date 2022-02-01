#include"world.h"

/////////////////コンストラクタ/////////////////////

CWorld::CWorld( const TCHAR* _name ):
	ConnectMenu( "noseResource/battleMenuHaikei.png","noseResource/battleMenuSelect.png",0,0,128,30,1,12,WHITE,RED),
	MovementMenu( "noseResource/battleMenuHaikei.png","noseResource/battleMenuSelect.png",514,0,128,30,1,12,WHITE,RED),
	Message( 0,360,640,120 )
{
	for(int i=0;i<12;i++){
		connect[i] = NO_WORLD;
	}
	name = _name;
	connectNum=0;

	goingFlag = false;
	dungeonFlag=false;

	ConnectMenu.AddNewString("もどる",1,12);
}

/////////////////パブリック関数///////////////////
void CWorld::main(){
	Draw();
}

void CWorld::StartUp(){
	goingFlag = false;
}

void CWorld::Draw(){
	DrawGraph(0,0,graph.background,true);
	DrawFormatString(200,0,RED,"ここは%sです",name.c_str());
	Message.Draw();
}

WorldName CWorld::GoingPlace(){
	if(goingFlag ==true ){
		goingFlag = false;
		return connect[ConnectMenu.SelectSpot().second-1];
	}
	return NO_WORLD;
}

std::string CWorld::GetName(){
	return name;
}

void CWorld::AddNewConnectPlace(WorldName newPlace){
	if( connectNum - 1 <= CONNECT_MAX ){
		connect[connectNum] = newPlace;
		connectNum++;
		
		switch(newPlace){
		
		case HOUSE:
			ConnectMenu.AddNewString("自宅");
			break;
		case KAJIYA:
			ConnectMenu.AddNewString("かじや");
			break;
		case GATE:
			ConnectMenu.AddNewString("門");
			break;
		default:break;
		}

		Message.Call("新しく行き先が追加されました！");
	}else{
		return;
	}
}
///////////////////CHouse///////////////////

	////////////////コンストラクタ//////////////////
CHouse::CHouse():
	CWorld("自宅")
{
	wName = HOUSE;

	MovementMenu.AddNewString("外に出る");
	MovementMenu.AddNewString("装備を見る");
	MovementMenu.AddNewString("アイテムを見る");
	MovementMenu.AddNewString("セーブする");

	scene=SELECT;
}

	///////////////パブリック関数///////////////////
void CHouse::main(){
	Draw();
	
	switch(scene){
	
	case SELECT:
		Message.Call("何をしますか");
		MovementMenu.Draw();
		
		if(MovementMenu.Selected()){
			scene = (Scene)MovementMenu.SelectSpot().second;//Sceneの宣言と同じ順番になるようにMovementMenuに文字をいれているので、これでうまくいく
		}
		break;
	
	case GO_OUT:
		Message.Call("どこに行きますか");
		ConnectMenu.Draw();

		if(ConnectMenu.Selected()){
			if(ConnectMenu.SelectingString()=="もどる"){
				scene = SELECT;
			}else{
				goingFlag = true;
			}
		}

		break;
	case SHOW_ARMS:
		MyArms.Draw();
		Message.Call("装備したい武器・防具を選んでください");
		if(MyArms.ReturnSelected()){
			scene = SELECT;
		}
		
		break;

	case SHOW_ITEM:
		Message.Call("使用したいアイテムを選んでください");
		break;

	case SAVE:
		Message.Call("どのファイルにセーブしますか");
		break;
	}

}

void CHouse::StartUp(){
	scene = SELECT;
	MyArms.Awake();
}

//////////////////CArmShop////////////////////////

	//////////////コンストラクタ/////////////
CArmShop::CArmShop():
	CWorld("かじや")
{
	wName = KAJIYA;

	MovementMenu.AddNewString("外に出る");
	MovementMenu.AddNewString("装備を作る");
	MovementMenu.AddNewString("装備を買う");
	MovementMenu.AddNewString("装備を売る");
}
	/////////////パブリック関数///////////////
void CArmShop::main(){
	Draw();
	switch(scene){

	case SELECT:
		Message.Call("何をしますか");
		MovementMenu.Draw();
		
		if(MovementMenu.Selected()){
			scene = (Scene)MovementMenu.SelectSpot().second;//Sceneの宣言と同じ順番になるようにMovementMenuに文字をいれているので、これでうまくいく
		}
		break;
	
	case GO_OUT:
		Message.Call("どこに行きますか");
		ConnectMenu.Draw();

		if(ConnectMenu.Selected()){
			if(ConnectMenu.SelectSpot().second == 12){
				scene = SELECT;
			}else{
				goingFlag = true;
			}
		}

		break;
	}

}
void CArmShop::StartUp(){
	scene = SELECT;
}

///////////////////CGATE////////////////////

//////////////コンストラクタ/////////////
CGate::CGate():
	CWorld("門"),
	SelectDungeon( "noseResource/battleMenuHaikei.png","noseResource/battleMenuSelect.png",0,0,128,30,1,12,WHITE,RED)
{
	wName = GATE;
	MovementMenu.AddNewString("村の外に出る");
	MovementMenu.AddNewString("他の場所に行く");

	SelectDungeon.AddNewString("やんの巣窟");
}
	/////////////パブリック関数///////////////

void CGate::main(){
	Draw();
	
	switch(scene){
	case SELECT:
		Message.Call("どうしますか");
		MovementMenu.Draw();
		
		if(MovementMenu.Selected()){
			scene = (Scene)MovementMenu.SelectSpot().second;//Sceneの宣言と同じ順番になるようにMovementMenuに文字をいれているので、これでうまくいく
		}
		break;
	case GO_QUEST:
		Message.Call("どこに行きますか");
		SelectDungeon.Draw();
		if( SelectDungeon.Selected() ){
			dungeonFlag = true;
		}
		break;
	case GO_OUT:
		Message.Call("どこに行きますか");
		ConnectMenu.Draw();

		if(ConnectMenu.Selected()){
			if(ConnectMenu.SelectingString()=="もどる"){
				scene = SELECT;
			}else{
				goingFlag = true;
			}
		}
		break;
	}

}

void CGate::StartUp(){
	scene = SELECT;
}

void CGate::AddNewDungeon(){
	
}