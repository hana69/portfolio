#include "Me.h"
#include"key.h"
//#include"SaveData.h"

CMe::CMe(int _stageNum) 
	:x(0),y(0),
	vx(0),vy(0),
	gameOver(false),gameClear(false),
	hitUnderSide(false),
	pressedDie(false),
	stageNum(_stageNum),
//	startTime(GetNowCount()),
//	duration(10000),
	//sd(new SaveData("noseResource/saveData.txt") ),
	graph(LoadGraph("noseResource/trokko_Draw_5.png"))
{}

CMe::~CMe(){
//	delete sd;
}

void CMe::SetV(bool underSea) {
	if (underSea) {
		vx = 0.8f;
		vy += 0.1f;
	}
	else {
		vx = 1.0f;
		vy += 0.2f;
	}
}

void CMe::Move(){

	if (gameOver) {
		if (550 <= y && y <= WINDOW_HEIGHT) {
			x += vx;
			y += vy;
		}
		
	}
	else{
		if (550 < y) {
			gameOver = true;
		}
		x += vx;
		y += vy;
	}
}

void CMe::ResetV() {
	vx = 0;
	//vy = 0;
}
void CMe::ResetHit() {
	hitUnderSide = false;
	hitOverSide = false;
}

void CMe::Restart() {
	gameOver = false;
	gameClear = false;
	x = 0;
	y = 0;
	vx = 0;
	vy = 0;
	hitUnderSide = false;
	pressedDie = false;
	//startTime = GetNowCount();
}

void CMe::Draw(int _scroll){
	if(pressedDie){
		DrawExtendGraph(x - _scroll - 4, diedScUpY-4, x - _scroll - 4 + 58,diedScDownY-8, graph, true);
	}
	else {
		DrawGraph( x - _scroll - 4 , y - 4 , graph , true );
	}
}

void CMe::CollideWith(CScaffold* _sc) {
	if (_sc->Type() != ScaffoldType::ERASER) {
		if (_sc->Y() * 50 < y + 50 && _sc->Y() * 50 + 50 > y) {
			if (x + 50 <= _sc->X() * 50 && x + vx + 50 >= _sc->X() * 50) {
				vx = 0;
				x = _sc->X() * 50 - 50;
			}
		}
		if (_sc->X() * 50 < x + 50 && _sc->X() * 50 + 50 > x) {
			if (_sc->Y() * 50 < y + 50 + vy && _sc->Y() * 50 + 50 > y + vy) {
				vy = 0;
				if (y > _sc->Y() * 50) {//足場の下側（自機の上側）に当たった
					hitUnderSide = true;
					diedScUpY = _sc->Y() * 50 + 50;
					y = _sc->Y() * 50 + 50;
				}
				else {//足場の上側（自機の下側）に当たった
					hitOverSide = true;
					diedScDownY = _sc->Y() * 50;
					y = _sc->Y() * 50 - 50;
				}
				if (hitUnderSide && hitOverSide && diedScDownY - diedScUpY < 50) {
					if (!gameOver) {
						pressedDie = true;
						gameOver = true;
						vy = 0;
					}
				}
			}
			if (_sc->Y() * 50 <= y + 50 && _sc->Y() * 50 + 50 >= y) {
				if (y < _sc->Y() * 50) {
					HitEffect(_sc->Type(), _sc->X(), _sc->Y());
				}
			}
		}
	}
}

void CMe::HitEffect(ScaffoldType _type,int _x,int _y) {
	switch (_type) {
	case ScaffoldType::JUMP:
		vy = -7;
		break;
	case ScaffoldType::SPEED_UP:
		vx = 3;
		break;
	case ScaffoldType::SPEED_DOWN:
		vx = 0.35;
		break;
	case ScaffoldType::GOAL:
		if (x+vx >= _x*50) {
			x = _x*50;
			gameClear = true;
			vx = 0;
		//	duration = GetNowCount() - startTime;
		//	if (sd->Data(stageNum) > duration) {
		//		sd->SetData(stageNum,duration);
			//}
		}
		break;
	}
}