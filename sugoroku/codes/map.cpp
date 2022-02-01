#include"map.h"
#include"player.h"

CIntData placedata("sugoroku_Resource/placedata.txt");

void CMap::Awake(){	
	mapNum=1;
	MapMouse[UP].Awake(355,240,407,274);
	MapMouse[DOWN].Awake(355,318,406,356);
	MapMouse[ENTER].Awake(480,270,572,310);
	MapMouse[DRUG].Awake(0,0,640,480);

	MapKey.Awake();

	goal=0;
	
	for(int i=0;i<100;i++){
		placeType[i]=0;
		placeX[i]=0;
		placeY[i]=0;
		placePic[i]=0;
	}

	scrollx=0;
	scrolly=0;

	tempScrollx=0;
	tempScrolly=0;

	ScrollCase=false;

	
	char adress[100];
	for(int i=0;i<5;i++){
		sprintf(adress,"sugoroku_Resource/haikei%d.png",i+1);
		haikeiPic[i]=LoadGraph(adress);
	}
	haikeiNum=0;
}

void CMap::Init(){

	if(mapNum==0){
		mapNum = GetRand(MAPMAX-1)+1;
	}

	switch(mapNum){
	case 1:
		mapPic[1] = LoadGraph("sugoroku_Resource/map1.png");
		mapdata[1] = LoadSoftImage("sugoroku_Resource/map1.png");
		break;
	case 2:
		mapPic[2] = LoadGraph("sugoroku_Resource/map2.png");
		mapdata[2] = LoadSoftImage("sugoroku_Resource/map2.png");
		break;
	case 3:
		mapPic[3] = LoadGraph("sugoroku_Resource/map3.png");
		mapdata[3] = LoadSoftImage("sugoroku_Resource/map3.png");
		break;
	case 4:
		mapPic[4] = LoadGraph("sugoroku_Resource/map4.png");
		mapdata[4] = LoadSoftImage("sugoroku_Resource/map4.png");
		break;
	case 5:
		mapPic[5] =  LoadGraph("sugoroku_Resource/map5.png");
		mapdata[5] =  LoadSoftImage("sugoroku_Resource/map5.png");
		break;
	case 6:
		mapPic[6] =  LoadGraph("sugoroku_Resource/map6.png");
		mapdata[6] =  LoadSoftImage("sugoroku_Resource/map6.png");
		break;
	case 7:
		mapPic[7] =  LoadGraph("sugoroku_Resource/map7.png");
		mapdata[7] =  LoadSoftImage("sugoroku_Resource/map7.png");
		break;
	}

	placedata.ReadData();
	
	for(int i=(mapNum-1)*100;i<=(mapNum-1)*100+100;i++){
		if(placedata.LeftData[i]==0 && placedata.RightData[i]==0){
			goal = i-1-(mapNum-1)*100;
			break;
		}
	}

	for( int i=0; i < DATAWIDTH; i++ ){
		for( int j=0; j < DATAHIGHT;j++ ){
			GetPixelSoftImage( mapdata[mapNum] , i , j , &Data[i][j].R , &Data[i][j].G , &Data[i][j].B , &Data[i][j].A );
		}
	}

	for( int i=0; i < DATAWIDTH*2; i++ ){
		for( int j=0; j < DATAHIGHT*2; j++ ){
			for(int k=0;k <= goal;k++){
			
				if( Data[i][j].R != 255 || Data[i][j].G != 255 || Data[i][j].B != 255 ){
					if(placedata.LeftData[k+(mapNum-1)*100] == i){
						placeX[k] = i;
					}
					if(placedata.RightData[k+(mapNum-1)*100] == j){
						placeY[k] = j;
					}
					if(placedata.LeftData[k+(mapNum-1)*100]==i && placedata.RightData[k+(mapNum-1)*100]==j){
						placeType[k] = GetColor( Data[i][j].R,Data[i][j].G,Data[i][j].B );
					}
				}
		
			}
		}
	}

	
	for(int i=0;i<=goal;i++){
		if(placeType[i]==GO_AHEAD){
			placePic[i] = LoadGraph("sugoroku_Resource/susumu.png");
		}
		if(placeType[i]==GO_BACK){
			placePic[i] = LoadGraph("sugoroku_Resource/modoru.png");
		}
		if(placeType[i]==REST){
			placePic[i] = LoadGraph("sugoroku_Resource/yasumi.png");
		}
		if(placeType[i]==STOP){
			placePic[i] = LoadGraph("sugoroku_Resource/stop.png");
		}
		if(placeType[i]==GET_CARD){
			placePic[i] = LoadGraph("sugoroku_Resource/card.png");
		}
		if(placeType[i]==RETURN_START){
			placePic[i] = LoadGraph("sugoroku_Resource/sutato_ni_modoru.png");
		}
		if(placeType[i]==BRANK){
			placePic[i] = LoadGraph("sugoroku_Resource/nanimonai.png");
		}
		if(placeType[i]==GOAL ){
			placePic[i] = LoadGraph("sugoroku_Resource/goal.png");
		}
		if(placeType[i]==START){
			placePic[i] = LoadGraph("sugoroku_Resource/start.png");
		}
	}

	haikeiNum=GetRand(4);

}

void CMap::Draw(){
	
	DrawExtendGraph(WINDOW_WIDTH/2-25-scrollx,WINDOW_HEIGHT/2-25-scrolly,WINDOW_WIDTH/2-25+1600-scrollx,WINDOW_HEIGHT/2-25+1200-scrolly,mapPic[mapNum],true);
	DrawExtendGraph(0,0,640,480,haikeiPic[haikeiNum],true);
	for(int i=0;i<=goal;i++){
		
		if( placePic[i]!=0 && 
			WINDOW_WIDTH/2-25+placeX[i]*50-scrollx < 640  && 
			WINDOW_WIDTH/2+25+placeX[i]*50-scrollx > 0    && 
			WINDOW_HEIGHT/2-25+placeY[i]*50-scrolly < 480 && 
			WINDOW_HEIGHT/2+25+placeY[i]*50-scrolly > 0   
		){//////////////画面内の時のみ描画
			DrawGraph(WINDOW_WIDTH/2-25+placeX[i]*50-scrollx,WINDOW_HEIGHT/2-25+placeY[i]*50-scrolly,placePic[i],true);
		}

	}
	

}

void CMap::DrawMini(){
	
	
	DrawExtendGraph(0,0,160,120,mapPic[mapNum],true);
	DrawBox(0,0,160,120,BLACK,false);
	
	DrawBox(scrollx/10-(int)29.5 , scrolly/10-(int)21.5 , scrollx/10+64-(int)29.5 , scrolly/10+48-(int)21.5,BLUE,false);

}

void CMap::Select(){

	SetFontSize(40);
	if(mapNum==0){
		DrawString(300,280,"ランダム",RED);
	}
	else{
		DrawFormatString(280,280,RED,"ステージ%d",mapNum);
	}
	SetFontSize(16);

	if(MapKey.Pushed(KEY_INPUT_UP, TITLE_SOUND)){
		mapNum++;	
	}
	
	if(MapKey.Pushed(KEY_INPUT_DOWN,TITLE_SOUND)){
		mapNum--;
	}

	if( MapMouse[UP].Pushed() && MapMouse[DOWN].GetFlag()==false && MapMouse[ENTER].GetFlag()==false ){
		MapMouse[UP].SetFlag();
	}

	if(MapMouse[UP].Released()){
		mapNum++;
	}

	if( MapMouse[DOWN].Pushed() && MapMouse[UP].GetFlag()==false && MapMouse[ENTER].GetFlag()==false ){
		MapMouse[DOWN].SetFlag();
	}

	if(MapMouse[DOWN].Released()){
		mapNum--;
	}

	if(mapNum < 0){
		mapNum = MAPMAX+1+mapNum;
	}
	
	if(mapNum > MAPMAX){
		mapNum = mapNum-1-MAPMAX;
	}

	if(MapMouse[ENTER].Pushed() && MapMouse[UP].GetFlag()==false && MapMouse[DOWN].GetFlag()==false){
		MapMouse[ENTER].SetFlag();
	}

}

bool CMap::EndSelect(){

	if(MapMouse[ENTER].Released() || MapKey.Pushed(KEY_INPUT_RETURN, TITLE_SOUND) ){
		return true;
	}

	return false;
}

void CMap::Look(){

	if(!ScrollCase){
		tempScrollx = scrollx;
		tempScrolly = scrolly;
		ScrollCase = 1;
	}

	else{
		if(CheckHitKey(KEY_INPUT_RIGHT)){
			scrollx += SCROLLSPEED ;
		}
		if(CheckHitKey(KEY_INPUT_LEFT)){
			scrollx -= SCROLLSPEED ;
		}
		if(CheckHitKey(KEY_INPUT_UP)){
			scrolly -= SCROLLSPEED ;
		}
		if(CheckHitKey(KEY_INPUT_DOWN)){
			scrolly += SCROLLSPEED ;
		}
		
		if(MapMouse[DRUG].GetFlag()==true){
			scrollx += MapMouse[DRUG].GetChangeX();
			scrolly += MapMouse[DRUG].GetChangeY();
		}

		MapMouse[DRUG].SetTemp();

	}

	if(scrollx < SC_LIMIT_LEFT ){
		scrollx = SC_LIMIT_LEFT;
	}
	if(scrollx > SC_LIMIT_RIGHT){
		scrollx = SC_LIMIT_RIGHT;
	}
	if(scrolly < SC_LIMIT_TOP){
		scrolly = SC_LIMIT_TOP;
	}
	if(scrolly > SC_LIMIT_BOTTOM){
		scrolly = SC_LIMIT_BOTTOM;
	}

}

void CMap::Back(){
	ScrollCase=0;
}

void CMap::SetScroll(int X , int Y){
	if(!ScrollCase){
		scrollx = X;
		scrolly = Y;
		tempScrollx = scrollx;
		tempScrolly = scrolly;
	}
}

int CMap::GetPlaceType(int Num){
	return placeType[Num];	
}

int CMap::GetPlaceX(int Num){
		return placeX[Num];
}

int CMap::GetPlaceY(int Num){
	return placeY[Num];
}

int CMap::GetScrollChangeX(){
	return scrollx-tempScrollx;
}

int CMap::GetScrollChangeY(){
	return scrolly-tempScrolly;
}

int CMap::GetGoal(){
	return goal;
}