#include"Stage.h"
#include"General.h"
#include"ActionField.h"
#include"ScaffoldMaker.h"

Stage::Stage(int _stageNum,int _finalStageNum)
	:scroll(0),
	field(new CActionField(_stageNum,_finalStageNum)),maker(new CScaffoldMaker()),
	backGraph(_stageNum>=15 ? LoadGraph("noseResource/seaBack.png"): LoadGraph("noseResource/normalBack.png"))
{
	SetFontSize(15);
}

Stage::~Stage() {
	delete field;
	delete maker;
}

void Stage::Update() {
	DrawBack(field->RightEdge());

	field->Update(scroll);
	if (field->MeGotCoin()) {
		maker->AddCoin();
	}
	if (!field->MenuOpening()) {
		Scroll();
		if (maker->DrawFinished()) {
			field->Make(maker->DrawnSpotX(), maker->DrawnSpotY(), maker->DrawnType(), scroll);
		}
	}
	if (field->MenuOpening() || field->GameCleared() || field->GameOvered()) {
		maker->OnlyDraw();
	}
	else {
		maker->Update();
	}
	
	if (field->SelectedReturnStart()) {
		scroll = 0;
		field->Restart();
		maker->Reset();
	}
}

bool Stage::SelectedReturnTitle() {
	return field->SelectedReturnTitle();
}
bool Stage::SelectedGoToNextStage() {
	return field->SelectedGoToNextStage();
}

///////////////private関数////////////////////////
void Stage::Scroll() {
	static CMouse mouse;
	static float a;
	a += mouse.Wheel(1) * 50.0;
	if (a>50) {
		scroll += 50;
		a = 0;
	}
	else if (a<-50) {
		scroll -= 50;
		a = 0;
	}
	//////マウスが画面外左右にいったらスクロール/////////
	if (mouse.X()<0) {
		a -= 8;
	}
	if (mouse.X()>WINDOW_WIDTH) {
		a += 8;
	}
	/////////////////////////////////////////////////////

	/////////スクロールの左限右限を設定/////////////
	if (scroll<0) {
		scroll = 0;
	}
	if (scroll>field->RightEdge()*50-WINDOW_WIDTH) {
		scroll = field->RightEdge()*50- WINDOW_WIDTH;
	}
	////////////////////////////////////////////////
}

void Stage::DrawBack(int rightEdge) {
	DrawGraph(0, 0, backGraph, true);
	///////////ぐりっど////////////////////////
	for (int i = 0; i <= rightEdge * 50; i += 50) {
		DrawLine(i - scroll, 0, i - scroll, WINDOW_HEIGHT, BLUE);
	}
	for (int j = 0; j < WINDOW_HEIGHT; j += 50) {
		DrawLine(0, j, WINDOW_WIDTH, j, BLUE);
	}
	//////////////////////////////////////////
}