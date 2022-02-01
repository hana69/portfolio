#include"BattleManager.h"
#include<new>
////////コンストラクタ////////
CBattleManager::CBattleManager(CAlly *_me_p,CAlly *_girl_p)
	:floor(0),floorMax(0),finish(false),bgm(0),end(false),clearSound(0),clearBonus(false)
{
	for(int i=0;i<3;i++){
		new(&battles[i])CBattle(_me_p,_girl_p);
	}
}
/////////パブリック関数///////
void CBattleManager::SetEnemy(
		CEnemy* _enemy1,
		CEnemy* _enemy2,CEnemy* _enemy3,
		CEnemy* _enemy4,CEnemy* _enemy5
	){
	battles[floorMax].AddEnemy(_enemy1);
	if(_enemy2!=NULL){
		battles[floorMax].AddEnemy(_enemy2);
	}
	if(_enemy3!=NULL){
		battles[floorMax].AddEnemy(_enemy3);
	}
	if(_enemy4!=NULL){
		battles[floorMax].AddEnemy(_enemy4);
	}
	if(_enemy5!=NULL){
		battles[floorMax].AddEnemy(_enemy5);
	}

	if(floorMax<9){
		floorMax++;
	}

}

void CBattleManager::StartBattle(bool _clearBonus){
	if(bgm==0){
		bgm=LoadSoundMem("noseResource/normalbgm.mp3");
	}
	PlaySoundMem(bgm,DX_PLAYTYPE_LOOP);
	battles[0].StartBattle();
	floor=0;
	end=false;
	finish=false;
	clearBonus=_clearBonus;
}

void CBattleManager::Main(){
	static int endGraph[2]={	
		LoadGraph("noseResource/battleEnd.png"),
		LoadGraph("noseResource/battleEnd_reward.png")
	};
	static int frame=0,tempframe=0;
	battles[floor].main();
	if(!end){
		if(battles[floor].Ended()){
			if(floor==floorMax-1){
				battles[floor].Init();
				end=true;
				floorMax=0;
				StopSoundMem(bgm);
			}else{
				battles[floor].Init();
				floor++;
				battles[floor].StartBattle();
			}
			tempframe=frame;
		}
	}else{
		if(frame-tempframe > 30 ){
			if(clearBonus==false){
				DrawGraph(0,0,endGraph[0],true);
			}else{
				DrawGraph(0,0,endGraph[1],true);
			}
			if(frame-tempframe>90){
				if(Key.Pushed(KEYNAME.ENTER)){
					finish=true;
				}
			}
		}
	}
	frame++;
}

bool CBattleManager::Finished(){
	return finish;
}