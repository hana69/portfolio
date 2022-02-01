#include "text.h"

void CTxt::CardEffectDraw(CardType CardType,int piNum , bool go_or_return){
	
	switch(CardType){
	case GO_ONE:
		DrawString(10,360,"１マス進みました",WHITE);
		break;
	case GO_TWO:
		DrawString(10,360,"２マス進みました",WHITE);
		break;
	case GO_THREE:
		DrawString(10,360,"３マス進みました",WHITE);
		break;
	case GO_FOUR:
		DrawString(10,360,"４マス進みました",WHITE);
		break;
	case GO_FIVE:
		DrawString(10,360,"５マス進みました",WHITE);
		break;
	case GO_SIX:
		DrawString(10,360,"６マス進みました",WHITE);
		break;
	case GO_TEN_OR_RETURN_TEN:
		switch(go_or_return){
		case false:
			DrawString(10,360,"１０マス戻りました",WHITE);
			break;
		case true:
			DrawString(10,360,"１０マス進みました",WHITE);
			break;
		}
		break;
	case PI:
		DrawFormatString(10,360,WHITE,"%dマス進みました",piNum);
		break;
	}

}

void CTxt::CardConfirmDraw(){
	DrawString(10,360,"本当にこのカードを使いますか？",WHITE);
}

void CTxt::Draw( int player , int Case ,int Num , int time ){
	
	DrawBox( 0 , 350 , 640 , 480 , GetColor(0,0,0) , true);
	DrawBox( 0 , 350 , 640 , 480 , GetColor(126 , 126 , 126 ) , false);

	switch(Case){
	case JUDGE_STATUS:
		DrawFormatString( 10 , 360 ,WHITE , "プレイヤー%dのターン" , player );

		break;
	case SELECT_MOVEMENT:
		DrawString(10 , 360 , "十字キーで選んで、Enterキーで決定してください" , WHITE  );
		DrawString(10,380,"または，文字を左クリックしてください",WHITE);
		break;
	case ROLL_DICE:
		break;
	case MOVE:
		if(Num > 0){
			DrawFormatString ( 10 , 360 , WHITE , "あと%dマス" , Num-1 );
		}
		break;
	case DRAW_TEXT:
		break;
	case EFFECT:
		break;
	}

}

void CTxt::EffectDraw( int type){
	if(type== GO_BACK){DrawString(10,360,"３マス戻る",WHITE);}

	if(type==GO_AHEAD){DrawString(10,360,"３マス進む",WHITE);}

	if(type==REST){DrawString(10,360,"一回休み",WHITE);}

	if(type==RETURN_START){DrawString(10,360,"スタートに戻る",WHITE);}

	if(type==STOP){DrawString(10,360,"４か５か６が出るまで進めません",WHITE);}

}