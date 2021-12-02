#include"ActionField.h"
#include<algorithm>
#include"mouse.h"
#include"coin.h"
#include"Me.h"
#include"Menu.h"
#include"SaveData.h"

int CActionField::limitdata[100] = {};
int CActionField::mapdata[100] = {};
CActionField::CActionField(int _stageNum,int _finalStageNum) 
	:width(200),height( 11 ),
	isTutorial(_stageNum==0),underSea(_stageNum>=15),
	returnStartFlag(false),returnTitleFlag(false),menuOpening(false),
	coinGotFlag(false),goToNextStageFlag(false),
	coin(new CCoin(width)),me(new CMe(_stageNum)),
	pauseMenu(new Pause()),gameOverMenu(new GameOverMenu()),gameClearMenu(new GameClearMenu(_stageNum)),
	finalStageNum(_finalStageNum)
{
	//配列の初期化
	for (int i = 0; i < 500; i++) {
		limit[i] = 0;
		for (int j = 0; j < 15; j++) {
			firstPut[i][j] = false;
		}
	}
	//
	pauseFuncs[(unsigned)Pause::Texts::RETURN_TO_START] = &CActionField::ReturnToStart;
	pauseFuncs[(unsigned)Pause::Texts::RETURN_TO_TITLE] = &CActionField::ReturnToTitle;
	pauseFuncs[(unsigned)Pause::Texts::RESUME] = &CActionField::Resume;
	
	gameClearFuncs[(unsigned)GameClearMenu::Texts::RETURN_TO_TITLE] = &CActionField::ReturnToTitle;
	gameClearFuncs[(unsigned)GameClearMenu::Texts::GO_TO_NEXT_STAGE] = &CActionField::GoToNextStage;

	gameOverFuncs[(unsigned)GameOverMenu::Texts::RETURN_TO_START] = &CActionField::ReturnToStart;
	gameOverFuncs[(unsigned)GameOverMenu::Texts::RETURN_TO_TITLE] = &CActionField::ReturnToTitle;

	//////マップ読み込み///////////////
	if (limitdata[_stageNum] == 0) {
		std::string s = "noseResource/limitdata"; 
		s += std::to_string(_stageNum);
		s += ".png";
		limitdata[_stageNum] = LoadSoftImage(s.c_str());
	}
	if (mapdata[_stageNum] == 0) {
		std::string s = "noseResource/mapdata";
		s += std::to_string(_stageNum);
		s += ".png";
		mapdata[_stageNum] = LoadSoftImage(s.c_str());
	}
	////////////

	int r, g, b, a;
	for (int i = 0; i < width;i++) {
		for (int j = 0; j < height;j++) {
			GetPixelSoftImage( limitdata[_stageNum],i,j,&r,&g,&b,&a);
			if (r == 255 && g == 0 && b == 0) {
				limit[i] = j;
			}
			GetPixelSoftImage(mapdata[_stageNum], i, j, &r , &g , &b, &a);
			if (r == 128 && g == 128 && b == 128) {
				sc[i].push_back(new CScaffold(ScaffoldType::NORMAL,i,j) );
				firstSc[i][j] = new CScaffold(ScaffoldType::NORMAL, i, j);
				firstPut[i][j] = true;
			}
			else if (r == 255 && g == 128 && b == 0) {
				coin->Add(i, j);
			}
			else if (r == 255 && g == 0 && b == 255) {
				sc[i].push_back(new CScaffold(ScaffoldType::GOAL, i, j));
				firstSc[i][j] = new CScaffold(ScaffoldType::GOAL, i, j);
				firstPut[i][j] = true;
				width = i+5;
			}
			else if (r == 255 && g == 0 && b == 0) {
				sc[i].push_back(new CScaffold(ScaffoldType::JUMP, i, j));
				firstSc[i][j] = new CScaffold(ScaffoldType::JUMP, i, j);
				firstPut[i][j] = true;
			}
			else if (r == 255 && g == 255 && b == 0) {
				sc[i].push_back(new CScaffold(ScaffoldType::SPEED_UP, i, j));
				firstSc[i][j] = new CScaffold(ScaffoldType::SPEED_UP, i, j);
				firstPut[i][j] = true;
			}
			else if (r == 0 && g == 0 && b == 255) {
				sc[i].push_back(new CScaffold(ScaffoldType::SPEED_DOWN, i, j));
				firstSc[i][j] = new CScaffold(ScaffoldType::SPEED_DOWN, i, j);
				firstPut[i][j] = true;
			}
		}
	}
	
	////////////////////////////////////////
}
CActionField::~CActionField() {
	for (int i = 0; i < width; i++) {
		for (auto j : sc[i]) {
			delete j;
		}
	}
	for (int i = 0; i < width;i++) {
		for (int j = 0; j < 15;j++) {
			if (firstPut[i][j]) {
				delete firstSc[i][j];
			}
		}
	}
	delete me;
	delete coin;
	delete pauseMenu;
	delete gameOverMenu;
	delete gameClearMenu;
}

void CActionField::Update(int _scroll){
	coinGotFlag = false;
	if (me->GameClear()) {
		Draw(_scroll);
		gameClearMenu->Update(finalStageNum);
		if (gameClearMenu->Selected()) {
			(this->*gameClearFuncs[(unsigned)gameClearMenu->SelectedText()])();
		}
	}else if (me->GameOver()) {
		Draw(_scroll);
		me->SetV(underSea);
		me->Move();
		me->ResetV();
		gameOverMenu->Update();
		if (gameOverMenu->Selected()) {
			(this->*gameOverFuncs[(unsigned)gameOverMenu->SelectedText()])();
		}
	}
	else{
		if (!menuOpening) {
			me->SetV(underSea);
			Collision();//ここでcoinGotFlagがtrueになるかも
			Move();
			me->ResetV();
			me->ResetHit();
		}
		Draw(_scroll);
		MenuButtonUpdate();
		if ( menuOpening ) {
			pauseMenu->Update();
			if ( pauseMenu->Selected() ) {
				(this->*pauseFuncs[(unsigned)pauseMenu->SelectedText()])();
			}
		}
	}
}

void CActionField::OnlyDraw(int _scroll) {
	coinGotFlag = false;
	DrawBox(WINDOW_WIDTH - (20 * 2 + 50) + 6, WINDOW_HEIGHT - (50 * 4 + 20 * 5) - 47, WINDOW_WIDTH - (20 * 2 + 50) + 83, WINDOW_HEIGHT - (50 * 4 + 20 * 5) - 25, ORANGE, true);
	DrawBox(WINDOW_WIDTH - (20 * 2 + 50) + 6, WINDOW_HEIGHT - (50 * 4 + 20 * 5) - 47, WINDOW_WIDTH - (20 * 2 + 50) + 83, WINDOW_HEIGHT - (50 * 4 + 20 * 5) - 25, WHITE, false);
	DrawLimit(_scroll);
	me->Draw(_scroll);
	for (int i = 0; i < width; i++) {
		for (auto j : sc[i]) {
			j->Draw(_scroll);
		}
	}
	coin->Draw(_scroll);
	static int menuGraph = LoadGraph("noseResource/menuBottun.png");
	DrawGraph(WINDOW_WIDTH - (20 * 2 + 50) + 10, WINDOW_HEIGHT - (50 * 4 + 20 * 5) - 47, menuGraph, true);
	MenuButtonUpdate();
	
}

void CActionField::Make(int _x,int _y,ScaffoldType _type,int _scroll) {
	/*for (int i = max(DRAW_AREA_LEFT / 50+1 , _info.x1); i <= min(DRAW_AREA_RIGHT/50, _info.x2); i++) {
		int temp = 0;
		if (!sc[i + (_scroll / 50)].empty()) {
			temp = sc[i + (_scroll / 50)].back()->Y();
		}
		for (int j = max((DRAW_AREA_TOP + 1) / 50, _info.y1); j <= min((DRAW_AREA_TOP + 151) / 50 - 1, _info.y2); j++) {
			if (temp <= 9) {
				sc[i + (_scroll / 50)].push_back(new CScaffold(_info.type, i + (_scroll / 50), j));
				temp++;
			}
		}
	}*/
	if (sc[_x / 50 + (_scroll / 50)].size() <= 9 || _type==ScaffoldType::ERASER) {
		sc[_x / 50 + (_scroll / 50)].push_back(new CScaffold(_type, _x / 50 + (_scroll / 50), _y / 50));
	}
}

void CActionField::Restart() {
	me->Restart();
	for (int i = 0; i < width; i++) {
		for (auto j : sc[i]) {
			delete j;
		}
		sc[i].clear();
		for (int j = 0; j < 15;j++) {
			if (firstPut[i][j]) {
				sc[i].push_back(new CScaffold(firstSc[i][j]->Type(), i, j));
			}
		}
	}
	menuOpening = false;
	coin->Reset();
	returnStartFlag = false;
	returnTitleFlag = false;
}

bool CActionField::GameOvered() { return me->GameOver(); };
bool CActionField::GameCleared() { return me->GameClear(); };

void CActionField::DrawMenu() {
	if (menuOpening) {
		pauseMenu->Update();
		if (pauseMenu->Selected()) {
			(this->*pauseFuncs[(unsigned)pauseMenu->SelectedText()])();
		}
	}
}
void CActionField::MenuButtonUpdate() {
	DrawBox(WINDOW_WIDTH - (20 * 2 + 50) + 6, WINDOW_HEIGHT - (50 * 4 + 20 * 5) - 47, WINDOW_WIDTH - (20 * 2 + 50) + 83, WINDOW_HEIGHT - (50 * 4 + 20 * 5) - 25, ORANGE, true);
	DrawBox(WINDOW_WIDTH - (20 * 2 + 50) + 6, WINDOW_HEIGHT - (50 * 4 + 20 * 5) - 47, WINDOW_WIDTH - (20 * 2 + 50) + 83, WINDOW_HEIGHT - (50 * 4 + 20 * 5) - 25, WHITE, false);
	static CMouse mouse(WINDOW_WIDTH - (20 * 2 + 50) + 6, WINDOW_HEIGHT - (50 * 4 + 20 * 5) - 47, WINDOW_WIDTH - (20 * 2 + 50) + 83, WINDOW_HEIGHT - (50 * 4 + 20 * 5) - 25);
	if (mouse.Insided()) {
		static int menuGraph = LoadGraph("noseResource/menuBottunPoint.png");
		DrawGraph(WINDOW_WIDTH - (20 * 2 + 50) + 6, WINDOW_HEIGHT - (50 * 4 + 20 * 5) - 47, menuGraph, true);
		if (mouse.LeftPushed()) {
			menuOpening = true;
		}
	}
	else {
		static int menuGraph = LoadGraph("noseResource/menuBottun.png");
		DrawGraph(WINDOW_WIDTH - (20 * 2 + 50) + 10, WINDOW_HEIGHT - (50 * 4 + 20 * 5) - 47, menuGraph, true);
	}

}

void CActionField::Collision() {
	EraserCollision();
	ScaffoldCollision();
	CoinCollision();
}
	void CActionField::ScaffoldCollision() {
		for (int i = 0; i < 3 && !me->GameOver(); i++) {
			for (int j = 0; j < sc[(int)me->X() / 50 + i].size() && !me->GameOver(); j++) {
				me->CollideWith(sc[(int)me->X() / 50 + i][j]);
			}
		}
	}
	void CActionField::CoinCollision() {
		for (int i = (int)(me->X() / 50); i < me->X() / 50 + 1; i++) {
			for (int j = (int)(me->Y() / 50); j < me->Y() / 50 + 1; j++) {
				if (coin->Valid(i, j)) {
					coin->Delete(i, j);
					coinGotFlag = true;
				}
			}
		}
	}
	void CActionField::EraserCollision() {
		for (int i = 0; i < width; i++) {
			for (int j = 0; j < sc[i].size(); j++) {
				if (sc[i][j]->Type() == ScaffoldType::ERASER) {
					if (j != 0) {//上側のやつを消す処理
						if (sc[i][j - 1]->Y() * 50 + 50 > sc[i][j]->Y() * 50 && sc[i][j-1]->Type()!=ScaffoldType::GOAL) {
							delete sc[i][j - 1];
							for (int k = j - 1; k < sc[i].size() - 1; k++) {
								sc[i][k] = sc[i][k + 1];
							}
							sc[i].pop_back();
						}
					}
					else {
						if (sc[i][0]->Y() * 50 + 50<0) {//画面上側までいったら消す
							delete sc[i][0];
							for (int k = 0; k < sc[i].size() - 1; k++) {
								sc[i][k] = sc[i][k + 1];
							}
							sc[i].pop_back();
						}
					}
				}
			}
		}
	}

void CActionField::Draw(int _scroll) {
	DrawLimit(_scroll);
	me->Draw(_scroll);
	for (int i = 0; i < width; i++) {	
		for (auto j : sc[i]) {
			j->Draw(_scroll);
		}
	}
	coin->Draw(_scroll);
}
	void CActionField::DrawLimit(int _scroll) {
		static int limitGraph = LoadGraph("noseResource/limit.png");
		
		for (int i = 0; i < width; i++) {
			if (0 < i*50+50-_scroll && i*50-_scroll < WINDOW_WIDTH) {
				DrawGraph(i*50-_scroll,limit[i]*50-5,limitGraph,true);
				//DrawFormatString(0,i*15,YELLOW,"%d",limit[i]);
			}
		}
		
	}
void CActionField::Move() {
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < sc[i].size(); j++) {
			if (j == 0) {
				sc[i][j]->Move(limit[i],underSea);
			}
			else {
				sc[i][j]->Move(max(limit[i],sc[i][j - 1]->Y() + 1),underSea);
			}
		}
	}
	me->Move();
}

int CActionField::MeX() { return me->X(); };
int CActionField::MeY() { return me->Y(); };
void CActionField::ReturnToTitle() {
	returnTitleFlag = true;
}
void CActionField::ReturnToStart() {
	returnStartFlag = true;
}
void CActionField::Resume() {
	menuOpening = false;
}
void CActionField::GoToNextStage() {
	goToNextStageFlag = true;
}