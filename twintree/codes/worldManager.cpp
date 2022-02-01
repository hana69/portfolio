#include"worldManager.h"

CWorldManager::CWorldManager()
{
	
	house.AddNewConnectPlace(KAJIYA);
	house.AddNewConnectPlace(GATE);

	kajiya.AddNewConnectPlace(HOUSE);
	gate.AddNewConnectPlace(HOUSE);

	nowPlace_p = &house;

}
	
void CWorldManager::Awake(){
	house.StartUp();
}

bool CWorldManager::GetOut(){

	if(nowPlace_p == &gate){
		if( nowPlace_p->GoneDungeon() ){
			return true;
		}
	}

	return false;
}

void CWorldManager::Main(){

	nowPlace_p -> main();

	switch(nowPlace_p -> GoingPlace() ){

	case HOUSE:
		nowPlace_p = &house;
		nowPlace_p -> StartUp();
		break;
	case KAJIYA:
		nowPlace_p = &kajiya;
		nowPlace_p -> StartUp();
		break;
	case GATE:
		nowPlace_p = &gate;
		nowPlace_p -> StartUp();
	default: break;

	}

}