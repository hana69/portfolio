#include "main.h"

//#define ENTERTIME 60　デバッグ用に一時的に変数になっている

void CMain::LoopAwake(){
	Map.Init();
	Player.Init(Map.GetPlaceX(0),Map.GetPlaceY(0));
	Menu.ResetButtonSwitch();
	frame = 0;
}

void CMain::Awake(){
	selectCase = TITLE;
	loopCase = NOT_LOOP;
	menuCase = NOT_MENU;
	howtoCase = NOT_HOWTO;
	resultCase = NOT_RESULT;
	optionCase = NOT_OPTION;

	//selectCase = NOT_SELECT;
	//resultCase = CELEBRATE_GOAL;

	whereToReturn = 0;

	selectingOptionSpot = 0;

	frame = 0;
	time  = 0;

	enterTime = 60;

	Key.Awake();

	Mouse[0].Awake(640,383,800,480);//ボタン
	Mouse[1].Awake(640,26,800,50);//メニューを開く

	Mouse[2].Awake(640,270,800,310);//カードを使う
	Mouse[3].Awake(640,330,800,370);//サイコロを振る

	Mouse[4].Awake(640,52,800,77);//一つ前に戻る

	Mouse[5].Awake(480,350,588,388);//もどる（人数、ステージ選択画面のみ）

	Mouse[6].Awake(362,418,518,450);//あそびかた　次のページへ
	Mouse[7].Awake(198,441,355,475);//あそびかた　前のページへ
	Mouse[8].Awake(622,440,722,472);//あそびかたから戻る

	Mouse[9].Awake(440,80,480,135);
	Mouse[10].Awake(630,80,670,135);

	Mouse[11].Awake(437,182,628,238);
	Mouse[12].Awake(630,182,671,238);

	Mouse[13].Awake(440,325,480,380);
	Mouse[14].Awake(630,325,670,380);

	Mouse[15].Awake(552,445,708,473);

	Mouse[16].Awake(0,0,800,480);//全範囲

	LoadDivGraph("sugoroku_Resource/button.PNG",2,2,1,160,96,buttonPic);

	maplookPic = LoadGraph("sugoroku_Resource/lookmapinfp,png");

	selectSpot = 1;

	selectSpotPic=LoadGraph("sugoroku_Resource/aomidori.png");
	selectPic = LoadGraph("sugoroku_Resource/sentaku.png");
	howToPic[1] = LoadGraph("sugoroku_Resource/HowToPlay1.png");
	howToPic[2] = LoadGraph("sugoroku_Resource/HowToPlay2.png");

	goalPic=LoadGraph("sugoroku_Resource/aftergoal.png");
	resultPic=LoadGraph("sugoroku_Resource/result.png");

	optionPic = LoadGraph("sugoroku_Resource/option.png");

	sound.cancel = LoadSoundMem("sugoroku_Resource/modoru.mp3");
	sound.dice = LoadSoundMem("sugoroku_Resource/erabu.mp3");

	Dice.Awake();
	Map.Awake();
	Player.Awake();
	Menu.Awake();
	Title.Awake();

	loopBGM[0] = LoadSoundMem("sugoroku_Resource/BGM1.mp3");
	loopBGM[1] = LoadSoundMem("sugoroku_Resource/BGM2.mp3");
	loopBGM[2] = LoadSoundMem("sugoroku_Resource/BGM3.mp3");
	loopBGM[3] = LoadSoundMem("sugoroku_Resource/BGM4.mp3");

	sound.clear=LoadSoundMem("sugoroku_Resource/clear.mp3");

	bgmNum=GetRand(BGMMAX);
	PlaySoundMem(loopBGM[bgmNum],DX_PLAYTYPE_LOOP);
}

void CMain::Loop(){
	
	Map.Draw();
	Player.Draw( Map.GetScrollChangeX(),Map.GetScrollChangeY() );

	for(int i=0;i<4;i++){
		Player.SetPlace( i,Map.GetPlaceX(Player.GetPlace(i)) , Map.GetPlaceY(Player.GetPlace(i)) );//Playerの「今ｎマス目にいる」という情報を受け取ったMapが「ｎマス目のｘ（ｙ）座標」を返してそれをもとにPlayerが描画する位置を決めてる
	}

	Map.SetScroll( Player.GetX(TURN) , Player.GetY(TURN) );//スクロールする値はターンプレイヤーの座標に依存する
	
	DrawMiniMap();//左上の小さいマップ

	if(Dice.GetDebugMode()==2){
		Txt.Draw(Player.GetTurn()+1 , loopCase , Dice.GetNum()-(frame-time)/5 , frame-time );
	}else{
		Txt.Draw(Player.GetTurn()+1 , loopCase , Dice.GetNum()-(frame-time)/30 , frame-time );
	}

	Dice.DiceDraw(loopCase,frame);

	Menu.SubDraw(Map.GetGoal()-Player.GetPlace(TURN));//右にある縦長の黄緑枠の箱を描く
	Player.DrawNowPlace(Map.GetGoal());

	if(Mouse[0].GetFlag()==false){///////////右下のボタンの表示
		DrawGraph(640,384,buttonPic[0],true);
	}
	else{
		DrawGraph(640,384,buttonPic[1],true);
	}

	if(loopCase!=MOVE && loopCase != USE_CARD){//動いてる時にこれをするとバグるので
		Dice.ModeSelect();
		MenuOpen();
	}
	
	Player.Manage(loopCase ,Map.GetPlaceType( Player.GetPlace(TURN) ), frame , time , Dice.GetNum() ,Map.GetGoal(), Dice.GetDebugMode());//プレイヤーに関する中でloopCaseによってやることが変わるもの

	frame++;
}

void CMain::MenuOpen(){
	if( Menu.Opened() ){
		Menu.Init(loopCase);
		loopCase = NOT_LOOP;
		menuCase = MENU;
	}

}

void CMain::DrawMiniMap(){
	Map.DrawMini();
	Player.DrawMini(Map.GetScrollChangeX(),Map.GetScrollChangeY(),frame);
}

void CMain::ChangeCase(){

	if(Mouse[0].Pushed()){
		Mouse[0].SetFlag();
	}

	if(loopCase==MOVE){//移動する時は出た目によって時間が変わる
		loopCase = plus1_L[loopCase];
		time = frame;
	}

	else
	if(Key.Pushed(KEY_INPUT_RETURN,SUGOROKU_SOUND) || Key.Hold(KEY_INPUT_RETURN,enterTime,SUGOROKU_SOUND) || Mouse[0].Released()){
		
		if(loopCase == JUDGE_STATUS ){
			if( Player.GetPlace(TURN) >= Map.GetGoal() || Player.GetStatus(TURN)==1){//休み/ゴール後の判定
				loopCase = DRAW_TEXT;
			}
		}
		
		if(loopCase == USE_CARD){
			loopCase = EFFECT;
			time=frame;
		}

		if(loopCase == JUDGE_GOAL){
			Player.SetTurn();
		}

		loopCase = plus1_L[loopCase];
		time = frame;

	}

}

void CMain::BackCase(){
	if(Mouse[4].Pushed()){
		Mouse[4].SetFlag();
	}
	if(Mouse[4].GetFlag()==true){
		DrawExtendGraph(641,52,799,77,selectSpotPic,true);
	}
	if(Mouse[5].Pushed()){
		Mouse[5].SetFlag();
	}
	if(selectCase != NOT_SELECT && loopCase == NOT_SELECT){
		if(Key.Pushed(KEY_INPUT_BACK,TITLE_SOUND) ){
			selectCase = minus1_S[selectCase];
		}
	}
	else if(Key.Pushed(KEY_INPUT_BACK,SUGOROKU_SOUND) ){
		loopCase = minus1_L[loopCase];
	}

	if(Mouse[5].Released()){
		selectCase = minus1_S[selectCase];
	}
	if(Mouse[4].Released() ){
		loopCase = minus1_L[loopCase];
	}
	

}

int CMain::SelectMovement(){
	
	DrawGraph(641,270,selectPic,true);

	switch(selectSpot){
	case 0:	//カードを使う
		if(Key.Pushed(KEY_INPUT_UP,SUGOROKU_SOUND)||Key.Hold(KEY_INPUT_UP,10,SUGOROKU_SOUND)||
		   Key.Hold(KEY_INPUT_DOWN,10,SUGOROKU_SOUND)||Key.Pushed(KEY_INPUT_DOWN,SUGOROKU_SOUND)){
			selectSpot = 1;
		}

		if(Key.Pushed(KEY_INPUT_RETURN,SUGOROKU_SOUND)){
			return 1;
		}

		DrawGraph(640,270,selectSpotPic,true);
		break;
	case 1://サイコロを振る
		if(Key.Pushed(KEY_INPUT_UP,SUGOROKU_SOUND)|| Key.Hold(KEY_INPUT_UP,10,SUGOROKU_SOUND) ||
		   Key.Hold(KEY_INPUT_DOWN,10,SUGOROKU_SOUND) || Key.Pushed(KEY_INPUT_DOWN,SUGOROKU_SOUND)){
			selectSpot = 0 ;
		}

		if(Key.Pushed(KEY_INPUT_RETURN,SUGOROKU_SOUND) || Key.Hold(KEY_INPUT_RETURN,10,SUGOROKU_SOUND)){
			return 2;
		}

		DrawGraph(640,330,selectSpotPic,true);
		break;
	default: break;
	}

	if( Mouse[2].Pushed()){
		Mouse[2].SetFlag();
		selectSpot = 0;
	}
	if( Mouse[3].Pushed() ){
		Mouse[3].SetFlag();
		selectSpot = 1;
	}

	if(Mouse[2].Released()){
		return 1;
	}
	if(Mouse[3].Released()){
		return 2;
	}

	return 0;
}

void CMain::GameLoop(){

	if(Dice.GetDebugMode()==2){
		enterTime = 20;
	}
	else{
		enterTime = 60;
	}
/////////////////////////////////////////////////////////////////////////////////////
	switch(selectCase){
		case TITLE:
			Title.Draw(selectCase,frame);
			Title.ModeSelect(selectCase);

			switch(Title.EndModeSelect() ){
			case 1:
				selectCase = SELECT_PLAYNUM;
				break;
			case 2:
				whereToReturn = 1;
				selectCase = NOT_SELECT;
				howtoCase = HOWTO_1;
				break;
			case 3:
				selectCase = NOT_SELECT;
				optionCase = OPTION;
				optionWhereReturn = 1;
				break;
			default:break;
			}
			frame++;
			break;
		case SELECT_PLAYNUM:
			Title.Draw(selectCase,frame);
			Player.PlayNumSelect(frame);

			if(Player.EndNumSelect()){
				selectCase = SELECT_STAGE;
				time = frame;
			}
			else{
				BackCase();
			}
			
			frame++;
			break;
		case SELECT_STAGE:
			Title.Draw(selectCase,frame);
			Map.Select();

			if(Map.EndSelect()){
				LoopAwake();
				selectCase = NOT_SELECT;
				loopCase = JUDGE_STATUS;
				time=frame;
			}
			else{
				BackCase();
			}
			frame++;
			break;
	}
	/////////////////////////////////////////////////

	switch(optionCase){
	case OPTION:
		DrawGraph(0,0,optionPic,true);
		for(int i=9;i<15;i++){
			if(Mouse[i].Pushed()){
				Mouse[i].SetFlag();
				selectingOptionSpot = (int)(i-9)/2;//9,10のとき0、11,12のとき１、13,14のとき２
			}
		}
		if(Mouse[15].Pushed()){
			Mouse[15].SetFlag();
		}

		switch(selectingOptionSpot){
		case 0:
			if(Dice.GetDebugMode()==2){
				if(Key.Pushed(KEY_INPUT_LEFT,TITLE_SOUND) || Key.Pushed(KEY_INPUT_RIGHT,TITLE_SOUND) ){
					Dice.SetDebugMode(0);
				}
			}else{
				if(Key.Pushed(KEY_INPUT_LEFT,TITLE_SOUND) || Key.Pushed(KEY_INPUT_RIGHT,TITLE_SOUND) ){
					Dice.SetDebugMode(2);
				}
			}
			DrawBox(510,80,600,135,BLUE,false);
			break;
		case 1:
			if(pointBattle){
				if(Key.Pushed(KEY_INPUT_LEFT,TITLE_SOUND) || Key.Pushed(KEY_INPUT_RIGHT,TITLE_SOUND)){
					pointBattle = false;				
				}
			}else{
				if(Key.Pushed(KEY_INPUT_LEFT,TITLE_SOUND) || Key.Pushed(KEY_INPUT_RIGHT,TITLE_SOUND)){
					pointBattle = true;
				}
			}
			DrawBox(510,184,600,236,BLUE,false);
			break;
		case 2:
			if(Key.Pushed(KEY_INPUT_LEFT,TITLE_SOUND)){
				bgmNum--;
				if(bgmNum < 0){
					bgmNum = BGMMAX;
				}
				if(bgmNum == BGMMAX){
					StopSoundMem(loopBGM[0]);
				}else{
					StopSoundMem(loopBGM[bgmNum+1]);
				}
				PlaySoundMem(loopBGM[bgmNum],DX_PLAYTYPE_LOOP);
			}
			if(Key.Pushed(KEY_INPUT_RIGHT,TITLE_SOUND)){
				bgmNum++;
				if(bgmNum > BGMMAX){
					bgmNum = 0;
				}
				if(bgmNum == 0){
					StopSoundMem(loopBGM[BGMMAX]);
				}
				else{
					StopSoundMem(loopBGM[bgmNum-1]);
				}
				PlaySoundMem(loopBGM[bgmNum],DX_PLAYTYPE_LOOP);
			}
			
			DrawBox(490,327,620,380,BLUE,false);
			break;
		default:
			break;
		}
		SetFontSize(24);
		if(Dice.GetDebugMode()==2){
			DrawString(520,90,"はやい",BLACK);
		}else{
			DrawString(520,90,"おそい",BLACK);
		}
		if(pointBattle){
			DrawString(520,200,"する",BLACK);
		}else{
			DrawString(520,200,"しない",BLACK);
		}
		DrawFormatString(500,345,BLACK,"おんがく%d",bgmNum+1);
		SetFontSize(16);
		if(Mouse[14].Released()){
			bgmNum ++;
			if(bgmNum > BGMMAX){
				bgmNum = 0;
			}
			if(bgmNum == 0){
				StopSoundMem(loopBGM[BGMMAX]);
			}else{
				StopSoundMem(loopBGM[bgmNum-1]);
			}
			PlaySoundMem(loopBGM[bgmNum],DX_PLAYTYPE_LOOP);
		}
		if(Mouse[13].Released() ){
			bgmNum--;
			if(bgmNum < 0){
				bgmNum = BGMMAX;
			}
			if(bgmNum == BGMMAX){
				StopSoundMem(loopBGM[0]);
			}else{
				StopSoundMem(loopBGM[bgmNum+1]);
			}
			PlaySoundMem(loopBGM[bgmNum],DX_PLAYTYPE_LOOP);
		}
		if(Mouse[11].Released() || Mouse[12].Released()){
			if(pointBattle==true){
				pointBattle = false;
			}
			else if(pointBattle==false){
				pointBattle = true;
			}
		}
		if(Mouse[10].Released() || Mouse[9].Released()){
			if(Dice.GetDebugMode() == 2){
				Dice.SetDebugMode(0);
			}
			else if(Dice.GetDebugMode() == 1){
				Dice.SetDebugMode(2);
			}
		}
		if(Key.Pushed(KEY_INPUT_DOWN,TITLE_SOUND)){
			selectingOptionSpot ++;
		}
		if(Key.Pushed(KEY_INPUT_UP,TITLE_SOUND)){
			selectingOptionSpot--;
		}
		if(selectingOptionSpot > 2){
			selectingOptionSpot = 0;
		}
		if(selectingOptionSpot < 0){
			selectingOptionSpot = 2;
		}

		if(Key.Pushed(KEY_INPUT_BACK,TITLE_SOUND) || Mouse[15].Released()){
			optionCase=NOT_OPTION;
			time = frame;
			if(optionWhereReturn == 1){
				selectCase=TITLE;
			}
			else if(optionWhereReturn == 2){
				menuCase = MENU;
			}
		}

		break;
	default:break;
	}

///////////////////////////////////////////////////////////////////////////
	switch(loopCase){
		case JUDGE_STATUS:
			Loop();
			ChangeCase();
			
			break;
		case SELECT_MOVEMENT:
			Loop();
			switch(SelectMovement()){
			case 1:
				loopCase = USE_CARD;
				time = frame;
				break;
			case 2:
				loopCase = ROLL_DICE;
				time = frame;
				break;
			default :break;
			}
			
			break;
		case USE_CARD:
			Loop();

			if(Player.CardConfirm()){
				Txt.CardConfirmDraw();
			}
			
			if(Player.CardIsUsed()){
				Txt.CardEffectDraw(Player.GetUsedCardNum(), Player.GetPiNum(),Player.Get_go_or_return());
				
				DrawString(10 , 380 , "Enterキーを押すか、ボタンを押してください" , WHITE);
				ChangeCase();
			}
			else if(Player.GetCardEffect()==false){//効果の反映中に戻るとバグが起きるため
				BackCase();
			}

			break;
		case ROLL_DICE:
			Loop();
			ChangeCase();
			BackCase();
			if(frame%6==0){
				PlaySoundMem(sound.dice,DX_PLAYTYPE_BACK);
			}
			break;
		case MOVE:
			if(time == frame){
				Dice.SetNum();
			}
				
			Loop();

			if(Dice.GetDebugMode()==2){  //高速モード
				if(frame >= time+(Dice.GetNum())*5){
					ChangeCase();
				}
			}	
			else if(frame >= time+(Dice.GetNum())*30){//動き終ったら次のＣａｓｅへ
				ChangeCase();
			}

			break;
		case DRAW_TEXT:
			Loop();
			Txt.EffectDraw( Map.GetPlaceType(Player.GetPlace(TURN) ) );
			ChangeCase();

			break;
		case EFFECT:
			Loop();
			Player.CardDraw();

			if(Player.EffectEnded()){
				ChangeCase();
			}
			break;
		case JUDGE_GOAL:
			Loop();
			if(Player.Goaled()){
				loopCase=NOT_LOOP;
				resultCase=CELEBRATE_GOAL;
				time=frame;
			}

			ChangeCase();
			break;
	}
//////////////////////////////////////メニュー//////////////////////////////////////////	
	switch(menuCase){
		case MENU:
			DrawMiniMap();
			Map.Draw();
			Player.Draw(Map.GetScrollChangeX(),Map.GetScrollChangeY() );

			Menu.Draw();
			Menu.SubDraw(Map.GetGoal()-Player.GetPlace(TURN));
			Player.DrawNowPlace(Map.GetGoal());
			DrawGraph(640,384,buttonPic[0],true);
			Player.CardDraw();

			Menu.Select();

			switch( Menu.SelectedCase() ){
			case 0:
				menuCase = NOT_MENU;
				selectCase = TITLE;
				break;
			case 1:
				whereToReturn = 2;
				menuCase = NOT_MENU;
				howtoCase = HOWTO_1;
				break;
			case 2:
				menuCase = MAPLOOK;
				Menu.ResetButtonSwitch();
				break;
			case 3:
				menuCase = NOT_MENU;
				optionCase = OPTION;
				optionWhereReturn = 2;
			}

			if(Menu.Closed()){
				menuCase = NOT_MENU;
				loopCase = Menu.GetTempCase();
				PlaySoundMem(sound.cancel,DX_PLAYTYPE_BACK);
			}

			break;

		case MAPLOOK:
			Map.Look();

			Map.Draw();
			Player.Draw(Map.GetScrollChangeX(),Map.GetScrollChangeY());
			Menu.SubDraw(Map.GetGoal()-Player.GetPlace(TURN));
			Player.DrawNowPlace(Map.GetGoal());
			DrawGraph(640,384,buttonPic[0],true);
			Player.CardDraw();
			DrawMiniMap();

			DrawGraph(400,10,maplookPic,true);

			if( Menu.Opened() ){
				menuCase = MENU; 
				Map.Back();
				Menu.Init( Menu.GetTempCase() );
				frame = time;
			}

			frame++;

			break;
	}
	
//////////////////////////////////あそびかた//////////////////////////////////////////////

	switch(howtoCase){
	case HOWTO_1:
		DrawGraph(0,0,howToPic[1],true);

		if(Mouse[6].Pushed()){
			Mouse[6].SetFlag();
		}
		if(Mouse[6].Released()){
			howtoCase = HOWTO_2;
		}

		if(Key.Pushed(KEY_INPUT_RETURN,TITLE_SOUND)){
			howtoCase = HOWTO_2;
		}
		break;

	case HOWTO_2:
		DrawGraph(0,0,howToPic[2],true);

		if(Key.Pushed(KEY_INPUT_BACK,TITLE_SOUND)){
			howtoCase = HOWTO_1;
		}
		if(Mouse[7].Pushed()){
			Mouse[7].SetFlag();
		}
		if(Mouse[7].Released()){
			howtoCase = HOWTO_1;
		}

		if(Mouse[8].Pushed()){
			Mouse[8].SetFlag();
		}
		
		if(Key.Pushed(KEY_INPUT_RETURN,TITLE_SOUND) || Mouse[8].Released()){
			howtoCase = NOT_HOWTO;
			
			if(whereToReturn == 1){
				selectCase = TITLE;
				frame = time;
			}
			else if(whereToReturn == 2){
				menuCase = MENU;
				Menu.Init( Menu.GetTempCase() );
				frame = time;
			}

		}
		break;
	}
///////////////////////////////リザルト画面////////////////////////////

	switch(resultCase){
	case CELEBRATE_GOAL:
		Map.Draw();
		Map.DrawMini();
		Txt.Draw(Player.GetTurn(),loopCase,0,frame-time);
		Menu.SubDraw(0);
		Player.Draw( Map.GetScrollChangeX(),Map.GetScrollChangeY() );

		DrawGraph(0,0,goalPic,true);

		if(frame-time==0){
			StopSoundMem(loopBGM[bgmNum]);
			PlaySoundMem(sound.clear,DX_PLAYTYPE_BACK);
		}
		
		if(frame-time<120){
			SetFontSize(frame-time);
		}
		else{
			SetFontSize(120);
		}

		DrawString(100,250,"おめでとう！",BLACK);
		SetFontSize(16);

		if(frame-time > 120){
			DrawString(220,450,"Enterを押すか左クリックしてください",RED);
		}
		frame++;
		
		if(Mouse[16].Pushed()){
			Mouse[16].SetFlag();
		}

		if(Key.Pushed(KEY_INPUT_RETURN,RESULT_SOUND) || Mouse[16].Pushed() ){
			if(pointBattle){
				resultCase = RANKING;
			}else{
				resultCase = NOT_RESULT;
				selectCase = TITLE;
			}
			frame=time;

		}
		break;
	case RANKING:
		if(frame-time==0){
			Player.SetRanking(Map.GetGoal());
		}
		frame ++;
		
		if(680-(frame-time-300) >= 200){
			DrawGraph(0,0,resultPic,true);
		}

		Player.DrawRanking(frame-time);
		
		if(Mouse[16].Pushed()){
			Mouse[16].SetFlag();
		}

		if(frame-time >= 840 &&( Key.Pushed(KEY_INPUT_RETURN,RESULT_SOUND)) || Mouse[16].Released() ){
			resultCase = NOT_RESULT;
			selectCase = TITLE;
			bgmNum=GetRand(BGMMAX);
			PlaySoundMem(loopBGM[bgmNum],DX_PLAYTYPE_LOOP);
			frame=time;
		}
		break;
	}

}