#include"Menu.h"

#define SelectMax 4

#define TitleCase -2
#define HowToPlayCase 20
#define MapLookCase 30

void CMenu::Awake(){
	menuGazou[0] = LoadGraph("sugoroku_Resource/menu1.png");
	menuGazou[1] = LoadGraph("sugoroku_Resource/menu2.png");
	menuGazou[2] = LoadGraph("sugoroku_Resource/menu3.png");
	menuGazou[3] = LoadGraph("sugoroku_Resource/menu4.png");
	
	buttonPic[0] = LoadGraph("sugoroku_Resource/closemenu.png");

	subMenuPic = LoadGraph("sugoroku_Resource/subMenu.png");
	selectSpotPic = LoadGraph("sugoroku_Resource/aomidori.png");

	MenuMouse[0].Awake(312,140,469,157);//タイトルに戻る
	MenuMouse[1].Awake(341,192,438,207);//あそび方
	MenuMouse[2].Awake(328,240,443,257);//マップを見る
	MenuMouse[3].Awake(347,289,427,306);//せってい
	MenuMouse[4].Awake(640,26,800,50);//メニュー/マップを閉じる

	buttonSwitch = false;
	MenuKey.Awake();
}

void CMenu::ResetButtonSwitch(){
	buttonSwitch = false;
}

void CMenu::Init(LoopCase NowCase){
	tempCase = NowCase;
	frame = 0;
	tempF = 0;
	menuSelect = 0;
}

int CMenu::SelectedCase(){
	if( MenuKey.Pushed(KEY_INPUT_RETURN,TITLE_SOUND) ){
		return menuSelect;
	}
	
	if( MenuMouse[0].Released() || MenuMouse[1].Released() || MenuMouse[2].Released() || MenuMouse[3].Released() ){
		return menuSelect;
	}
	return 10;
}

bool CMenu::Opened(){
	if(MenuMouse[4].Pushed()){
		MenuMouse[4].SetFlag();
	}
	if(MenuMouse[4].GetFlag()==true){
		DrawExtendGraph(641,27,799,50,selectSpotPic,true);
	}
	if(buttonSwitch==false){
		if( MenuKey.Pushed(KEY_INPUT_SPACE,SUGOROKU_SOUND) || MenuMouse[4].Released() ){
			buttonSwitch=true;
			return true;
		}
	}
	return false;
}

bool CMenu::Closed(){

	if(MenuMouse[4].Pushed()){
		MenuMouse[4].SetFlag();
	}
	if(MenuMouse[4].GetFlag()==true){
		DrawExtendGraph(641,27,799,50,selectSpotPic,true);
	}
	if(buttonSwitch==true){
		DrawGraph(641,26,buttonPic[0],true);
		if(MenuMouse[4].Released() || MenuKey.Pushed(KEY_INPUT_SPACE,TITLE_SOUND)){
			buttonSwitch = false;
			return true;
		}
	}

	return false;
}

void CMenu::Select(){

	if(MenuKey.Pushed(KEY_INPUT_UP,TITLE_SOUND)||MenuKey.Hold(KEY_INPUT_UP,10,TITLE_SOUND)){
		menuSelect--;
		tempF = frame;
	}
	if(MenuKey.Hold(KEY_INPUT_DOWN,10,TITLE_SOUND)||MenuKey.Pushed(KEY_INPUT_DOWN,TITLE_SOUND)){
		menuSelect ++;
		tempF = frame;
	}

	if( MenuMouse[0].Pushed() && !MenuMouse[1].GetFlag() && !MenuMouse[2].GetFlag() && !MenuMouse[3].GetFlag() ){
		MenuMouse[0].SetFlag();
		menuSelect = 0;
	}
	if( MenuMouse[1].Pushed() && !MenuMouse[0].GetFlag() && !MenuMouse[2].GetFlag() && !MenuMouse[3].GetFlag() ){
		MenuMouse[1].SetFlag();
		menuSelect = 1;
	}
	if( MenuMouse[2].Pushed() && !MenuMouse[0].GetFlag() && !MenuMouse[1].GetFlag() && !MenuMouse[3].GetFlag() ){
		MenuMouse[2].SetFlag();
		menuSelect = 2;
	}
	if( MenuMouse[3].Pushed() && !MenuMouse[0].GetFlag() && !MenuMouse[1].GetFlag() && !MenuMouse[2].GetFlag() ){
		MenuMouse[3].SetFlag();
		menuSelect = 3;
	}

	if(menuSelect < 0){
		menuSelect = SelectMax+menuSelect;
	}
	if(menuSelect >= SelectMax){
		menuSelect = menuSelect-SelectMax;
	}

}

void CMenu::Draw(){
	DrawGraph(0,0,menuGazou[menuSelect],true);
	frame++;
}

void CMenu::SubDraw(int RestPlace){
	DrawGraph(640,0,subMenuPic,true);
	DrawFormatString(735,5,RED,"%d",RestPlace);
}

LoopCase CMenu::GetTempCase(){
	return tempCase;
}

int CMenu::GetFrame(){
	return frame;
}
