#include "DxLib.h"
#include "Suken.h"
#include "main.h"

#define FPS 60

int WINAPI WinMain(HINSTANCE,HINSTANCE,LPSTR,int){

	SetWindowText("sugoroku");
	SetWindowIconID(101);
	SetGraphMode(800 , 480 , 16 , 60);
	ChangeWindowMode(TRUE), DxLib_Init(), SetDrawScreen( DX_SCREEN_BACK );
	int img = LoadGraph("sugoroku_Resource/Please_Read_readme.png");
	DrawGraph(0,0,img,true);

	ScreenFlip();

	Sleep(1000);

	CMain Main;

	SetTransColor(155,155,15);

	Main.Awake();

	while( ScreenFlip()==0 && ProcessMessage()==0 && ClearDrawScreen()==0 ){
		Main.GameLoop();
		Sleep((int)(1000/FPS));
	}
        
	DxLib_End();

	ShellExecute( GetMainWindowHandle(),"open " ," Launcher.exe" , NULL , NULL , SW_SHOW );

	return 0;
} 