#include "title.h"

void CTitle::Awake(){
	for(int i=0;i<10;i++){
		titlegazou[i]=0;
	}
	titlegazou[0] = LoadGraph("sugoroku_Resource/title0.png");
	titlegazou[1] = LoadGraph("sugoroku_Resource/title1.png");
	titlegazou[2] = LoadGraph("sugoroku_Resource/title2.png");
	titlegazou[3] = LoadGraph("sugoroku_Resource/title3.png");
	titlegazou[4] = LoadGraph("sugoroku_Resource/title4.png");

	char adress[100];
	for(int i=0;i<6;i++){
		sprintf(adress,"sugoroku_Resource/dice%d.png",i+1);
		dicePic[i]=LoadGraph(adress);
	}

	frame=0;
	Case = 0;

	TMouse[0].Awake(314,210,437,237);
	TMouse[1].Awake(300,270,458,297);
	TMouse[2].Awake(312,333,439,359);
	TKey.Awake();
}

void CTitle::Draw(int NowCase , int frame){
	switch(NowCase){
	case TITLE:
		DrawGraph( 0 , 0 , titlegazou[Case] , true);	
		
		for(int i=0;i<23;i++){
			DrawExtendGraph(0,i*20,20,i*20+20,dicePic[((frame%120)/3+i)%6],true);
		}
		for(int j=0;j<40;j++){
			DrawExtendGraph(j*20,0,j*20+20,20,dicePic[((frame%120)/3+j)%6],true);
		}
		for(int i=0;i<23;i++ ){
			DrawExtendGraph(780,i*20,800,i*20+20,dicePic[((frame%120)/3+i)%6],true);
		}
		for(int j=0;j<40;j++){
			DrawExtendGraph(j*20,460,j*20+20,480,dicePic[((frame%120)/3+j)%6],true);
		}

		//if(frame%60==0){
		//	num=GetRand(5);
		//}
		break;
	case SELECT_PLAYNUM:
		DrawGraph(0,0,titlegazou[3],true);
		
		for(int i=0;i<23;i++){
			DrawExtendGraph(0,i*20,20,i*20+20,dicePic[((frame%120)/3+i)%6],true);
		}
		for(int j=0;j<40;j++){
			DrawExtendGraph(j*20,0,j*20+20,20,dicePic[((frame%120)/3+j)%6],true);
		}
		for(int i=0;i<23;i++ ){
			DrawExtendGraph(780,i*20,800,i*20+20,dicePic[((frame%120)/3+i)%6],true);
		}
		for(int j=0;j<40;j++){
			DrawExtendGraph(j*20,460,j*20+20,480,dicePic[((frame%120)/3+j)%6],true);
		}
		break;
	case SELECT_STAGE:
		DrawGraph(0,0,titlegazou[4],true);
		
		for(int i=0;i<23;i++){
			DrawExtendGraph(0,i*20,20,i*20+20,dicePic[((frame%120)/3+i)%6],true);
		}
		for(int j=0;j<40;j++){
			DrawExtendGraph(j*20,0,j*20+20,20,dicePic[((frame%120)/3+j)%6],true);
		}
		for(int i=0;i<23;i++ ){
			DrawExtendGraph(780,i*20,800,i*20+20,dicePic[((frame%120)/3+i)%6],true);
		}
		for(int j=0;j<40;j++){
			DrawExtendGraph(j*20,460,j*20+20,480,dicePic[((frame%120)/3+j)%6],true);
		}
		break;
	}
}

void CTitle::ModeSelect(int NowCase){

	frame++;

	if(TKey.Pushed(KEY_INPUT_UP,TITLE_SOUND) || TKey.Hold(KEY_INPUT_UP,10,TITLE_SOUND)){
		Case--;
	}
	if(TKey.Pushed(KEY_INPUT_DOWN,TITLE_SOUND) || TKey.Hold(KEY_INPUT_DOWN,10,TITLE_SOUND)){
		Case++;
	}

	if(Case > 2){
		Case = 0;
	}
	if(Case < 0){
		Case = 2;
	}

	for(int i=0;i<3;i++){
		if(TMouse[i].Pushed()){
			TMouse[i].SetFlag();
			Case = i;
		}
	}

}

int CTitle::EndModeSelect(){

	if( TKey.Pushed(KEY_INPUT_RETURN,TITLE_SOUND) ){		
		return Case+1;
	}

	if( TMouse[0].Released()){
		return 1;
	}
	if( TMouse[1].Released() ){	
		return 2;
	}
	if( TMouse[2].Released() ){
		return 3;
	}
	

	return 0;
}
