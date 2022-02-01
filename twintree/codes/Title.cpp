#include"Title.h"
CTitle::CTitle(){
	for(int i=0;i<2;i++){
		titleGraph[i]=0;
	}
	haikeiPic=0;
	scene=TITLE;
	end =false;
}

void CTitle::Awake(){
	haikeiPic=LoadGraph("noseResource/haikei_normal.png");

	titleGraph[0]=LoadGraph("noseResource/Title0.png");
	titleGraph[1]=LoadGraph("noseResource/Title1.png");

	
}

void CTitle::Draw(){
	static int frame=0;
	switch(scene){
	case TITLE:
		TitleDraw();
		break;
	case HTP:
		HTPDraw();
		break;
	}
	frame++;
}

bool CTitle::GetEnd(){
	return end;
}

void CTitle::TitleDraw(){
	DrawExtendGraph(0,0,WINDOW_WIDTH,WINDOW_HEIGHT,haikeiPic,true);
	static int titleScene=1;
	NumSelect_UD(&titleScene,0,1);
	DrawGraph(0,0,titleGraph[titleScene],true);

	end=false;
	
	if(Key.Pushed(KEYNAME.ENTER)){
		if(titleScene==0){
			end = true;
		}else{
			scene=HTP;
		}
	}
}

void CTitle::HTPDraw(){
	if(Key.Pushed(KEYNAME.ENTER) || Key.Pushed(KEYNAME.BACK)){
		scene=TITLE;
	}
}