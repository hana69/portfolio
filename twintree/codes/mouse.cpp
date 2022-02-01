#include"mouse.h"

CMouse::CMouse(int X1,int Y1,int X2,int Y2){
	rangeX1 = X1;
	rangeX2 = X2;
	rangeY1 = Y1;
	rangeY2 = Y2;

	flag = false;
	rightFlag = false;

	x=y=0;
	tempX=tempY=0;
}

bool CMouse::RightReleased(){

	if( rightFlag==false && GetMouseInput() &(MOUSE_INPUT_RIGHT != 0) ){
		rightFlag = true;
	}
	if( rightFlag == true && !(GetMouseInput() &(MOUSE_INPUT_RIGHT != 0) ) ){
		rightFlag = false;
		return true;
	}

	return false;
}
bool CMouse::LeftReleased(){

	if(rightFlag==false && GetMouseInput()&(MOUSE_INPUT_LEFT != 0) ){
		flag=true;
	}
	if(flag==true && !(GetMouseInput()&(MOUSE_INPUT_LEFT != 0) ) ){
		flag = false;
		if(rangeX1 < x && x < rangeX2 && rangeY1 < y &&  y < rangeY2){
			return true;
		}
	}

	return false;
}

void CMouse::SetTemp(){
	GetMousePoint(&x,&y);

	if( Insided() &&  GetMouseInput()&(MOUSE_INPUT_LEFT != 0) && flag==false ){
		flag=true;
		tempX=x;
		tempY=y;
	}

	if( !(GetMouseInput() &(MOUSE_INPUT_LEFT!=0) ) && flag == true  ){
		flag=false;
	}

		tempX=x;
		tempY=y;

}

int CMouse::GetChangeX(){
	GetMousePoint(&x,&y);
	return tempX-x;
}
int CMouse::GetChangeY(){
	GetMousePoint(&x,&y);
	return tempY-y;
}
bool CMouse::GetFlag(){
	return flag;
}
///////////////////////プライベート関数///////////////////////////////////
bool CMouse::Insided(){
	if(rangeX1 < x && x < rangeX2 && rangeY1 < y &&  y < rangeY2){
		return true;
	}
	return false;
}