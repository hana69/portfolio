#include"key.h"
#include"StageManager.h"
#include"mouse.h"

//#include"SaveData.h"

int WINAPI WinMain(HINSTANCE,HINSTANCE,LPSTR,int){
	SetOutApplicationLogValidFlag(false);//Logを出力しない
	SetWindowText("あしばメーカーver.2");
	//SetWindowIconID(101);
	SetGraphMode(WINDOW_WIDTH , WINDOW_HEIGHT , 16 );
	SetUseDirectInputFlag(true);
	ChangeWindowMode(true), DxLib_Init(), SetDrawScreen( DX_SCREEN_BACK );
	
	ScreenFlip();
	//SetTransColor(155,155,15);
	
	StageManager stageManager;
	while( ScreenFlip()==0 && ProcessMessage()==0 && ClearDrawScreen()==0 ){
		CMouse::Update();
		stageManager.UpDate();
		/*if (loopEscapeFlag==true) {
			loopEscapeFlag = false;
			break;
		}*/
		if (Key.Pushed(KEYNAME.ESC)) {
			break;
		}
		Sleep(0);
	}
        
	DxLib_End();
	return 0;
} 