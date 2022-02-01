#include"mouse.h"

void CMouse::Awake(int X1,int Y1,int X2,int Y2){
	rangeX1 = X1;
	rangeX2 = X2;
	rangeY1 = Y1;
	rangeY2 = Y2;

	flag = false;
	rightFlag = false;

	x=y=0;
	tempX=tempY=0;
}

void CMouse::SetFlag(){
	flag = true;
}

bool CMouse::GetFlag(){
	return flag;
}

bool CMouse::Pushed(){
	GetMousePoint(&x,&y);

	if( rangeX1 < x && x < rangeX2 && rangeY1 < y &&  y < rangeY2 && !flag && GetMouseInput()&MOUSE_INPUT_LEFT != 0 ){
		return true;
	}
	return false;
}
bool CMouse::RightPushed(){

	if( rightFlag==false && GetMouseInput()&MOUSE_INPUT_RIGHT != 0){
		rightFlag = true;
	}
	if( rightFlag == true && !(GetMouseInput()&MOUSE_INPUT_RIGHT != 0)  ){
		rightFlag = false;
		return true;
	}

	return false;
}

bool CMouse::Released(){

	if(flag==true && !(GetMouseInput()&MOUSE_INPUT_LEFT != 0)){
		flag = false;
		if(rangeX1 < x && x < rangeX2 && rangeY1 < y &&  y < rangeY2){
			return true;
		}
	}

	return false;

}

bool CMouse::Insided(){
	if(rangeX1 < x && x < rangeX2 && rangeY1 < y &&  y < rangeY2){
		return true;
	}
	return false;
}

void CMouse::SetTemp(){
	GetMousePoint(&x,&y);

	if( rangeX1 < x && x < rangeX2 && rangeY1 < y &&  y < rangeY2 &&  GetMouseInput()&MOUSE_INPUT_LEFT != 0 && !flag ){
		flag=true;
		tempX=x;
		tempY=y;
	}

	if( !(GetMouseInput()&MOUSE_INPUT_LEFT!=0) && flag == true  ){
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