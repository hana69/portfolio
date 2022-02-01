#include"card.h"

CCard::CCard(){
	
	for(int i=0;i<SPOTMAX;i++){
		CardMouse[i].Awake(640,270+i*20,800,270+i*20+20);
	}

	for(int i=0;i<CONFIRMCASE_MAX;i++){
		confirm[i].Mouse[0].Awake(640,370,800,410);
		confirm[i].Mouse[1].Awake(640,440,800,480);
	}

	selectSpot = 0;
	tempType = NO_CARD;

	confirm[USE].selectSpot="いいえ";
	confirm[RELEASE].selectSpot="いいえ";
	confirm[GET].selectSpot="いれかえる";

}

void CCard::Awake(){
	confirm[USE].picture = LoadGraph("sugoroku_Resource/YESorNO.png");//　　　　｝捨てる時、使う時は　はい/いいえ　で確認
	confirm[RELEASE].picture = LoadGraph("sugoroku_Resource/YESorNO.png");//

	confirm[GET].picture = LoadGraph("sugoroku_Resource/AKIRAMERUorIREKAERU.png");

	selectSpotPic = LoadGraph("sugoroku_Resource/aomidori.png");

	for(int i=0;i<CONFIRMCASE_MAX;i++){
		confirm[i].selectSpotPic = LoadGraph("sugoroku_Resource/aomidori.png");
	}
	CardKey.Awake();
}

void CCard::Init(){
	for(int i=0;i<SPOTMAX;i++){
		cardType[i] = NO_CARD;
	}

	selectSpot = 0;
	tempType = NO_CARD;

	confirm[USE].selectSpot="いいえ";
	confirm[RELEASE].selectSpot="いいえ";
	confirm[GET].selectSpot="いれかえる";

	newCardType=NO_CARD;

	endFlag=true;
}

void CCard::Lost(){
	cardType[selectSpot] = NO_CARD;
}

void CCard::SetUsedCardType(){
	usedCardType=cardType[selectSpot];

	if(cardType[selectSpot]!=PI){
		cardType[selectSpot] = NO_CARD;
	}

}

CardType CCard::NewCardType(){
	return newCardType;
}

CardType CCard::UsedCardType(){
	return usedCardType;
}

CardType CCard::ReleasedCardType(){
	return releasedCardType;
}

string CCard::NewCardName(){
	return CARD_NAME[newCardType];
}
string CCard::ReleaseCardName(){
	return CARD_NAME[releasedCardType];
}

CardType CCard::GetHavingCardType(int spot){
	return cardType[spot];
}


int CCard::Get(CardType NewCard,int turn){

	if(endFlag==true){
		newCardType = NewCard;
		releasedCardType=NO_CARD;
		endFlag = false;
		changeFlag = false;

		for(int i=0;i<SPOTMAX;i++){	
			if(cardType[i] == NO_CARD){
				cardType[i] = newCardType ;
				endFlag = true;
				return NOT_RELEASE;
			}
		}

	}

	if(endFlag==false && changeFlag==false){

		DrawFormatString(10,360,WHITE,"%sを手に入れましたが、これ以上カードは持てません",CARD_NAME[newCardType].c_str());
		
		switch(ConfirmIsEnded(GET)){
		case 1://あきらめる　が選ばれた時
			endFlag = true;
			return RELEASE_NEW_CARD;
			break;
		case 2://いれかえる　が選ばれたとき
			changeFlag = true;
			break;
		default:break;
		}
	
	}

	if(endFlag==false && changeFlag==true){
		DrawFormatString(10,360,WHITE,"%sをどのカードと入れ替えますか？",CARD_NAME[newCardType].c_str());

		if(CardKey.Pushed(KEY_INPUT_BACK,SUGOROKU_SOUND)){
			changeFlag=false;
		}

		if(Selected(turn)){
			releasedCardType = cardType[selectSpot];
			cardType[selectSpot] = newCardType;
			changeFlag = false;
			endFlag = true;
			return RELEASE_OLD_CARD;
		}
	}

	return false;

}

bool CCard::Selected(int turn){
	
	Draw(turn);
	DrawExtendGraph(640,270+selectSpot*20,800,290+selectSpot*20,selectSpotPic,true);

	if(CardKey.Pushed(KEY_INPUT_UP,SUGOROKU_SOUND) || CardKey.Hold(KEY_INPUT_UP,SELECTINTERVAL,SUGOROKU_SOUND) ){
		selectSpot--;
	}
	if(CardKey.Pushed(KEY_INPUT_DOWN,SUGOROKU_SOUND) || CardKey.Hold(KEY_INPUT_DOWN,SELECTINTERVAL,SUGOROKU_SOUND)){
		selectSpot++;
	}

	if(selectSpot >= SPOTMAX ){
		selectSpot = 0;
	}
	if(selectSpot < 0){
		selectSpot = SPOTMAX-1;
	}

	if(CardKey.Pushed(KEY_INPUT_RETURN,SUGOROKU_SOUND)){
		return true;
	}

	for(int i=0;i<SPOTMAX;i++){
		
		for(int j=0;j<SPOTMAX;j++){		
			if(i!=j){
				if(CardMouse[j].GetFlag()==true){
					break;
				}
			}
		}

		if(CardMouse[i].Pushed()){
			selectSpot = i;
			CardMouse[i].SetFlag();
		}

	}

	for(int i=0;i<SPOTMAX;i++){
		if(CardMouse[i].Released()){
			return true;
		}
	}

	return false;

}

int CCard::ConfirmIsEnded(ConfirmCase Case){

	switch(Case){
	case USE://使う時の確認
		DrawGraph(640,370,confirm[USE].picture,true);
		if(confirm[USE].Mouse[1].GetFlag()==false && confirm[USE].Mouse[0].Pushed()){
			confirm[USE].Mouse[0].SetFlag();
			confirm[USE].selectSpot="はい";
		}
		if(confirm[USE].Mouse[0].GetFlag()==false && confirm[USE].Mouse[1].Pushed()){
			confirm[USE].Mouse[1].SetFlag();
			confirm[USE].selectSpot = "いいえ";
		}

		if(confirm[USE].selectSpot=="はい"){
			if(CardKey.Pushed(KEY_INPUT_UP,SUGOROKU_SOUND) || CardKey.Pushed(KEY_INPUT_DOWN,SUGOROKU_SOUND)){
				confirm[USE].selectSpot = "いいえ";
			}
			DrawGraph(640,370,confirm[USE].selectSpotPic,true);
			if( CardKey.Pushed(KEY_INPUT_RETURN,SUGOROKU_SOUND) || confirm[USE].Mouse[0].Released() ){
				
				return 1;
			}
		}

		if(confirm[USE].selectSpot=="いいえ"){
			if(CardKey.Pushed(KEY_INPUT_UP,SUGOROKU_SOUND) || CardKey.Pushed(KEY_INPUT_DOWN,SUGOROKU_SOUND)){
				confirm[USE].selectSpot = "はい";
			}
			DrawGraph(640,440,confirm[USE].selectSpotPic,true);		
			if( CardKey.Pushed(KEY_INPUT_RETURN,SUGOROKU_SOUND) || confirm[USE].Mouse[1].Released()){
				return 2;
			}
		}	
		break;
	case RELEASE://捨てる時の確認
		DrawGraph(640,370,confirm[RELEASE].picture,true);
		if(confirm[RELEASE].Mouse[1].GetFlag()==false && confirm[RELEASE].Mouse[0].Pushed()){
			confirm[RELEASE].Mouse[0].SetFlag();
			confirm[RELEASE].selectSpot="はい";
		}
		if(confirm[RELEASE].Mouse[0].GetFlag()==false && confirm[RELEASE].Mouse[1].Pushed()){
			confirm[RELEASE].Mouse[1].SetFlag();
			confirm[RELEASE].selectSpot = "いいえ";
		}

		if(confirm[RELEASE].selectSpot=="はい"){
			if(CardKey.Pushed(KEY_INPUT_UP,SUGOROKU_SOUND) || CardKey.Pushed(KEY_INPUT_DOWN,SUGOROKU_SOUND)){
				confirm[RELEASE].selectSpot = "いいえ";
			}
			DrawGraph(640,370,confirm[RELEASE].selectSpotPic,true);
			if( CardKey.Pushed(KEY_INPUT_RETURN,SUGOROKU_SOUND) || confirm[RELEASE].Mouse[0].Released() ){
				return 1;
			}
		}

		if(confirm[RELEASE].selectSpot=="いいえ"){
			if(CardKey.Pushed(KEY_INPUT_UP,SUGOROKU_SOUND) || CardKey.Pushed(KEY_INPUT_DOWN,SUGOROKU_SOUND)){
				confirm[RELEASE].selectSpot = "はい";
			}
			DrawGraph(640,440,confirm[RELEASE].selectSpotPic,true);		
			if( CardKey.Pushed(KEY_INPUT_RETURN,SUGOROKU_SOUND) || confirm[RELEASE].Mouse[1].Released()){
				return 2;
			}
		}	
		break;
	case GET://カードをゲットした時の確認
		DrawGraph(640,370,confirm[GET].picture,true);
		if(confirm[GET].Mouse[1].GetFlag()==false && confirm[GET].Mouse[0].Pushed()){
			confirm[GET].Mouse[0].SetFlag();
			confirm[GET].selectSpot="あきらめる";
		}
		if(confirm[GET].Mouse[0].GetFlag()==false && confirm[GET].Mouse[1].Pushed()){
			confirm[GET].Mouse[1].SetFlag();
			confirm[GET].selectSpot = "いれかえる";
		}

		if(confirm[GET].selectSpot=="あきらめる"){
			if(CardKey.Pushed(KEY_INPUT_UP,SUGOROKU_SOUND) || CardKey.Pushed(KEY_INPUT_DOWN,SUGOROKU_SOUND)){
				confirm[GET].selectSpot = "いれかえる";
			}
			DrawGraph(640,370,confirm[GET].selectSpotPic,true);
			if( CardKey.Pushed(KEY_INPUT_RETURN,SUGOROKU_SOUND) || confirm[GET].Mouse[0].Released() ){
				return 1;
			}
		}

		if(confirm[GET].selectSpot=="いれかえる"){
			if(CardKey.Pushed(KEY_INPUT_UP,SUGOROKU_SOUND) || CardKey.Pushed(KEY_INPUT_DOWN,SUGOROKU_SOUND)){
				confirm[GET].selectSpot = "あきらめる";
			}
			DrawGraph(640,440,confirm[GET].selectSpotPic,true);		
			if( CardKey.Pushed(KEY_INPUT_RETURN,SUGOROKU_SOUND) || confirm[GET].Mouse[1].Released()){
				return 2;
			}
		}	
		break;

	default:break;
	}

	return 0;

}

void CCard::Draw( int player , LoopCase loopCase ){

	if(loopCase==USE_CARD){
		DrawExtendGraph(640,270+selectSpot*20,800,290+selectSpot*20,confirm[0].selectSpotPic,true);//confirm自体とは関係なくselectSpotPicを使いたかっただけ
	}

	DrawFormatString(640,250,BLACK,"プレイヤー%dのカード",player+1);
	for(int i=0;i<SPOTMAX;i++){
		DrawString(650,270+i*20,CARD_NAME[ cardType[i] ].c_str(),BLUE);
	}

}

bool CCard::PiCheck(){
	
	for(int i=0;i<SPOTMAX;i++){
		if(cardType[i]==PI){
			return true;
		}
	}

	return false;

}

CardType CCard::GetSelectingCardType(){
	return cardType[selectSpot];
}

//int CCard::CRelease::Confirm(){
//
//	switch(Case){
//	case 0:
//		DrawGraph(640,0,confirmPic[Case],true);
//		if(RKey.Pushed(KEY_INPUT_UP) || RKey.Pushed(KEY_INPUT_DOWN)){
//			Case = 1;
//		}
//		if(RKey.Pushed(KEY_INPUT_RETURN)){
//			return 1;
//		}
//		break;
//	case 1:
//		DrawGraph(0,0,confirmPic[Case],true);
//		if(RKey.Pushed(KEY_INPUT_UP) || RKey.Pushed(KEY_INPUT_DOWN)){
//			Case=0;
//		}
//		if(RKey.Pushed(KEY_INPUT_RETURN)){
//			return 2;
//		}
//		break;
//	default:return 0;break;
//	}
//	return 0;
//}
//
//bool CCard::CRelease::Selected(CCard &Card_p){
//
//	if(Case==2){
//
//		if( Card_p.Selected() ){
//
//		}
//
//		if(RKey.Pushed(KEY_INPUT_RETURN)){
//			Card_p.cardType[Card_p.selectSpot] = NO_CARD;
//		}
//
//	}
//	return false;
//}
