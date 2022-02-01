#include "DxLib.h"
#include "Suken.h"
#include "dice.h"

void CDice::Awake(){
	for(int i=0;i<10;i++){
		dicePic[i]=0;
	}

	dicePic[1] = LoadGraph("sugoroku_Resource/dice1.png"); 
	dicePic[2] = LoadGraph("sugoroku_Resource/dice2.png");
	dicePic[3] = LoadGraph("sugoroku_Resource/dice3.png");
	dicePic[4] = LoadGraph("sugoroku_Resource/dice4.png");
	dicePic[5] = LoadGraph("sugoroku_Resource/dice5.png");
	dicePic[6] = LoadGraph("sugoroku_Resource/dice6.png");

	Random=1;
	Num=0;
	debugmode=0;
}

void CDice::DiceDraw( int Case , int frame){

	DrawBox( DICE_X , DICE_Y , DICE_X+60 , DICE_Y+60 , BLUE , false);

	switch(Case){
	case JUDGE_STATUS:
		DrawGraph( DICE_X , DICE_Y , dicePic[1] , true);
		break;
	case SELECT_MOVEMENT:
		DrawGraph( DICE_X , DICE_Y , dicePic[1] , true);
		break;
	case USE_CARD:
		DrawGraph( DICE_X , DICE_Y , dicePic[1] , true);
		break;
	case ROLL_DICE:
		DrawGraph( DICE_X , DICE_Y , dicePic[Random] , true);
		break;
	case MOVE:
		DrawGraph( DICE_X , DICE_Y , dicePic[Num] , true);
		break;
	case DRAW_TEXT:
		DrawGraph( DICE_X , DICE_Y , dicePic[Num] , true);
		break;
	case EFFECT:
		DrawGraph( DICE_X , DICE_Y , dicePic[1] , true);
		break;
	case JUDGE_GOAL:
		DrawGraph( DICE_X , DICE_Y , dicePic[1] , true);
		break;
	default:break;
	}

	if(debugmode==1){
		if(frame%30==0){
			Random++;
			if(Random>6){
				Random = 1;
			}
		}
	}

	else{
		if(frame%5==0){
			Random++;
		}
		if(Random > 6){
			Random = 1;
		}
	}

}

void CDice::ModeSelect(){

	if(CheckHitKey(KEY_INPUT_0)){
		debugmode = 0;
	}	
	if(CheckHitKey(KEY_INPUT_1)){
		debugmode = 1;
	}
	if(CheckHitKey(KEY_INPUT_2)){
		debugmode = 2;
	}

	switch(debugmode){
	case 0:DrawString(0,120,"ïÅí ",RED);break;
	case 1:DrawString(0,120,"ñ⁄âüÇµâ¬î\",RED);break;
	case 2:DrawString(0,120,"çÇë¨",RED);break;
	}

}

void CDice::SetNum(){

	if(debugmode==1){
		Num = Random;
	}
	else{
		Num = GetRand(5)+1;
	}

	if(CheckHitKey(KEY_INPUT_F1)){
		Num = 1;
	}
	if(CheckHitKey(KEY_INPUT_F2)) Num=2;
	if(CheckHitKey(KEY_INPUT_F3)) Num=3;
	if(CheckHitKey(KEY_INPUT_F4)) Num=4;
	if(CheckHitKey(KEY_INPUT_F5)) Num=5;
	if(CheckHitKey(KEY_INPUT_F6)) Num=6;

}

int CDice::GetNum(){
	return Num;
}

int CDice::GetRandom(){
	return Random;
}

int CDice::GetDebugMode(){
	return debugmode;
}

void CDice::SetDebugMode(int num){
	debugmode=num;
}