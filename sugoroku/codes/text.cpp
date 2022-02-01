#include "text.h"

void CTxt::CardEffectDraw(CardType CardType,int piNum , bool go_or_return){
	
	switch(CardType){
	case GO_ONE:
		DrawString(10,360,"�P�}�X�i�݂܂���",WHITE);
		break;
	case GO_TWO:
		DrawString(10,360,"�Q�}�X�i�݂܂���",WHITE);
		break;
	case GO_THREE:
		DrawString(10,360,"�R�}�X�i�݂܂���",WHITE);
		break;
	case GO_FOUR:
		DrawString(10,360,"�S�}�X�i�݂܂���",WHITE);
		break;
	case GO_FIVE:
		DrawString(10,360,"�T�}�X�i�݂܂���",WHITE);
		break;
	case GO_SIX:
		DrawString(10,360,"�U�}�X�i�݂܂���",WHITE);
		break;
	case GO_TEN_OR_RETURN_TEN:
		switch(go_or_return){
		case false:
			DrawString(10,360,"�P�O�}�X�߂�܂���",WHITE);
			break;
		case true:
			DrawString(10,360,"�P�O�}�X�i�݂܂���",WHITE);
			break;
		}
		break;
	case PI:
		DrawFormatString(10,360,WHITE,"%d�}�X�i�݂܂���",piNum);
		break;
	}

}

void CTxt::CardConfirmDraw(){
	DrawString(10,360,"�{���ɂ��̃J�[�h���g���܂����H",WHITE);
}

void CTxt::Draw( int player , int Case ,int Num , int time ){
	
	DrawBox( 0 , 350 , 640 , 480 , GetColor(0,0,0) , true);
	DrawBox( 0 , 350 , 640 , 480 , GetColor(126 , 126 , 126 ) , false);

	switch(Case){
	case JUDGE_STATUS:
		DrawFormatString( 10 , 360 ,WHITE , "�v���C���[%d�̃^�[��" , player );

		break;
	case SELECT_MOVEMENT:
		DrawString(10 , 360 , "�\���L�[�őI��ŁAEnter�L�[�Ō��肵�Ă�������" , WHITE  );
		DrawString(10,380,"�܂��́C���������N���b�N���Ă�������",WHITE);
		break;
	case ROLL_DICE:
		break;
	case MOVE:
		if(Num > 0){
			DrawFormatString ( 10 , 360 , WHITE , "����%d�}�X" , Num-1 );
		}
		break;
	case DRAW_TEXT:
		break;
	case EFFECT:
		break;
	}

}

void CTxt::EffectDraw( int type){
	if(type== GO_BACK){DrawString(10,360,"�R�}�X�߂�",WHITE);}

	if(type==GO_AHEAD){DrawString(10,360,"�R�}�X�i��",WHITE);}

	if(type==REST){DrawString(10,360,"���x��",WHITE);}

	if(type==RETURN_START){DrawString(10,360,"�X�^�[�g�ɖ߂�",WHITE);}

	if(type==STOP){DrawString(10,360,"�S���T���U���o��܂Ői�߂܂���",WHITE);}

}