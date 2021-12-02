#include"ClickObj.h"
#include<stdlib.h>
#include"DxLib.h"
#include"mouse.h"
ClickObj::ClickObj(int _x1,int _y1,int _x2 , int _y2 ,int _graph[]) 
	:x1(_x1),y1(_y1),x2(_x2),y2(_y2),
	nowState(MOUSE_STATE::NOT_SELECTING),
	clickedFlag(false)
{
	for (int i = 0; i < 4;i++) {
		graph[i] = *(_graph + i);
	}
	//LoadDivGraph("ReturnToTitle_4in1.png", 4, 1, 4, 173, 20, graph);
}

void ClickObj::Update() {
	SetNowState();
	
	DrawGraph(x1, y1, graph[(int)nowState], true);
}

bool ClickObj::Clicked() {
	return clickedFlag;
}

void ClickObj::SetNowState() {
	CMouse mouse(x1, y1, x2, y2);
	/*switch (nowState) {
	case MOUSE_STATE::NOT_SELECTING:
		if (mouse.Insided()) {
			nowState = MOUSE_STATE::SELECTING;
		}
		clickedFlag = false;
		break;
	case MOUSE_STATE::SELECTING:
		if (mouse.Insided()) {
			if (mouse.LeftPushing()) {
				nowState = MOUSE_STATE::PUSHING;
			}
		}
		else {
			nowState = MOUSE_STATE::NOT_SELECTING;
		}
		break;
	case MOUSE_STATE::PUSHING:
		if (mouse.Insided()) {
			if (mouse.LeftReleased()) {
				nowState = MOUSE_STATE::RELEASED;
			}
		}
		else {
			nowState = MOUSE_STATE::NOT_SELECTING;
		}
		break;
	case MOUSE_STATE::RELEASED:
		clickedFlag = true;
		nowState = MOUSE_STATE::NOT_SELECTING;
		break;
	}*/
	if (nowState==MOUSE_STATE::NOT_SELECTING) {
		clickedFlag = false;
		if (mouse.Insided()) {
			nowState = MOUSE_STATE::SELECTING;
		}
	}
	if (nowState == MOUSE_STATE::SELECTING) {
		if (mouse.Insided()) {
			if (mouse.LeftPushing()) {
				nowState = MOUSE_STATE::PUSHING;
			}
		}
		else {
			nowState = MOUSE_STATE::NOT_SELECTING;
		}
	}
	if (nowState == MOUSE_STATE::PUSHING) {
		if (mouse.Insided()) {
			if (mouse.LeftReleased()) {
				nowState = MOUSE_STATE::RELEASED;
			}
		}
		else {
			nowState = MOUSE_STATE::NOT_SELECTING;
		}
	}
	if (nowState == MOUSE_STATE::RELEASED) {
		clickedFlag = true;
		nowState = MOUSE_STATE::NOT_SELECTING;
	}
	
}

