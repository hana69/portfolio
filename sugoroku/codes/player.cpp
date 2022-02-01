#include "player.h"
#include"map.h"

void CPlayer::Move( int Num , int Frame , int Time ,int Max , int Debugmode ){

	if(Frame-Time==0){
		if(place+Num > Max){
			overFlag = true;
			overNum = place+Num-Max;
		}
		else{
			overFlag = false;
		}
		moveEndFlag=false;
		moveNumCount+=Num;
	}

	if(Debugmode == 2){
		if((Frame-Time)%5==0){
			moveEndFlag = true;//最初にtrueにして、最後までfalseにならなければ進まなかったと判断できる
		}
	}
	else{
		if((Frame-Time)%30==0){
			moveEndFlag = true;
		}
	}

	switch(overFlag){
	case false:
		if(Debugmode!=2){//高速モードでないとき
			if(Frame-Time < Num*30 && place < Max){
				if((Frame-Time)%30==0){ 
					place++;
					PlaySoundMem(sound.move,1);
					moveEndFlag = false;
					
					if(status==STOP_S){
						if(Num<4){
							place--;
							PlaySoundMem(sound.stop,DX_PLAYTYPE_BACK);
						}
						else{
							status=NORMAL_S;
						}
					}

				}
			}
		}
		if(Debugmode==2){//高速モードの時
			if(Frame-Time < Num*5 && place<Max){
				if((Frame-Time)%5==0){
					place++;
					PlaySoundMem(sound.move,1);
					moveEndFlag = false;

					if(status==STOP_S){
						if(Num<4){
							place--;
							PlaySoundMem(sound.stop,DX_PLAYTYPE_BACK);
						}
						else{
							status = NORMAL_S;
						}
					}
				}
			}
		}
		break;
	case true:
		if(Debugmode==2){//高速モードの時

			if(place<Max){	
				if((Frame-Time)%5==0){
					place++;
					PlaySoundMem(sound.move,1);
					moveEndFlag = false;
					if(status==STOP_S){
						if(Num<4){
							place--;
							PlaySoundMem(sound.stop,DX_PLAYTYPE_BACK);
						}
						else{
							status = NORMAL_S;
						}
					}
				}
			}
			else{
				returnFlag = true;
			}

			if(returnFlag == true && Frame-Time < Num*5){
				if((Frame-Time)%5==0){
					place--;
					PlaySoundMem(sound.move,1);
					moveEndFlag = false;
					if(Max == place+overNum){
						returnFlag = false;
					}
				}
			}

		}

		else{//高速モードでないとき
			if(place<Max && returnFlag==false){	
				if((Frame-Time)%30==0){
					place++;
					PlaySoundMem(sound.move,1);
					moveEndFlag = false;
					if(status==STOP_S){
						if(Num<4){
							place--;
							PlaySoundMem(sound.stop,DX_PLAYTYPE_BACK);
						}
						else{
							status = NORMAL_S;
						}
					}
				}		
			}
			else{
				returnFlag = true;
			}

			if(returnFlag==true && Frame-Time < Num*30){
				if(Frame-Time < Num*30){
					if((Frame-Time)%30==0){
						place--;
						PlaySoundMem(sound.move,1);
						moveEndFlag = false;
						if(Max == place+overNum){
							returnFlag = false;
							moveEndFlag=true;
						}
					}
				}
			}

		}
		break;

	}

}

void CPlayer::Draw( int scrollX,int scrollY){
	DrawGraph( x+WINDOW_WIDTH/2-25-scrollX , y+WINDOW_HEIGHT/2-25-scrollY ,playerPic, true );
	
}

void CPlayer::DrawMini(int frame){
	if(frame%60<30){
		DrawGraph( x/10, y/10,miniPic[0],true );
	}
	else{
		DrawGraph( x/10, y/10,miniPic[1],true );
	}
}

void CPlayer::GetAndReleaseCard(CardType Type,int time,int turn){
	if(cardGetType==0){
		switch(Card.Get( Type,turn)){
		case NOT_RELEASE:
			cardGetType = NOT_RELEASE;
			tempTime = time;
			break;
		case RELEASE_NEW_CARD:
			cardGetType = RELEASE_NEW_CARD;
			tempTime = time;
			break;
		case RELEASE_OLD_CARD:
			cardGetType = RELEASE_OLD_CARD;
			tempTime = time;
			break;
		default:
			cardGetType=0;
			break;
		}
	}
	
	switch(cardGetType){
		case NOT_RELEASE:
			DrawFormatString(10,360,WHITE,"%sを手に入れました",Card.NewCardName().c_str());
			if(time-tempTime > 60){
				effectEnded = true;
				cardGetType=0;
			}
			break;
		case RELEASE_NEW_CARD:
			DrawFormatString(10,360,WHITE,"%sを捨てました",Card.NewCardName().c_str());
			if(time-tempTime > 60){
				effectEnded = true;
				cardGetType=0;
			}
			break;
		case RELEASE_OLD_CARD:
			DrawFormatString(10,360,WHITE,"%sの代わりに、%sを捨てました",Card.NewCardName().c_str(),Card.ReleaseCardName().c_str());
			if(time-tempTime > 60){
				effectEnded = true;
				cardGetType=0;
			}
			break;
		default: break;
		}
}


bool CPlayer::PiGot(){
	if(piGetFlag==true){
		piGetFlag=false;
		return true;
	}
	return false;
}

bool CPlayer::PiLost(){
	if(piLostFlag==true){
		piLostFlag=false;
	 return true;
	}
	return false;
}
void CPlayer::Effect(int type,bool piValid ,int time,int turn){
	
	if(time==0){
		if(type==GO_BACK){
			place-=3;
			moveNumCount+=3;
			PlaySoundMem(sound.return_three,DX_PLAYTYPE_BACK);
		}

		if(type == GO_AHEAD){
			place+=3;
			moveNumCount+=3;
			PlaySoundMem(sound.go_three,DX_PLAYTYPE_BACK);
		}

		if(type==REST){
			switch(status){
			case NORMAL_S:
				status=REST_S;
				break;
			case REST_S:
				status=NORMAL_S;
				break;
			}
		}

		if(type==RETURN_START){
			PlaySoundMem(sound.return_start,DX_PLAYTYPE_BACK);
			moveNumCount += place;
			place = 0;
			returnStartCount++;
		}

		if(type==STOP){
			status = STOP_S;
		}
		if(type==GET_CARD){
			effectEnded = false;
			cardGetType = 0;
		}
	 }
	
	if(type==GET_CARD && !effectEnded){
		if(piValid==false){//πカードが存在しない場合
			GetAndReleaseCard( (CardType)(GetRand(CARD_TYPE_MAX-2)+1)/*0及びCARDTYPE_MAXはカードではないので、その二つを除く*/ , time , turn );
		}else{
			GetAndReleaseCard( (CardType)(GetRand(CARD_TYPE_MAX-3)+1)/*0及びCARDTYPE_MAXはカードではないので、その二つを除く*/ , time , turn );
		}
		if(Card.NewCardType()==PI){
			piGetFlag=true;
		}
		if(Card.ReleasedCardType()==PI){
			
			piGetFlag=false;
			piLostFlag=true;
		}
	}
	return;
}

void CPlayer::JudgeGoal(int goal){
	if(place==goal){
		goaled=true;
	}
}
