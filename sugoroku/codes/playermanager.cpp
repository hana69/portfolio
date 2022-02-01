#include"player.h"

#define SELECTMAX 4

void CPlayerManager::Awake(){

	LoadDivGraph("sugoroku_Resource/Mini1.png",2,2,1,5,5,player[0].miniPic);
	LoadDivGraph("sugoroku_Resource/Mini2.png",2,2,1,5,5,player[1].miniPic);
	LoadDivGraph("sugoroku_Resource/Mini3.png",2,2,1,5,5,player[2].miniPic);
	LoadDivGraph("sugoroku_Resource/Mini4.png",2,2,1,5,5,player[3].miniPic);

	playerMax = 0;
	
	cursorPic = LoadGraph("sugoroku_Resource/cursor.png");

	select.selectSpotPic = LoadGraph("sugoroku_Resource/aomidori.png");

	resultPic[0] = LoadGraph("sugoroku_Resource/result1.png");
	resultPic[1] = LoadGraph("sugoroku_Resource/result2.png");
	resultPic[2] = LoadGraph("sugoroku_Resource/result3.png");
	resultPic[3] = LoadGraph("sugoroku_Resource/result4.png");

	cardUsedFlag=false;
	cardConfirm =false;

	PMouse[0].Awake(354,240,408,274);
	PMouse[1].Awake(354,320,406,356);
	PMouse[2].Awake(480,270,572,310);

	for(int i=0;i<3;i++){
		select.Mouse[i].Awake(640,200+i*20,800,220+i*20);
	}

	for(int i=0;i<4;i++){
		player[i].Card.Awake();
		player[i].sound.move = LoadSoundMem("sugoroku_Resource/idou.mp3");
		player[i].sound.go_three = LoadSoundMem("sugoroku_Resource/3masu_susumu.mp3");
		player[i].sound.return_three = LoadSoundMem("sugoroku_Resource/modoru.mp3");
		player[i].sound.stop = LoadSoundMem("sugoroku_Resource/stop.mp3");
		player[i].sound.return_start = LoadSoundMem("sugoroku_Resource/return_start.mp3");
	}
	pointPlusSound = LoadSoundMem("sugoroku_Resource/erabu.mp3");
	PKey.Awake();

}

void CPlayerManager::Init(int firstX,int firstY){
	for(int i=0;i<4;i++){
		player[i].place = 0;
		player[i].status = NORMAL_S;
		player[i].x = firstX*50;
		player[i].y = firstY*50;
		player[i].returnFlag=false;
		player[i].overFlag=false;
		player[i].Card.Init();
		player[i].moveEndFlag=false;
		player[i].cardGetType=0;
		player[i].goaled=false;
		player[i].ranking=0;
		player[i].cardUseCount=0;
		player[i].returnStartCount=0;
		player[i].moveNumCount=0;
		for(int j=0;j<5;j++){
			player[i].bonusPoint[j]=0;
		}
		player[i].totalPoint=0;
		player[i].piGetFlag=false;
	}
	for(int i=0;i<3;i++){
		select.spotNum[i]=0;
	}

	select.endFlag = false; 
	cardSelectedFlag = false;
	cardEffect = false;

	canUse=false;

	player[0].playerPic = LoadGraph("sugoroku_Resource/player1.png");
	player[1].playerPic = LoadGraph("sugoroku_Resource/player2.png");
	player[2].playerPic = LoadGraph("sugoroku_Resource/player3.png");
	player[3].playerPic = LoadGraph("sugoroku_Resource/player4.png");

	turn=0;
	
	drawingLine=0;
	nowRanking=0;
	rankPlusFlag=false;

	piValid=false;
	nowPiRank=-1;

	piValid=true;

}

int CPlayerManager::GetPiNum(){
	return piNum[nowPiRank]-48;
}

void CPlayerManager::SetTurn(){
	turn++;
	cardUsedFlag=false;
	if(turn >= playerMax){
		turn = 0;
	}
}

void CPlayerManager::PlayNumSelect(int frame){
	
	SetFontSize(40);
	DrawFormatString(375,280,RED,"%d人",playerMax);
	SetFontSize(16);

	if(PKey.Pushed(KEY_INPUT_UP,TITLE_SOUND)){
		playerMax ++;
	}

	if(PKey.Pushed(KEY_INPUT_DOWN,TITLE_SOUND)){
		playerMax --;
	}
	
	if( PMouse[0].Pushed() &&!PMouse[1].GetFlag() && !PMouse[2].GetFlag()){
		PMouse[0].SetFlag();
	}

	if(PMouse[0].Released() ){
		playerMax++;
	}

	if( PMouse[1].Pushed() && !PMouse[0].GetFlag() && !PMouse[2].GetFlag() ){
		PMouse[1].SetFlag();
	}

	if(PMouse[1].Released() ){
		playerMax--;
	}

	if(playerMax < 1){
		playerMax = SELECTMAX+playerMax;
	}

	if(playerMax > SELECTMAX){
		playerMax = playerMax-SELECTMAX;
	}

	if(PMouse[2].Pushed() && !PMouse[0].GetFlag() && !PMouse[1].GetFlag()){
		PMouse[2].SetFlag();
	}

}

void CPlayerManager::CardDraw(){
	player[turn].Card.Draw(turn);
}

int CPlayerManager::EndNumSelect(){
	if( PMouse[2].Released() || PKey.Pushed(KEY_INPUT_RETURN,TITLE_SOUND) ){
		return 1;
	}
	return 0;
}

void CPlayerManager::SetPlace(int Num,int X , int Y){
	player[Num].x = X*50;
	player[Num].y = Y*50;
}

void CPlayerManager::CardEffect(CardType Type,int frame,LoopCase Case,int goal,int debugmode){

	switch(Type){
		case GO_ONE:
			if(player[turn].status==STOP_S){
				player[turn].status=NORMAL_S;
			}
			player[turn].Card.Draw(turn,Case);
			player[turn].Move(1,frame,temptime,goal,debugmode);
			if(player[turn].moveEndFlag==true){
				cardUsedFlag = true;
				cardEffect = false;
			}
			break;
		case GO_TWO:
			if(player[turn].status==STOP_S){
				player[turn].status=NORMAL_S;
			}
			player[turn].Card.Draw(turn,Case);
			player[turn].Move(2,frame,temptime,goal,debugmode);
			if(player[turn].moveEndFlag==true){
				cardUsedFlag = true;
				cardEffect = false;
			}
			break;
		case GO_THREE:
			if(player[turn].status==STOP_S){
				player[turn].status=NORMAL_S;
			}
			player[turn].Card.Draw(turn,Case);
			player[turn].Move(3,frame,temptime,goal,debugmode);
			if(player[turn].moveEndFlag==true){
				cardUsedFlag = true;
				cardEffect = false;
			}
			break;
		case GO_FOUR:
			if(player[turn].status==STOP_S){
				player[turn].status=NORMAL_S;
			}
			player[turn].Card.Draw(turn,Case);
			player[turn].Move(4,frame,temptime,goal,debugmode);
			if(player[turn].moveEndFlag==true){
				cardUsedFlag = true;
				cardEffect = false;
			}					
			break;
		case GO_FIVE:
			if(player[turn].status==STOP_S){
				player[turn].status=NORMAL_S;
			}
			player[turn].Card.Draw(turn,Case);
			player[turn].Move(5,frame,temptime,goal,debugmode);						
			if(player[turn].moveEndFlag==true){
				cardUsedFlag = true;
				cardEffect = false;
			}
			break;
		case GO_SIX:
			if(player[turn].status==STOP_S){
				player[turn].status=NORMAL_S;
			}
			player[turn].Card.Draw(turn,Case);
			player[turn].Move(6,frame,temptime,goal,debugmode);				
			if(player[turn].moveEndFlag==true){
				cardUsedFlag = true;
				cardEffect = false;
			}
			break;
		case GO_TEN_OR_RETURN_TEN:
			if(frame==temptime){
				go_or_return=GetRand(1);
			}
			if(player[turn].status==STOP_S){
				player[turn].status=NORMAL_S;
			}
			player[turn].Card.Draw(turn,Case);
			switch(go_or_return){
				case 1:
					player[turn].Move(10,frame,temptime,goal,debugmode);
					if(player[turn].moveEndFlag==true){
						cardUsedFlag = true;
						cardEffect = false;
					}
					break;
				case 0:
					player[turn].place -= 10;
					player[turn].moveNumCount+=10;
					if(player[turn].place <= 0){
						player[turn].place = 0;
					}
					cardUsedFlag = true;
					cardEffect=false;
				break;
			}
			
			break;

		case STEAL:
			if(canUse==false){		
				if(temptime == frame){
					SetSpotNum(turn+1);	
					for(int i=0;i<playerMax-1;i++){
						for(int j=0;j<SPOTMAX;j++){
							if(player[select.spotNum[i]-1].Card.GetHavingCardType(j) != NO_CARD){
								canUse = true;
							}
						}
					}
				}
				else{
					DrawString(10,360,"盗むカードがありません。窃盗は失敗に終わりました",WHITE);
				}
				if(frame-temptime > 60){
					cardEffect = false;
					cardUsedFlag  =true;
					cardSelectedFlag = false;
					select.endFlag = false;
				}	
			}

									
			if(select.endFlag == false && cardSelectedFlag == false && canUse == true){	
				PlayerSelect();//プレイヤーを選び終わると、この関数の中でselect.endFlagがtrueになる
				DrawString(10,360,"どのプレイヤーからカードを盗みますか？",WHITE);
				if(player[turn].Card.EndFlag()){
					DrawString(10,400,"true",WHITE);
				}
			}
			else if(select.endFlag == true && cardSelectedFlag == false&&canUse == true){
				player[select.player-1].Card.Draw(select.player-1,Case);
			
				if(PKey.Pushed(KEY_INPUT_BACK,SUGOROKU_SOUND)){
					select.endFlag = false;
				}

				if(player[select.player-1].Card.Selected(select.player-1)){
					if(player[select.player-1].Card.GetSelectingCardType() != NO_CARD){
						stoleCard = player[select.player-1].Card.GetSelectingCardType();
						cardSelectedFlag = true;
						temptime = frame;
					}
				}
				
				DrawString(10,360,"どのカードを盗みますか？",WHITE);
			}

			else if(select.endFlag == true && cardSelectedFlag == true && canUse==true){
				player[turn].GetAndReleaseCard(stoleCard,frame,turn);

				if(frame-temptime>60){
					cardEffect = false;
					cardUsedFlag  =true;
					cardSelectedFlag = false;
					select.endFlag = false;
					player[select.player-1].Card.Lost();
					canUse=false;
				}
			}
			break;
		case PI:
			if(frame==temptime){
				nowPiRank++;
			}
			if(player[turn].status==STOP_S){
				player[turn].status=NORMAL_S;
			}
			player[turn].Card.Draw(turn,Case);
			player[turn].Move(piNum[nowPiRank]-48,frame,temptime,goal,debugmode);				
			if(player[turn].moveEndFlag==true){
				cardUsedFlag = true;
				cardEffect = false;
			}
			break;
		case NO_CARD:
			break;
		default:
			break;
	}


}

bool CPlayerManager::CardIsUsed(){
	return cardUsedFlag;
}
bool CPlayerManager::EffectEnded(){
	return player[turn].effectEnded;
}
bool CPlayerManager::Get_go_or_return(){
	return go_or_return;
}

void CPlayerManager::PlayerSelect(){

	for(int i=0;i<playerMax-1;i++){
		DrawFormatString(640,200+i*20,BLACK,"プレイヤー%d",select.spotNum[i]);
	}
	DrawExtendGraph(640,200+(select.spot)*20,800,200+(select.spot)*20+20,select.selectSpotPic,true);

	if(select.Key.Pushed(KEY_INPUT_UP,SUGOROKU_SOUND) || select.Key.Hold(KEY_INPUT_UP,SELECTINTERVAL,SUGOROKU_SOUND) ){
		select.spot--;
	}
	if(select.Key.Pushed(KEY_INPUT_DOWN,SUGOROKU_SOUND) || select.Key.Hold(KEY_INPUT_DOWN,SELECTINTERVAL,SUGOROKU_SOUND)){
		select.spot++;
	}

	if(select.spot > playerMax-2 ){
		select.spot = 0;
	}
	if(select.spot < 0){
		select.spot = playerMax-2;
	}

	if(select.Key.Pushed(KEY_INPUT_RETURN,SUGOROKU_SOUND)){
		select.player = select.spotNum[select.spot];
		select.endFlag = true;
		return ;
	}

	for(int i=0;i<playerMax-1;i++){
		if(select.Mouse[i].Pushed()){
			select.Mouse[i].SetFlag();
			select.spot = i;
		}
	}

	for(int i=0;i<playerMax-1;i++){
		if(select.Mouse[i].Released()){
			select.player = select.spotNum[select.spot];
			select.endFlag = true;
			return ;
		}
	}
	

}
void CPlayerManager::SetSpotNum(int turnPlayer){
	
	for(int i=0;i<playerMax-1;i++){
		if(i+1 < turnPlayer){
			select.spotNum[i] = i+1;
		}
		if(i+1 >= turnPlayer){
			select.spotNum[i] = i+2;
		}
	}

}

void CPlayerManager::Manage(LoopCase Case , int PlaceType , int frame , int time , int DiceNum ,int PlaceMax , int debugmode){

	switch(Case){
	case USE_CARD:
		if(frame-time==0){
			cardConfirm = false; 
			cardUsedFlag = false;
			cardEffect = false;	
		}

		if(!cardConfirm && cardUsedFlag==false && cardEffect == false){
			player[turn].Card.Draw(turn,Case);
			if( player[turn].Card.Selected(turn) ){
				if(player[turn].Card.GetSelectingCardType() != NO_CARD){
					cardConfirm = true;
				}
			}
			DrawFormatString(10,360,WHITE,"%s",CARD_TXT[player[turn].Card.GetSelectingCardType()].c_str());
		}

		if(cardConfirm && cardEffect == false){
			player[turn].Card.Draw(turn,Case);
			switch(player[turn].Card.ConfirmIsEnded(USE)){
			case 1://はいを選んだ時
				player[turn].Card.SetUsedCardType();
				cardEffect = true;
				cardConfirm = false;
				temptime = frame;
				player[turn].cardUseCount++;
				break;
			case 2://いいえを選んだ時
				cardConfirm = false;
				break;
			default: break;
			}	
		}	

		if(cardEffect == true){
			CardEffect(player[turn].Card.UsedCardType(),frame,Case,PlaceMax,debugmode);
		}

		break;
	case MOVE:
		player[turn].Move( DiceNum , frame , time ,PlaceMax, debugmode );
		break;
	case EFFECT:
		player[turn].Effect( PlaceType,piValid , frame-time ,turn);
		if(player[turn].effectEnded){
			if(player[turn].PiGot()){
				piValid = true;
			}
			if(player[turn].PiLost()){
				piValid = false;
			}
		}
		break;
	case JUDGE_GOAL:
		if(frame-time==0){
			player[turn].JudgeGoal(PlaceMax);
		}
		break;
	default:
		CardDraw();
		break;
	}
	DrawFormatString(0,40,BLUE,"%d",piValid);
}

void CPlayerManager::Draw(int ScrollX , int ScrollY){

	for(int i=playerMax-1;i>=0;i--){//1,2,3,4の順で描画
		player[i].Draw( ScrollX+player[turn].x , ScrollY+player[turn].y );
	}   player[turn].Draw( ScrollX+player[turn].x , ScrollY+player[turn].y );//ターンプレイヤーは一番後

	DrawGraph( WINDOW_WIDTH/2-25+12-ScrollX , WINDOW_HEIGHT/2-50-ScrollY,cursorPic,true);
}

void CPlayerManager::DrawMini(int ScrollX,int ScrollY,int frame){
	
	for(int i=playerMax-1;i>=0;i--){
		player[i].DrawMini(frame);
	}player[turn].DrawMini(frame);

}

int CPlayerManager::GetX(int Num){
	if(Num==TURN){
		return player[turn].x;
	}
	return player[Num].x;
}

int CPlayerManager::GetY(int Num){
	if(Num==TURN){
		return player[turn].y;
	}
	return player[Num].y;
}

int CPlayerManager::GetStatus(int Num){
	if(Num==TURN){
		return player[turn].status;
	}
	return player[Num].status;
}

int CPlayerManager::GetPlace(int Num){
	if(Num==TURN){
		return player[turn].place;
	}
	return player[Num].place;
}

int CPlayerManager::GetTurn(){
	return turn;
}

CardType CPlayerManager::GetUsedCardNum(){
	return player[turn].Card.UsedCardType();
}

bool CPlayerManager::CardConfirm(){
	return cardConfirm;
}

int CPlayerManager::GetCardEffect(){
	return cardEffect;
}

bool CPlayerManager::Goaled(){
	if(player[turn].goaled){
		return true;
	}
	
	return false;
}


void CPlayerManager::DrawNowPlace(int goal){
	
	SetRanking(goal);

	for(int i=0;i<playerMax;i++){
		for(int j=0;j<playerMax;j++){
			if(player[j].ranking==i){
				DrawFormatString(643,86+drawingLine*30,BLACK,"%d位:プレイヤー%d %d",player[j].ranking+1 , j+1, goal-player[j].place);
				drawingLine++;
			}
		}
	}
	drawingLine=0;

}

void CPlayerManager::SetRanking(int goal){

	for(int i=goal;i >= 0;i--){
		for(int j=0;j<playerMax;j++){
			if(player[j].place == i){
				player[j].ranking = nowRanking;
				rankPlusFlag=true;
			}
		}

		if(rankPlusFlag==true){
			nowRanking++;
			rankPlusFlag=false;
		}
	}

	nowRanking=0;

}

void CPlayerManager::DrawRanking(int time){


	for(int rank=0;rank<playerMax;rank++){
		for(int j=0;j<playerMax;j++){
			if(player[j].ranking == rank ){
				if(time < 60){
					DrawFormatString(300,200+drawingLine*20,WHITE,"%d位：プレイヤー%d",rank+1,j+1);
				}
				if(60 <= time && time<120 ){
					DrawFormatString(250,200+drawingLine*20,WHITE,"%d位：プレイヤー%d",rank+1,j+1);
					DrawString(380,180,"カード使用回数",YELLOW);
					DrawFormatString(460,200+drawingLine*20,YELLOW,"%d回",player[j].cardUseCount);
				}
				if(120 <= time && time<180){
					DrawFormatString(170,200+drawingLine*20,WHITE,"%d位：プレイヤー%d",rank+1,j+1);
					DrawString(300,180,"カード使用回数",YELLOW);
					DrawFormatString(380,200+drawingLine*20,YELLOW,"%d回",player[j].cardUseCount);
					DrawString(420,180,"スタートに戻った回数",PURPLE);
					DrawFormatString(560,200+drawingLine*20,PURPLE,"%d回",player[j].returnStartCount );
				}
				if(180 <= time && time <=240){
					DrawFormatString(100,200+drawingLine*20,WHITE,"%d位：プレイヤー%d",rank+1,j+1);
					DrawString(230,180,"カード使用回数",YELLOW);
					DrawFormatString(310,200+drawingLine*20,YELLOW,"%d回",player[j].cardUseCount);
					DrawString(350,180,"スタートに戻った回数",PURPLE);
					DrawFormatString(490,200+drawingLine*20,PURPLE,"%d回",player[j].returnStartCount );
					DrawString(530,180,"動いたマスの数",GREEN);
					DrawFormatString(590,200+drawingLine*20,GREEN,"%dマス",player[j].moveNumCount);
				}
				if( 240 < time && 680-(time-300) >= 260 ){
					DrawFormatString(100,200+drawingLine*20,WHITE,"%d位：プレイヤー%d",rank+1,j+1);
					DrawString(330,180,"カード使用回数",YELLOW);
					DrawString(450,180,"スタートに戻った回数",PURPLE);
					DrawString(630,180,"動いたマスの数",GREEN);
					DrawFormatString(250,200+drawingLine*20,WHITE,"%dポイント",player[j].totalPoint);
					
					for(int k=0;k<3;k++){
						if(player[j].bonusPoint[k] > 0){
							switch(k){
							case 0:
								if(time-300<0){
									DrawFormatString(350,200+drawingLine*20,YELLOW,"+%d",player[j].bonusPoint[k]);
								}
								else if(350-(time-300) > 320 ){
									DrawFormatString(350-(time-300),200+drawingLine*20,YELLOW,"+%d",player[j].bonusPoint[k]);
								}else if(350-(time-300) == 320 || 350-(time-300) == 321){
									player[j].totalPoint+=player[j].bonusPoint[k];
									PlaySoundMem(pointPlusSound,DX_PLAYTYPE_BACK);
								}
								
								break;
							case 1:
								if(time-300<0){
									DrawFormatString(580,200+drawingLine*20,PURPLE,"+%d",player[j].bonusPoint[k]);
								}
								else if(580-(time-300) > 320 ){
									DrawFormatString(580-(time-300),200+drawingLine*20,PURPLE,"+%d",player[j].bonusPoint[k]);
								}else if(580-(time-300) == 320 || 580-(time-300) == 321){
									player[j].totalPoint+=player[j].bonusPoint[k];
									PlaySoundMem(pointPlusSound,DX_PLAYTYPE_BACK);
								}
									break;
							case 2:
								if((time-300)<0){
									DrawFormatString(680,200+drawingLine*20,GREEN,"+%d",player[j].bonusPoint[k]);
								}else if(680-(time-300) > 320 ){
									DrawFormatString(680-(time-300),200+drawingLine*20,GREEN,"+%d",player[j].bonusPoint[k]);
								}else if(680-(time-300) == 320 || 680-(time-300) == 321){
									player[j].totalPoint+=player[j].bonusPoint[k];
									PlaySoundMem(pointPlusSound,DX_PLAYTYPE_BACK);
								}
								
								break;
							}
						}
					}
				}
				if(680-(time-300) < 260 && 680-(time-300) >= 200 ){
					DrawFormatString(300,200+drawingLine*20,WHITE,"%d位：プレイヤー%d",rank+1,j+1);
					DrawFormatString(450,200+drawingLine*20,WHITE,"%dポイント",player[j].totalPoint);
				}
				if(680-(time-300) == 200){
					for(int i=0;i<playerMax;i++){
						for(int j=0;j<playerMax;j++){
							if(player[i].totalPoint < player[j].totalPoint && player[i].ranking<player[j].ranking){
								tempRank = player[i].ranking;
								player[i].ranking = player[j].ranking;
								player[j].ranking = tempRank;
							}
						}
					}
					if( player[j].Card.PiCheck()==true ){
						player[j].totalPoint+=1;	
					}
				}
				if(680-(time-300) < 200){
					if(rank==0){
						DrawGraph(0,0,resultPic[j],true);
						if(time%60>30){
							DrawFormatString(300,200+drawingLine*20,WHITE,"%d位：プレイヤー%d",rank+1,j+1);
							DrawFormatString(450,200+drawingLine*20,WHITE,"%dポイント",player[j].totalPoint);
						}else{
							DrawFormatString(300,200+drawingLine*20,YELLOW,"%d位：プレイヤー%d",rank+1,j+1);
							DrawFormatString(450,200+drawingLine*20,YELLOW,"%dポイント",player[j].totalPoint);
						}
						
					}else{
						DrawFormatString(300,200+drawingLine*20,WHITE,"%d位：プレイヤー%d",rank+1,j+1);
						DrawFormatString(450,200+drawingLine*20,WHITE,"%dポイント",player[j].totalPoint);
					}
					if( player[j].Card.PiCheck()==true ){
						DrawString(570,200+drawingLine*20," πカードボーナスで+1！",RED);
					}
				}
				drawingLine++;
			}
		}
	}

	if(time==240){
		SetBonusPoint();
	}

	drawingLine=0;
}

void CPlayerManager::SetBonusPoint(){

	for(int j=0;j<playerMax;j++){
		if(player[j].ranking==0){
			player[j].totalPoint+=5;
		}
		else if(player[j].ranking==1){
			player[j].totalPoint+=3;
		}else{
			player[j].totalPoint+=1;
		}
		
	}

	for(int i=0;i<playerMax;i++){
			for(int j=0;j<playerMax;j++){
				if(player[i].cardUseCount < player[j].cardUseCount ){
					break;
				}
				if(j==playerMax-1){
					player[i].bonusPoint[0] += (int)(player[i].cardUseCount/5+1);
					
				}
			}
		}
		for(int i=0;i<playerMax;i++){
			for(int j=0;j<playerMax;j++){
				if(player[i].returnStartCount < player[j].returnStartCount ){
					break;
				}
				if(j==playerMax-1){
					player[i].bonusPoint[1] += (int)(player[i].returnStartCount/3+1);
				
				}
			}
		}
		for(int i=0;i<playerMax;i++){
			for(int j=0;j<playerMax;j++){
				if(player[i].moveNumCount < player[j].moveNumCount ){
					break;
				}
				if(j==playerMax-1){
					player[i].bonusPoint[2] += (int)(player[i].moveNumCount/100+1);
					
				}

			}
		}


}