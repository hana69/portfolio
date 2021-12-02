#include"Tutorial.h"
#include<string>
#include"DxLib.h"
#include"mouse.h"
#include"General.h"
#include"ActionField.h"
#include"ScaffoldMaker.h"

int Tutorial::graph[] = {};
Tutorial::Tutorial()
	:state(ExplainState::FIRST),explaining(false),
	field(new CActionField(0,1)),maker(new CScaffoldMaker()),
	scroll(0),drawFlag(false),meMoveFlag(true),scrollFlag(false),
	backGraph(LoadGraph("noseResource/normalBack.png"))
{
	std::string s;
	if (graph[1]==0) {
		for (int i = 1; i <= 22; i++) {
			s = "noseResource/tutorial/tutorial";
			s += std::to_string(i);
			s += ".png";
			graph[i] = LoadGraph(s.c_str());
		}
	}
	Start();
	SetFontSize(15);
}
Tutorial::~Tutorial() {
	delete field;
	delete maker;
}

void Tutorial::Start() {
	scroll = 0;
	state = ExplainState::FIRST;
	drawFlag = false;
	scrollFlag = false;
	meMoveFlag = true;
	for (int i = 0; i < 7;i++) {
		maker->AddCoin();
	}
}
void Tutorial::Update() {
	DrawBack();
	
	StateFunc();
	if (meMoveFlag == true) {
		field->Update(scroll);
	}
	else {
		field->OnlyDraw(scroll);
	}
	if (field->SelectedReturnStart()) {
		maker->Reset();
		Start();
		field->Restart();
	}
	if (field->GameCleared() || field->GameOvered()) {
		drawFlag = false;
	}
	if (drawFlag == true) {
		DrawExtendGraph(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, graph[(unsigned)state], true);
	}
	field->DrawMenu();
	Scroll();
	
}

bool Tutorial::SelectedReturnTitle() {
	return field->SelectedReturnTitle();
}
bool Tutorial::SelectedNextStage() {
	return field->SelectedGoToNextStage();
}

void Tutorial::StateFunc() {
	static CMouse mouse;
	switch (state) {
	case ExplainState::FIRST:
		if (field->MeX()>250) {
			state = ExplainState::ROAD_IS_BROKEN;
			drawFlag = true;
			meMoveFlag = false;
		}
		maker->OnlyDraw();
		break;
	case ExplainState::ROAD_IS_BROKEN:
		if (mouse.LeftReleased()) {
			state = ExplainState::LETS_CLICK;
		}
		maker->OnlyDraw();
		break;
	case ExplainState::LETS_CLICK:
		if(maker->DrawFinished()) {
			field->Make(maker->DrawnSpotX(), maker->DrawnSpotY(), maker->DrawnType(), scroll);
			meMoveFlag = true;
		}
		if (field->MeX() > 700) {
			state = ExplainState::MP_DECREASE;
			meMoveFlag = false;
		}
		maker->Update();
		break;
	case ExplainState::MP_DECREASE:
		if (mouse.LeftReleased()) {
			drawFlag = false;
			meMoveFlag = true;
			scrollFlag = true;
		}
		if (field->MeX() > 750) {
			state = ExplainState::SCROLL;
			meMoveFlag = false;
			drawFlag = true;
		}
		maker->OnlyDraw();
		break;
	case ExplainState::SCROLL:
		if (mouse.LeftReleased()) {
			drawFlag=false;
			meMoveFlag = true;
		}
		if (scroll > 500) {
			state = ExplainState::DISCOVER_COIN;
			drawFlag = true;
			meMoveFlag = false;
			scrollFlag = false;
		}
		else if(field->MeX() > 1250){
			scroll = 500;
			state = ExplainState::DISCOVER_COIN;
			drawFlag = true;
			meMoveFlag = false;
			scrollFlag = false;
		}
		maker->OnlyDraw();
		break;
	case ExplainState::DISCOVER_COIN:
		if (mouse.LeftReleased()) {
			drawFlag = false;
			meMoveFlag = true;
		}
		if (field->MeGotCoin()) {
			maker->AddCoin();
			state = ExplainState::MP_GAIN;
			drawFlag = true;
			meMoveFlag = false;
		}
		maker->OnlyDraw();
		break;
	case ExplainState::MP_GAIN:
		if (field->MeGotCoin()) {
			maker->AddCoin();
		}
		if (mouse.LeftReleased()) {
			drawFlag = false;
			meMoveFlag = true;
			scrollFlag = true;
		}
		if (scroll>=1800) {
			scroll = 1800;
			scrollFlag = false;
			meMoveFlag = false;
			drawFlag = true;
			state = ExplainState::HOLE_AGAIN;
		}
		else if(field->MeX() > 2300) {
			scroll = 1800;
			scrollFlag = false;
			meMoveFlag = false;
			drawFlag = true;
			state = ExplainState::HOLE_AGAIN;
		}
		maker->OnlyDraw();
		break;
	case ExplainState::HOLE_AGAIN:
		if (mouse.LeftReleased()) {
			state = ExplainState::BUT;
		}
		maker->OnlyDraw();
		break;
	case ExplainState::BUT:
		if (mouse.LeftReleased()) {
			drawFlag = false;
			meMoveFlag = true;
		}
		if (field->MeX()>2550) {
			meMoveFlag = false;
			drawFlag = true;
			state = ExplainState::GO_THROUH_SINGLE_HOLE;
		}
		maker->OnlyDraw();
		break;
	case ExplainState::GO_THROUH_SINGLE_HOLE:
		if (mouse.LeftReleased()) {
			drawFlag = false;
			scrollFlag = true;
			meMoveFlag = true;
		}
		if (scroll>3100) {
			scrollFlag = false;
			drawFlag = true;
			meMoveFlag = false;
			state = ExplainState::HAVETO_MAKE;
		}
		else if(field->MeX()>3200){
			scroll = 3100;
			scrollFlag = false;
			drawFlag = true;
			meMoveFlag = false;
			state = ExplainState::HAVETO_MAKE;
		}
		maker->OnlyDraw();
		break;
	case ExplainState::HAVETO_MAKE:
		if (maker->DrawFinished()) {
			meMoveFlag = true;
			field->Make(maker->DrawnSpotX(), maker->DrawnSpotY(), maker->DrawnType(), scroll);
		}
		if (field->MeX() > 3450 ) {
			drawFlag = false;
			scrollFlag = true;
		}

		if (scroll>3600) {
			scrollFlag = false;
			drawFlag = true;
			meMoveFlag = false;
			state = ExplainState::WALL_AND_SINGLE_HOLE;
		}
		else if (field->MeX()>4100) {
			scroll = 3650;
			scrollFlag = false;
			drawFlag = true;
			meMoveFlag = false;
			state = ExplainState::WALL_AND_SINGLE_HOLE;
		}
		
		if (field->MeGotCoin()) {
			maker->AddCoin();
		}
		maker->Update();
		break;
	case ExplainState::WALL_AND_SINGLE_HOLE:
		if (mouse.LeftReleased()) {
			meMoveFlag = true;
		}
		if (field->MeY()>250) {
			state = ExplainState::FALL;
			meMoveFlag = false;
			drawFlag = true;
		}
		if (field->MeGotCoin()) {
			maker->AddCoin();
		}
		maker->OnlyDraw();
		break;
	case ExplainState::FALL:
		if (mouse.LeftReleased()) {
			state = ExplainState::FILL_SINGLE_HOLE;
		}
		maker->OnlyDraw();
		break;
	case ExplainState::FILL_SINGLE_HOLE:
		if (maker->DrawFinished()) {
			meMoveFlag = true;
			field->Make(maker->DrawnSpotX(), maker->DrawnSpotY(), maker->DrawnType(), scroll);
		}
		if (field->MeY()<200) {
			meMoveFlag = true;
			state = ExplainState::STILL_THERE_IS_WALL;
		}
		maker->Update();
		break;
	case ExplainState::STILL_THERE_IS_WALL:
		if (mouse.LeftReleased()) {
			state = ExplainState::HAVETO_ERASE;
		}
		maker->OnlyDraw();
		break;
	case ExplainState::HAVETO_ERASE:
		if (maker->DrawFinished()) {
			meMoveFlag = true;
			drawFlag = false;
			scrollFlag = true;
			field->Make(maker->DrawnSpotX(), maker->DrawnSpotY(), maker->DrawnType(), scroll);
		}
		if (scroll > 4300) {
			scroll = 4350;
			meMoveFlag = false;
			drawFlag = true;
			scrollFlag = false;
			state = ExplainState::FOUND_STEP;
		}
		else if(field->MeX()>4800){
			scroll = 4350;
			meMoveFlag = false;
			drawFlag = true;
			scrollFlag = false;
			state= ExplainState::FOUND_STEP;
		}
		maker->Update();
		break;
	case ExplainState::FOUND_STEP:
		if (mouse.LeftReleased()) {
			state = ExplainState::VARIOUS_SCAFFOLD;
		}
		maker->OnlyDraw();
		break;
	case ExplainState::VARIOUS_SCAFFOLD:
		if (mouse.LeftReleased()) {
			state = ExplainState::CLICK_TO_SELECT;
		}
		maker->OnlyDraw();
		break;
	case ExplainState::CLICK_TO_SELECT:
		if (mouse.LeftReleased()) {
			state = ExplainState::SELECT_JUMP;
		}
		maker->OnlyDraw();
		break;
	case ExplainState::SELECT_JUMP:
		if (mouse.LeftReleased()) {
			state = ExplainState::HAVETO_JUMP;
		}
		maker->Update();
		break;
	case ExplainState::HAVETO_JUMP:
		if (maker->DrawFinished()) {
			field->Make(maker->DrawnSpotX(), maker->DrawnSpotY(), maker->DrawnType(), scroll);
			meMoveFlag = true;
		}
		if (field->MeY()<100) {
			drawFlag = false;
			scrollFlag = true;
		}
		if (scroll>4650) {
			drawFlag = true;
			meMoveFlag = false;
			scrollFlag = false;
			state = ExplainState::GOAL;
		}
		else if (field->MeX()>5300) {
			scroll = 4700;
			drawFlag = true;
			meMoveFlag = false;
			scrollFlag = false;
			state = ExplainState::GOAL;
		}
		maker->Update();
		break;
	case ExplainState::GOAL:
		if (mouse.LeftReleased()) {
			state = ExplainState::MENU;
		}
		maker->OnlyDraw();
		break;
	case ExplainState::MENU:
		if (mouse.LeftReleased()) {
			meMoveFlag = true;
			drawFlag = false;
		}
		maker->OnlyDraw();
		break;
		
	}
}

void Tutorial::Scroll() {
	static CMouse mouse;
	static float a;
	if (scrollFlag==true) {
		if (a > 50) {
			scroll += 50;
			a = 0;
		}
		else if (a < -50) {
			scroll -= 50;
			a = 0;
		}
		a += mouse.Wheel(1) * 50.0;
		//////マウスが画面外左右にいったらスクロール/////////
		if (mouse.X() < 0) {
			a -= 8;
		}
		if (mouse.X() > WINDOW_WIDTH) {
			a += 8;
		}
		/////////////////////////////////////////////////////

		/////////スクロールの左限右限を設定/////////////
		if (scroll < 0) {
			scroll = 0;
		}
		if (scroll > field->RightEdge() * 50 - WINDOW_WIDTH) {
			scroll = field->RightEdge() * 50 - WINDOW_WIDTH;
		}
		////////////////////////////////////////////////
	}
	else {
		a = 0;
	}
}

void Tutorial::DrawBack() {
	DrawGraph(0, 0, backGraph, true);
	///////////ぐりっど////////////////////////
	for (int i = 0; i <= field->RightEdge() * 50; i += 50) {
		DrawLine(i - scroll, 0, i - scroll, WINDOW_HEIGHT, BLUE);
	}
	for (int j = 0; j < WINDOW_HEIGHT; j += 50) {
		DrawLine(0, j, WINDOW_WIDTH, j, BLUE);
	}
	//////////////////////////////////////////
}