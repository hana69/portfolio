#include"StageManager.h"
#include"General.h"

#include"StageSelector.h"
#include"Stage.h"

#include"Tutorial.h"

StageManager::StageManager()
	:stageSelecting(true),
	isTutorial(false),
	stage(nullptr), tutorial(nullptr)
{
	fopen_s(&fp, "noseResource/saveData.txt", "r");
	fscanf(fp, "%d", &finalStageNum);
	fclose(fp);
	stageSelector = new StageSelector(finalStageNum);
}
StageManager::~StageManager() {
	if (stage!=nullptr) {
		delete stage;
	}
	if (stageSelector!=nullptr) {
		delete stageSelector;
	}
	if (tutorial != nullptr) {
		delete tutorial;
	}
}

void StageManager::UpDate() {	
	if (stageSelecting) {
		stageSelector->Update();
		if (stageSelector->SelectFinished()) {

			if (stageSelector->SelectedStage()!=0) {
				stage = new Stage(stageSelector->SelectedStage(),finalStageNum);
				stageSelecting = false;
				nowPlayingStageNum = stageSelector->SelectedStage();
				delete stageSelector;
				stageSelector = nullptr;
				isTutorial = false;
			}else {
				tutorial = new Tutorial();
				stageSelecting = false;
				nowPlayingStageNum = 0;
				delete stageSelector;
				stageSelector = nullptr;
				isTutorial = true;
			}
		}
	}
	else{
		if (isTutorial) {
			tutorial->Update();
			if (tutorial->SelectedReturnTitle()) {
				stageSelector = new StageSelector(finalStageNum);
				stageSelecting = true;
				delete tutorial; tutorial = nullptr;
			}
			else if (tutorial->SelectedNextStage()) {
				delete tutorial; tutorial = nullptr;
				nowPlayingStageNum = 1;
				stage = new Stage(nowPlayingStageNum,finalStageNum);
				isTutorial = false;
			}
		}
		else {
			stage->Update();
			if (stage->SelectedReturnTitle()) {
				stageSelector = new StageSelector(finalStageNum);
				stageSelecting = true;
				delete stage;
				stage = nullptr;
			}
			else if (stage->SelectedGoToNextStage()) {
				delete stage;
				if (nowPlayingStageNum < finalStageNum) {
					nowPlayingStageNum++;
				}
				stage = new Stage(nowPlayingStageNum,finalStageNum);
			}
		}
		
	}
}

///////////////////////‚ß‚¢‚ñ/////////////////////////
//CMain_S::CMain_S()
//	:stageNum(1),scroll(0),returnTitleFlag(false)
//{}
//
//void CMain_S::Start(int _stageNum) {	
//	field = new CActionField(_stageNum);
//	if (_stageNum == 0) {
//		tutorial = new CTutorial();
//	}
//	returnTitleFlag = false;
//	scroll = 0;
//	scaffoldDrawer.Reset();
//	stageNum = _stageNum;
//}
//
//void CMain_S::Update() {
//	
//	/*if (stageNum == 0) {	
//		if (!tutorial->Explaining()) {
//			if (tutorial->State()>=4) {
//				Scroll();
//			}
//			field->Update(scroll);
//			if (field->MeGotCoin()) {
//				scaffoldDrawer.AddCoin();
//			}
//			scaffoldDrawer.Update();
//			if (scaffoldDrawer.DrawFinished()) {
//				field->Make(scaffoldDrawer.DrawnScaffold(), scroll);
//				if (tutorial->State()==3) {
//					tutorial->DrawEndEffect();
//				}
//			}
//			
//			tutorial->Update(scroll, field->MeX());
//
//			if (field->MenuOpening()) {
//				static CMenu menu;
//				switch (menu.Update()) {
//				case RESUME:
//					field->CloseMenu();
//					break;
//				case RETURN_TO_TITLE_MENU:
//					returnTitleFlag = true;
//					delete field;
//					delete tutorial;
//					break;
//				case RETURN_TO_START_MENU:
//					scroll = 0;
//					field->Restart();
//					scaffoldDrawer.Reset();
//					tutorial->Start();
//					break;
//				}
//			}
//
//			if (field->GameCleared()) {
//				static CGameClearMenu gameClearMenu;
//				switch (gameClearMenu.Update()) {
//				case NEXT_STAGE:
//					delete field;
//					stageNum++;
//					field = new CActionField(stageNum);
//					scaffoldDrawer.Reset();
//					scroll = 0;
//					break;
//				case CLEARED_RETURN_TO_TITLE:
//					returnTitleFlag = true;
//					break;
//				}
//			}
//
//			if (field->GameOvered()) {
//				static CGameOverMenu gameOverMenu;
//				switch (gameOverMenu.Update()) {
//				case RETRY:
//					scroll = 0;
//					field->Restart();
//					scaffoldDrawer.Reset();
//					tutorial->Start();
//					break;
//				case RETURN_TO_TITLE:
//					returnTitleFlag = true;
//					delete field;
//					delete tutorial;
//					break;
//				}
//			}
//		}
//		else {
//			field->OnlyDraw(scroll);
//			scaffoldDrawer.OnlyDraw();
//			tutorial->Update(scroll, field->MeX());
//		}
//	}*/
//	/*else {
//		
//		if (field->MenuOpening()) {
//			static CMenu menu;
//			switch (menu.Update()) {
//			case RESUME:
//				field->CloseMenu();
//				break;
//			case RETURN_TO_TITLE_MENU:
//				returnTitleFlag = true;
//				break;
//			case RETURN_TO_START_MENU:
//				scroll = 0;
//				field->Restart();
//				scaffoldDrawer.Reset();
//				break;
//			}
//		}
//
//		if (field->GameCleared()) {
//			static CGameClearMenu gameClearMenu;
//			switch (gameClearMenu.Update()) {
//			case NEXT_STAGE:
//				if (stageNum < 8) {
//					delete field;
//					stageNum++;
//					field = new CActionField(stageNum);
//					scaffoldDrawer.Reset();
//					scroll = 0;
//				}
//				break;
//			case CLEARED_RETURN_TO_TITLE:
//				returnTitleFlag = true;
//				break;
//			}
//		}
//
//		if (field->GameOvered()) {
//			static CGameOverMenu gameOverMenu;
//			switch (gameOverMenu.Update()) {
//			case RETRY:
//				scroll = 0;
//				field->Restart();
//				scaffoldDrawer.Reset();
//				break;
//			case RETURN_TO_TITLE:
//				returnTitleFlag = true;
//				break;
//			}
//		}
//	}*/
//	
//}
//
//void CMain_S::Scroll() {
//	
//}