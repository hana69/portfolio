#include"world.h"

/////////////////�R���X�g���N�^/////////////////////

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

	ConnectMenu.AddNewString("���ǂ�",1,12);
}

/////////////////�p�u���b�N�֐�///////////////////
void CWorld::main(){
	Draw();
}

void CWorld::StartUp(){
	goingFlag = false;
}

void CWorld::Draw(){
	DrawGraph(0,0,graph.background,true);
	DrawFormatString(200,0,RED,"������%s�ł�",name.c_str());
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
			ConnectMenu.AddNewString("����");
			break;
		case KAJIYA:
			ConnectMenu.AddNewString("������");
			break;
		case GATE:
			ConnectMenu.AddNewString("��");
			break;
		default:break;
		}

		Message.Call("�V�����s���悪�ǉ�����܂����I");
	}else{
		return;
	}
}
///////////////////CHouse///////////////////

	////////////////�R���X�g���N�^//////////////////
CHouse::CHouse():
	CWorld("����")
{
	wName = HOUSE;

	MovementMenu.AddNewString("�O�ɏo��");
	MovementMenu.AddNewString("����������");
	MovementMenu.AddNewString("�A�C�e��������");
	MovementMenu.AddNewString("�Z�[�u����");

	scene=SELECT;
}

	///////////////�p�u���b�N�֐�///////////////////
void CHouse::main(){
	Draw();
	
	switch(scene){
	
	case SELECT:
		Message.Call("�������܂���");
		MovementMenu.Draw();
		
		if(MovementMenu.Selected()){
			scene = (Scene)MovementMenu.SelectSpot().second;//Scene�̐錾�Ɠ������ԂɂȂ�悤��MovementMenu�ɕ���������Ă���̂ŁA����ł��܂�����
		}
		break;
	
	case GO_OUT:
		Message.Call("�ǂ��ɍs���܂���");
		ConnectMenu.Draw();

		if(ConnectMenu.Selected()){
			if(ConnectMenu.SelectingString()=="���ǂ�"){
				scene = SELECT;
			}else{
				goingFlag = true;
			}
		}

		break;
	case SHOW_ARMS:
		MyArms.Draw();
		Message.Call("��������������E�h���I��ł�������");
		if(MyArms.ReturnSelected()){
			scene = SELECT;
		}
		
		break;

	case SHOW_ITEM:
		Message.Call("�g�p�������A�C�e����I��ł�������");
		break;

	case SAVE:
		Message.Call("�ǂ̃t�@�C���ɃZ�[�u���܂���");
		break;
	}

}

void CHouse::StartUp(){
	scene = SELECT;
	MyArms.Awake();
}

//////////////////CArmShop////////////////////////

	//////////////�R���X�g���N�^/////////////
CArmShop::CArmShop():
	CWorld("������")
{
	wName = KAJIYA;

	MovementMenu.AddNewString("�O�ɏo��");
	MovementMenu.AddNewString("���������");
	MovementMenu.AddNewString("�����𔃂�");
	MovementMenu.AddNewString("�����𔄂�");
}
	/////////////�p�u���b�N�֐�///////////////
void CArmShop::main(){
	Draw();
	switch(scene){

	case SELECT:
		Message.Call("�������܂���");
		MovementMenu.Draw();
		
		if(MovementMenu.Selected()){
			scene = (Scene)MovementMenu.SelectSpot().second;//Scene�̐錾�Ɠ������ԂɂȂ�悤��MovementMenu�ɕ���������Ă���̂ŁA����ł��܂�����
		}
		break;
	
	case GO_OUT:
		Message.Call("�ǂ��ɍs���܂���");
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

//////////////�R���X�g���N�^/////////////
CGate::CGate():
	CWorld("��"),
	SelectDungeon( "noseResource/battleMenuHaikei.png","noseResource/battleMenuSelect.png",0,0,128,30,1,12,WHITE,RED)
{
	wName = GATE;
	MovementMenu.AddNewString("���̊O�ɏo��");
	MovementMenu.AddNewString("���̏ꏊ�ɍs��");

	SelectDungeon.AddNewString("���̑��A");
}
	/////////////�p�u���b�N�֐�///////////////

void CGate::main(){
	Draw();
	
	switch(scene){
	case SELECT:
		Message.Call("�ǂ����܂���");
		MovementMenu.Draw();
		
		if(MovementMenu.Selected()){
			scene = (Scene)MovementMenu.SelectSpot().second;//Scene�̐錾�Ɠ������ԂɂȂ�悤��MovementMenu�ɕ���������Ă���̂ŁA����ł��܂�����
		}
		break;
	case GO_QUEST:
		Message.Call("�ǂ��ɍs���܂���");
		SelectDungeon.Draw();
		if( SelectDungeon.Selected() ){
			dungeonFlag = true;
		}
		break;
	case GO_OUT:
		Message.Call("�ǂ��ɍs���܂���");
		ConnectMenu.Draw();

		if(ConnectMenu.Selected()){
			if(ConnectMenu.SelectingString()=="���ǂ�"){
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