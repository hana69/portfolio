#include"DungeonManager.h"


CDungeonManager::CDungeonManager():
	yanVillage("‚â‚ñ‚Ì‘ƒŒA",10)
{
	nowDungeon_p = &yanVillage;
}

void CDungeonManager::Awake(){

}

void CDungeonManager::Main(){
	nowDungeon_p -> Main();
}