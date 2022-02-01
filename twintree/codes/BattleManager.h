#include"Battle.h"

class CBattleManager{
public:
	CBattleManager(CAlly *_me_p,CAlly *_girl_p);

	void SetEnemy(
		CEnemy* _enemy1,
		CEnemy* _enemy2=NULL,CEnemy* _enemy3=NULL,
		CEnemy* _enemy4=NULL,CEnemy* _enemy5=NULL);

	void StartBattle(bool _clearBonus);

	void Main();

	bool Finished();
private:
	CBattle battles[10];
	int bgm;
	int clearSound;
	bool clearBonus;
	int floor;
	int floorMax;
	bool finish;
	bool end;
};