#include"dungeon.h"
#include"Battle.h"
#include"EnemyManager.h"

class CDungeonManager{
public:
	CDungeonManager();

	void Awake();
	void Main();
private:
	CDungeon*  nowDungeon_p;

	CEnemyManager enemyManager;

	YAN_VILLAGE yanVillage;
};