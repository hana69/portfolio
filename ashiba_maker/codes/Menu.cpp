#include"Menu.h"
#include"ClickObj.h"
#include"General.h"

Menu::Menu(int _x,int _y, int _backGraph)
	:x(_x),y(_y),backGraph(_backGraph)
{}

void Menu::Update() {
	Draw();
//DrawBox(x, y, x + 200, y + 150, BLACK, true);
//	DrawBox(x, y, x + 200, y + 150, YELLOW, false);
	for (auto i:texts) {
		i->Update();
	}
}
void Menu::Draw() {
	DrawGraph(x,y,backGraph,true);
}
Menu::~Menu() {
	for (auto i : texts) {
		delete i;
	}
}

Pause::Pause()
	:Menu(WINDOW_WIDTH / 2 - 100, WINDOW_HEIGHT / 2 - 75,LoadGraph("noseResource/PauseBack.png")),
	selectedText(Texts::RESUME)
{
	int graph[(unsigned)Texts::MAX][4] = {};
	int w = 173;
	LoadDivGraph("noseResource/ReturnToStart_4in1.png", (unsigned)Texts::MAX, 1, (unsigned)Texts::MAX, w, 20, graph[(unsigned)Texts::RETURN_TO_START]);
	LoadDivGraph("noseResource/ReturnToTitle_4in1.png", (unsigned)Texts::MAX, 1, (unsigned)Texts::MAX, w, 20, graph[(unsigned)Texts::RETURN_TO_TITLE]);
	LoadDivGraph("noseResource/CloseMenu_4in1.png", (unsigned)Texts::MAX, 1, (unsigned)Texts::MAX, w, 20, graph[(unsigned)Texts::RESUME] );
	int c = WINDOW_WIDTH / 2;
	for (int i = 0; i < (int)Texts::MAX; i++) {
		if (graph[i][0]!=0) {
			texts.push_back(new ClickObj(c - w / 2, y + 50 + i * 30, c + w / 2, y + 50 + i * 30 + 20, graph[i]));
		}
	}
}

bool Pause::Selected() {
	for (int i = 0; i < /*(int)Texts::MAX*/texts.size();i++ ) {
		if (texts[i]->Clicked()) {
			selectedText = (Texts)i;
			return true;
		}
	}
	return false;
}

GameOverMenu::GameOverMenu()
:Menu(WINDOW_WIDTH / 2 - 200, WINDOW_HEIGHT / 2 - 75, LoadGraph("noseResource/GameOverBack.png")),
selectedText(Texts::RETURN_TO_START)
{
	int graph[(unsigned)Texts::MAX][4] = {};
	const int w = 173;
	LoadDivGraph("noseResource/ReturnToStart_4in1.png", 4, 1, 4, w, 20, graph[(unsigned)Texts::RETURN_TO_START]);
	LoadDivGraph("noseResource/ReturnToTitle_4in1.png", 4, 1, 4, w, 20, graph[(unsigned)Texts::RETURN_TO_TITLE]);
	//const int c = WINDOW_WIDTH / 2;
	texts.push_back(new ClickObj(x + 10, y + 120, x + 10 + w, y + 120 + 20, graph[(unsigned)Texts::RETURN_TO_START]));
	texts.push_back(new ClickObj(x + 210, y + 120, x + 210 + w, y + 120 + 20, graph[(unsigned)Texts::RETURN_TO_TITLE]));
}
bool GameOverMenu::Selected() {
	for (int i = 0; i < /*(int)Texts::MAX*/texts.size(); i++) {
		if (texts[i]->Clicked()) {
			selectedText = (Texts)i;
			return true;
		}
	}
	return false;
}

GameClearMenu::GameClearMenu(int _stageNum)
	:Menu(WINDOW_WIDTH / 2 - 200, WINDOW_HEIGHT / 2 - 75, LoadGraph("noseResource/GameClearBack.png")),
	selectedText(Texts::RETURN_TO_TITLE),
	stageNum(_stageNum)
{
	int graph[(unsigned)Texts::MAX][4] = {};
	LoadDivGraph("noseResource/ReturnToTitle_4in1.png", 4, 1, 4, 173, 20, graph[(unsigned)Texts::RETURN_TO_TITLE]);
	LoadDivGraph("noseResource/NextStage_4in1.png", 4, 1, 4, 150, 20, graph[(unsigned)Texts::GO_TO_NEXT_STAGE]);
	texts.push_back(new ClickObj(x + 25, y + 120, x + 25 + 173, y + 120 + 20, graph[(unsigned)Texts::RETURN_TO_TITLE]));
	texts.push_back(new ClickObj(x + 225, y + 120, x + 225 + 150, y + 120 + 20, graph[(unsigned)Texts::GO_TO_NEXT_STAGE]));
}
bool GameClearMenu::Selected() {
	for (int i = 0; i < /*(int)Texts::MAX*/texts.size(); i++) {
		if (texts[i]->Clicked()) {
			selectedText = (Texts)i;
			return true;
		}
	}
	return false;
}

void GameClearMenu::Update(int _finalStageNum) {
	Menu::Draw();
	for (int i = 0; i < (int)Texts::MAX;i++) {
		if (stageNum!=_finalStageNum || (Texts)i != Texts::GO_TO_NEXT_STAGE) {
			texts[i]->Update();
		}
	}
}
//CMenu::CMenu() 
//	:selectingState(RESUME),
//	x(WINDOW_WIDTH / 2 - 100),y(WINDOW_HEIGHT / 2 - 75)
//{
//	mouse[RESUME].SetRange(x+48,y+56,x+157,y+69);
//	mouse[RETURN_TO_START_MENU].SetRange(x+12,y+87,x+190,y+98);
//	mouse[RETURN_TO_TITLE_MENU].SetRange(x+45,y+118,x+155,y+130);
//
//	if (graph[NO_ACTION_MENU] == 0) {
//		graph[NO_ACTION_MENU] = LoadGraph("noseResource/Menu.png");
//	}
//	if (graph[RESUME]==0) {
//		graph[RESUME] = LoadGraph("noseResource/Menu_Resume.png");
//	}
//	if (graph[RETURN_TO_TITLE_MENU] == 0) {
//		graph[RETURN_TO_TITLE_MENU] = LoadGraph("noseResource/Menu_ReturnTitle.png");
//	}
//	if (graph[RETURN_TO_START_MENU] == 0) {
//		graph[RETURN_TO_START_MENU] = LoadGraph("noseResource/Menu_ReturnStart.png");
//	}
//}
//
//MENU_RETURN CMenu::Update() {
//	selectingState = NO_ACTION_MENU;
//
//	for (int i = 1; i < MENU_STATE_NUM;i++ ) {
//		if (mouse[i].Insided()) {
//			selectingState = (MENU_RETURN)i;
//		}
//	}
//	DrawGraph(x, y, graph[selectingState], true);
//	if (mouse[selectingState].LeftPushed()) {
//		return selectingState;
//	}
//
//	return NO_ACTION_MENU;
//	
//}