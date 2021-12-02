#include"ScaffoldMaker.h"
#include<math.h>
#include"MPGage.h"

CScaffoldMaker::CScaffoldMaker()
	:selector(WINDOW_WIDTH - (60+50), WINDOW_HEIGHT - (50 * 4 + 20 * 5), WINDOW_WIDTH, WINDOW_HEIGHT),
	mpGage(new MPGage(WINDOW_WIDTH - 35, WINDOW_HEIGHT - 20) ),
	x1(DRAW_AREA_LEFT), y1(DRAW_AREA_TOP), x2(DRAW_AREA_RIGHT), y2(DRAW_AREA_TOP + 50 * 3 + 1),
	drawAreaGraph(LoadGraph("noseResource/drawArea.png")),
	drawFinished(false),
	writingWidth(0),writed(false),
	point(0),needPoint(0),
	Mouse(x1, y1, x2, y2)
{}
/////////////publicä÷êî//////////////////////

CScaffoldMaker::~CScaffoldMaker() {
	delete mpGage;
}

void CScaffoldMaker::Update() {
	Draw();
	OnlyDraw();
	selector.Update(point,needPoint);
}

void CScaffoldMaker::OnlyDraw() {
	DrawGraph( x1 ,  y1 , drawAreaGraph , true);
	if (Mouse.Insided()) {
		if (Mouse.LeftPushing() && scaffoldCost[(unsigned)selector.SelectingType()] <= point) {
			mpGage->Update(point, true, selector.SelectingType());
			DrawGraph(Mouse.X() / 50 * 50, Mouse.Y() / 50 * 50, scaffoldGraph(selector.SelectingType()), true);
		}
		else if (Mouse.RightPushing() && scaffoldCost[(unsigned)ScaffoldType::ERASER] <= point) {
			mpGage->Update(point, true, ScaffoldType::ERASER);
			DrawGraph(Mouse.X() / 50 * 50, Mouse.Y() / 50 * 50, scaffoldGraph(ScaffoldType::ERASER), true);
		}
		else {
			mpGage->Update(point, false, selector.SelectingType());
		}
	}
	else {
		mpGage->Update(point, false, selector.SelectingType());
	}
	selector.Update(point, needPoint);
}

void CScaffoldMaker::AddCoin() {
	point+=5;
	if (point>50) {
		point = 50;
	}
}

void CScaffoldMaker::Reset() {
	point = 0;
}

bool CScaffoldMaker::DrawFinished() {
	if (drawFinished) {
		drawFinished = false;
		writed = false;
		return true;
	}
	needPoint = 0;
	writed = false;
	return false;
}

////////////privateä÷êî//////////////////////

void CScaffoldMaker::Draw() {
	/*const int tX = Mouse.TempX(), X = Mouse.X(), cX = Mouse.ChangeX(),
				  tY = Mouse.TempY(), Y = Mouse.Y(), cY = Mouse.ChangeY();*/
	/*if (cX > 0 && cY > 0) {
			for (int i = tX / 50 + tX % 50 / 25; i <= X / 50 + X % 50 / 25 - 1 && point >= needPoint+ scaffoldCost[(unsigned)selector.SelectingType()] && x1 < i * 50 && i * 50 < x2;i++) {
				needPoint += scaffoldCost[(unsigned)selector.SelectingType()];
				writingWidth++;
				for (int j = tY / 50 + tY % 50 / 25; j <= Y / 50 + Y % 50 / 25 - 1 && y1 < j * 50 && j * 50 <y2; j++) {
					DrawGraph(i * 50, j * 50, scaffoldGraph(selector.SelectingType()), true);				
					writed = true;
				}
			}
		}
		else if (cX > 0 && cY < 0) {
			for (int i = tX / 50 + tX % 50 / 25; i <= X / 50 + X % 50 / 25 - 1 && point >= needPoint+ scaffoldCost[(unsigned)selector.SelectingType()] && x1 < i * 50 && i * 50 < x2 ; i++) {
				needPoint += scaffoldCost[(unsigned)selector.SelectingType()];
				writingWidth++;
				for (int j = tY / 50 + tY % 50 / 25 - 1; j >= Y / 50 + Y % 50 / 25 && y1 < j * 50 && j * 50 <y2;j--) {
					DrawGraph(i * 50, j * 50, scaffoldGraph(selector.SelectingType()), true);
					writed = true;
				}
			}
		}
		else if (cX < 0 && cY > 0) {
			for (int i = tX / 50 + tX % 50 / 25 - 1; i >= X / 50 + X % 50 / 25 && point >= needPoint+ scaffoldCost[(unsigned)selector.SelectingType()] && x1 < i * 50 && i * 50 < x2; i--) {
				needPoint += scaffoldCost[(unsigned)selector.SelectingType()];
				writingWidth++;
				for (int j = tY / 50 + tY % 50 / 25; j <= Y / 50 + Y % 50 / 25 - 1 && y1 < j * 50 && j * 50 < y2; j++) {
					DrawGraph(i * 50, j * 50, scaffoldGraph(selector.SelectingType()), true);
					writed = true;
				}
			}
		}
		else {
			for (int i = tX / 50 + tX % 50 / 25 - 1; i >= X / 50 + X % 50 / 25 && point >= needPoint+ scaffoldCost[(unsigned)selector.SelectingType()] && x1 < i * 50 && i * 50 < x2; i--) {
				needPoint += scaffoldCost[(unsigned)selector.SelectingType()];
				writingWidth++;
				for (int j = tY / 50 + tY % 50 / 25 - 1; j >= Y / 50 + Y % 50 / 25 && y1 < j * 50 && j * 50 < y2; j--) {
					DrawGraph(i * 50, j * 50, scaffoldGraph(selector.SelectingType()), true);
					writed = true;
				}
			}
		}*/
		
	if (Mouse.Insided()) {
		if (Mouse.LeftReleased() && scaffoldCost[(unsigned)selector.SelectingType()] <= point) {
			drawFinished = true;
			point -= scaffoldCost[(unsigned)selector.SelectingType()];
			drawnType = selector.SelectingType();
			drawnSpotX = Mouse.X();
			drawnSpotY = Mouse.Y();
		}
		else if(Mouse.RightReleased() && scaffoldCost[(unsigned)ScaffoldType::ERASER]<=point){
			drawFinished = true;
			point -= scaffoldCost[(unsigned)ScaffoldType::ERASER];
			drawnType = ScaffoldType::ERASER;
			drawnSpotX = Mouse.X();
			drawnSpotY = Mouse.Y();
		}
	}
}
///////////////////////////Selector////////////////////////////////////

int	CSelectableObj::selecting = 0;
int	CSelectableObj::pointing = 0;
CScaffoldSelector::CScaffoldSelector(int _x1, int _y1, int _x2, int _y2)
	:x1(_x1), x2(_x2), y1(_y1), y2(_y2),
	init(false),selectingType(ScaffoldType::NORMAL)
{
	for (int i = 0; i <= (unsigned)ScaffoldType::NORMAL;i++) {
		selectableObj[i].SetPosition(x1+20, y1+20+i*70);
		selectableObj[i].SetType((ScaffoldType)i);
	}
	selectingType = ScaffoldType::NORMAL;
	
}

void CScaffoldSelector::Update(int _point,int _needPoint) {
	Draw(_point,_needPoint);
	for (auto i :selectableObj) {
		i.Select(&selectingType,_point);
	}
}

void CScaffoldSelector::Draw(int _point, int _needPoint) {
	/*DrawBox(x1 -77, y1 - 21, x1 + 58, y1 + 15 , GRAY, true);
	DrawBox(x1 -77, y1 - 21, x1 + 58, y1 + 15 , WHITE, false);
	DrawFormatString(x1 + 15, y1 - 20, YELLOW, "MP:%d", _point);
	DrawFormatString(x1 - 75, y1 - 3, RED, "Ç¬Ç≠Ç¡ÇΩå„ÇÃMP:%d", _point - _needPoint);*/
	
	for (int i = 0; i <= (unsigned)ScaffoldType::NORMAL; i++) {
		selectableObj[i].Draw(_point);
		if ( selectingType == (ScaffoldType)i ) {
			selectableObj[i].DrawSelecting();
		}
	}
}

CSelectableObj::CSelectableObj()
	:x(0), y(0), type(ScaffoldType::NORMAL)
{
	if (selecting == 0) {
		selecting = LoadGraph("noseResource/selecting.png");
	}
	if (pointing == 0) {
		pointing = LoadGraph("noseResource/pointing.png");
	}
}

void CSelectableObj::Draw(int _point) {
	static int unselectableGraph=LoadGraph("noseResource/unselectable.png");
	
	DrawGraph(x, y, scaffoldGraph(type), true);
	if (_point < scaffoldCost[(unsigned)type]) {
		DrawExtendGraph(x, y,x+50,y+50, unselectableGraph, true);
	}
	if (Mouse.Insided()) {
		DrawGraph(x - 1, y - 1, pointing, true);
	}
}

void CSelectableObj::DrawSelecting() {
	DrawGraph(x - 1, y - 1, selecting, true);
}

void CSelectableObj::SetPosition(int _x,int _y) {
	x = _x;
	y = _y;
	Mouse.SetRange(_x, _y, _x + 50, _y + 50);
}

void CSelectableObj::Select(ScaffoldType* _selectingType,int _point ) {
	if (Mouse.Insided()) {
		if (Mouse.LeftPushed()) {
			*_selectingType = type;
		}
	}
}
