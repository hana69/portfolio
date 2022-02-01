#include"ArmManager.h"
/////////////////Arm�N���X//////////////

////////////////�R���X�g���N�^/////////

CArmManager::CArm::CArm(){
	name="";
	atk =0;
	dff =0;
	element=NO_ELEMENT;
}

CArmManager::CArm::CArm(FILE* _armdata){
	fscanf( _armdata, "%s %d %d %d", name.c_str() , &atk,&dff,&element );
}
////////////////�p�u���b�N�֐�/////////////
void CArmManager::CArm::DrawInfo(){
	
	DrawFormatString( 75,82,WHITE,"%d",atk );
	DrawFormatString( 75,101,WHITE,"%d",dff );
	
	switch(element){
	case NO_ELEMENT:
		DrawString(75,120,"��",WHITE);
		break;
	case FIRE:
		DrawString(75,120,"��",RED);
		break;
	case ICE:
		DrawString(75,120,"��",BLUE);
		break;
	case WIND:
		DrawString(75,120,"��",GREEN);
		break;
	case THUNDER:
		DrawString(75,120,"��",YELLOW);
		break;
	}

}

std::string CArmManager::CArm::GetName(){
	return name;
}

int CArmManager::CArm::GetAtk(){
	return atk;
}

int CArmManager::CArm::GetDff(){
	return dff;
}

Element CArmManager::CArm::GetElement(){
	return element;
}
////////////////�I�y���[�^�[//////////////
void CArmManager::CArm::operator = (CArm* _arm){
	name = _arm -> name.c_str();
	atk = _arm -> atk;
	dff = _arm -> dff;
	element = _arm -> element;
}