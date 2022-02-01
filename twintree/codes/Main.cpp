#include "main.h"
#include <new>
CMain::CMain()
	:Me("(主人公)",700,500,200,150,100,100,50),
	 Girl("(少女)",500,700,50,150,300,200,200),
	 
	 pa_fp(fopen("noseResource/paData.txt","r")),
	 ZANGEKI(pa_fp),KYUGEKI(pa_fp),TOSSIN(pa_fp),MOUSINGEKI(pa_fp),
	 
	 ma_fp(fopen("noseResource/maData.txt","r")),
	 ORIA(ma_fp) ,RAZ_ORIA(ma_fp) ,ORIEL(ma_fp) ,RAZ_ORIEL(ma_fp)  ,ORUBERIA(ma_fp)  ,RAZ_ORUBERIA(ma_fp),
	 RIZEK(ma_fp),RAZ_RIZEK(ma_fp),RIZARK(ma_fp),RAZ_RIZARK(ma_fp),RIZERUKARU(ma_fp),RAZ_RIZERUKARU(ma_fp),
	 ZAHA(ma_fp) ,RAZ_ZAHA(ma_fp) ,ZAFIRA(ma_fp),RAZ_ZAFIRA(ma_fp) ,ZAFIRAM(ma_fp)   ,RAZ_ZAFIRAM(ma_fp),
	 SADAL(ma_fp),RAZ_SADAL(ma_fp),SADALT(ma_fp),RAZ_SADALT(ma_fp) ,SADALTIO(ma_fp)  ,RAZ_SADALTIO(ma_fp),
	 TIMYAKU_MEIDOU(ma_fp),
	 DANKAI(ma_fp),
	 
	 buff_fp(fopen("noseResource/buffData.txt","r")),
	 GEWALT(buff_fp),ERTRAGEN(buff_fp),WEISEN(buff_fp),SIGKEIT(buff_fp),BEEILEN(buff_fp),
	 SCHWACH(buff_fp),KROKANT(buff_fp),LUGE(buff_fp),SCHARF(buff_fp),LANGSAM(buff_fp),
	 
	 recover_fp(fopen("noseResource/recoverData.txt","r")),
	 ERHOLUNG(recover_fp) ,RAZ_ERHOLUNG(recover_fp),
	 TIEROA(recover_fp)   ,RAZ_TIERON(recover_fp),
	 KARUTIROA(recover_fp),KARUTIROA_RAZEL(recover_fp),

	 bst_fp(fopen("noseResource/bstData.txt","r")),
	 KONSUIHADOU( bst_fp),
	 MOUDOKUHADOU( bst_fp),
	 MAHUUHADOU( bst_fp),
	 KONSUISYOUHA( bst_fp),
	 MOUDOKUSYOUHA( bst_fp),
	 MAHUUSYOUHA( bst_fp),

	 bst_recover_fp(fopen("noseResource/bst_recoverData.txt","r")),
	 PRIOA(bst_recover_fp),PRIOA_RAZEL(bst_recover_fp),
	 TORMIA(bst_recover_fp),TORMIA_RAZEL(bst_recover_fp),
	 PETOROIA(bst_recover_fp),PETOROIA_RAZEL(bst_recover_fp),
	 
	 Battles(&Me,&Girl),SkillMessage(100,380,605,73)
{
	fclose(pa_fp);
	fclose(ma_fp);
	fclose(buff_fp);
	fclose(recover_fp);
	fclose(bst_fp);
	fclose(bst_recover_fp);
	
	saveData=fopen("noseResource/saveData.txt","r");
	fscanf(saveData,"%d",&battleLevelLimit);
	for(int i=0;i<4;i++){
		fscanf(saveData,"%d",&nowSkillLevel[i]);
		for(int j=0;j<10;j++){
			new(&Skills[i][j])CSkillManager(130,80);
		}
	}
	fclose(saveData);
	for(int i=0;i<2;i++){
		new(&UseSkills[i])CSkillManager(425,80);
		UseSkills[i].UnSelectable();
	}
	scene=TITLE;
	selectingSkillType=M_A;
	
	
	REDRAMP.AddSkill(&TOSSIN,100);

	YELLOWRAMP.AddSkill(&TOSSIN,70);
	YELLOWRAMP.AddSkill(&GEWALT,30);

	BLUERAMP.AddSkill(&RIZEK,30);
	BLUERAMP.AddSkill(&ERHOLUNG,20);
	BLUERAMP.AddSkill(&SCHWACH,25);
	BLUERAMP.AddSkill(&KROKANT,25);

	PURPLERAMP.AddSkill(&ORUBERIA,20);
	PURPLERAMP.AddSkill(&RIZERUKARU,20);
	PURPLERAMP.AddSkill(&MOUSINGEKI,60);
	
	BLACK_FIRERAMP.AddSkill(&RAZ_ORUBERIA,20);
	BLACK_FIRERAMP.AddSkill(&WEISEN,20);
	BLACK_FIRERAMP.AddSkill(&PETOROIA_RAZEL,10);
	BLACK_FIRERAMP.AddSkill(&TIMYAKU_MEIDOU,50);

	WHITE_THUNDERRAMP.AddSkill(&MOUSINGEKI,100);
	frame=tempframe=0;
}
///////////パブリック関数///////////////
void CMain::Awake(){
	fclose(enemy_fp);

	backPic=LoadGraph("noseResource/haikei_normal.png");
	titleBGM=LoadSoundMem("noseResource/title.mp3");

	//World.Awake();
	Title.Awake();
	SetSelectSkill();
}

void CMain::GameLoop(){
	
	switch(scene){
	case TITLE:
		if(frame==tempframe){
			PlaySoundMem(titleBGM,DX_PLAYTYPE_LOOP);
		}
		Title.Draw();
		if(Title.GetEnd()){
			scene=SELECT_SKILL;
			tempframe=frame+1;
		}
		break;
	case SELECT_SKILL:
		SelectSkill();
		break;
	case SELECT_BATTLE:
		SelectBattle();
		break;
	case BATTLE:
		if(tempframe==frame){
			StopSoundMem(titleBGM);
			
		}
		Battles.Main();
		if(Battles.Finished()){
			scene=TITLE;
			tempframe=frame+1;
		}
		break;
	}
	frame++;
}


//////////プライベート関数/////////////
void CMain::SetSelectSkill(){
	Skills[M_A][0].LearnNewSkill(&ORIA);
	Skills[M_A][0].LearnNewSkill(&RIZEK);
	Skills[M_A][0].LearnNewSkill(&ZAHA);
	Skills[M_A][0].LearnNewSkill(&SADAL);
	Skills[M_A][1].LearnNewSkill(&RAZ_ORIA);
	Skills[M_A][1].LearnNewSkill(&RAZ_RIZEK);
	Skills[M_A][1].LearnNewSkill(&RAZ_ZAHA);
	Skills[M_A][1].LearnNewSkill(&RAZ_SADAL);
	Skills[M_A][2].LearnNewSkill(&ORIEL);
	Skills[M_A][2].LearnNewSkill(&RIZARK);
	Skills[M_A][2].LearnNewSkill(&ZAFIRA);
	Skills[M_A][2].LearnNewSkill(&SADALT);
	Skills[M_A][3].LearnNewSkill(&RAZ_ORIEL);
	Skills[M_A][3].LearnNewSkill(&RAZ_RIZARK);
	Skills[M_A][3].LearnNewSkill(&RAZ_ZAFIRA);
	Skills[M_A][3].LearnNewSkill(&RAZ_SADALT);
	Skills[M_A][4].LearnNewSkill(&ORUBERIA);
	Skills[M_A][4].LearnNewSkill(&RIZERUKARU);
	Skills[M_A][4].LearnNewSkill(&ZAFIRAM);
	Skills[M_A][4].LearnNewSkill(&SADALTIO);
	Skills[M_A][5].LearnNewSkill(&RAZ_ORUBERIA);
	Skills[M_A][5].LearnNewSkill(&RAZ_RIZERUKARU);
	Skills[M_A][5].LearnNewSkill(&RAZ_ZAFIRAM);
	Skills[M_A][5].LearnNewSkill(&RAZ_SADALTIO);

	Skills[BUFF][0].LearnNewSkill(&SCHWACH);
	Skills[BUFF][0].LearnNewSkill(&KROKANT);
	Skills[BUFF][0].LearnNewSkill(&LUGE);
	Skills[BUFF][0].LearnNewSkill(&SCHARF);
	Skills[BUFF][0].LearnNewSkill(&LANGSAM);
	Skills[BUFF][1].LearnNewSkill(&GEWALT);
	Skills[BUFF][1].LearnNewSkill(&ERTRAGEN);
	Skills[BUFF][1].LearnNewSkill(&WEISEN);
	Skills[BUFF][1].LearnNewSkill(&SIGKEIT);
	Skills[BUFF][1].LearnNewSkill(&BEEILEN);
	
	Skills[BST_RECOVER][0].LearnNewSkill(&ERHOLUNG);
	Skills[BST_RECOVER][0].LearnNewSkill(&PRIOA);
	Skills[BST_RECOVER][0].LearnNewSkill(&TORMIA);
	Skills[BST_RECOVER][1].LearnNewSkill(&RAZ_ERHOLUNG);
	Skills[BST_RECOVER][1].LearnNewSkill(&PRIOA_RAZEL);
	Skills[BST_RECOVER][1].LearnNewSkill(&TORMIA_RAZEL);
	Skills[BST_RECOVER][2].LearnNewSkill(&KONSUIHADOU);
	Skills[BST_RECOVER][2].LearnNewSkill(&MOUDOKUHADOU);
	Skills[BST_RECOVER][2].LearnNewSkill(&MAHUUHADOU);
	Skills[BST_RECOVER][3].LearnNewSkill(&TIEROA);
	Skills[BST_RECOVER][3].LearnNewSkill(&PETOROIA);
	Skills[BST_RECOVER][4].LearnNewSkill(&RAZ_TIERON);
	Skills[BST_RECOVER][4].LearnNewSkill(&KONSUISYOUHA);
	Skills[BST_RECOVER][4].LearnNewSkill(&MOUDOKUSYOUHA);
	Skills[BST_RECOVER][4].LearnNewSkill(&MAHUUSYOUHA);
	Skills[BST_RECOVER][5].LearnNewSkill(&KARUTIROA);
	Skills[BST_RECOVER][5].LearnNewSkill(&PETOROIA_RAZEL);
	Skills[BST_RECOVER][6].LearnNewSkill(&KARUTIROA_RAZEL);
	
	Skills[P_A][0].LearnNewSkill(&ZANGEKI);
	Skills[P_A][0].LearnNewSkill(&KYUGEKI);
	Skills[P_A][1].LearnNewSkill(&TOSSIN);
	Skills[P_A][2].LearnNewSkill(&MOUSINGEKI);
}
void CMain::SelectSkill(){
	
	static int skillReadyGraph[P_A+1]={
		LoadGraph("noseResource/m_a_ready.png"),
		LoadGraph("noseResource/buff_ready.png"),
		LoadGraph("noseResource/bst_recover_ready.png"),
		LoadGraph("noseResource/p_a_ready.png")
	};
	static int skillSelectGraph[P_A+1]={
		LoadGraph("noseResource/m_a_select.png"),
		LoadGraph("noseResource/buff_select.png"),
		LoadGraph("noseResource/bst_recover_select.png"),
		LoadGraph("noseResource/p_a_select.png")
	};
	static int yajirusiGraph[2]={
		LoadGraph("noseResource/yajirusi_left.png"),
		LoadGraph("noseResource/yajirusi_right.png")
	};

	static int selectingSkillLevel;
	static bool skillSelecting;
	static int me_or_girl;
	if(frame==tempframe){
		selectingSkillLevel=0;
		skillSelecting=false;
		me_or_girl=0;
	}

	DrawExtendGraph(0,0,WINDOW_WIDTH,WINDOW_HEIGHT,backPic,true);

	if(!skillSelecting){
		NumSelect_UD((int*)&selectingSkillType,M_A,P_A);
		DrawExtendGraph(0,0,WINDOW_WIDTH,WINDOW_HEIGHT,skillReadyGraph[selectingSkillType],true);
		if(Key.Pushed(KEYNAME.ENTER)){
			skillSelecting=true;
		}
		if(Key.Pushed(KEYNAME.BACK)){
			scene=TITLE;
		}
	}else{
		DrawExtendGraph(0,0,WINDOW_WIDTH,WINDOW_HEIGHT,skillSelectGraph[selectingSkillType],true);
		Skills[selectingSkillType][selectingSkillLevel].Draw();
		if(nowSkillLevel[selectingSkillType] != 0){
			DrawGraph(90,210,yajirusiGraph[0],true);
			DrawGraph(380,210,yajirusiGraph[1],true);
		}
		SkillMessage.Draw();
		if(Skills[selectingSkillType][selectingSkillLevel].Selecting()!=NULL){
			SkillMessage.Call(Skills[selectingSkillType][selectingSkillLevel].Selecting()->GetName().c_str());
			if(Skills[selectingSkillType][selectingSkillLevel].Selecting()->GetHurigana()!="()"){
				SkillMessage.Add(Skills[selectingSkillType][selectingSkillLevel].Selecting()->GetHurigana().c_str());
			}
			SkillMessage.StartNewLine();
			SkillMessage.Add(Skills[selectingSkillType][selectingSkillLevel].Selecting()->GetExplain().c_str());
		}else{
			SkillMessage.Call("");
		}
		NumSelect_LR( &selectingSkillLevel , 0 , nowSkillLevel[selectingSkillType] );
		DrawFormatString(190,50,RED,"レベル%d",selectingSkillLevel+1);
		if(Key.Pushed(KEYNAME.BACK)){
			skillSelecting=false;
			selectingSkillLevel=0;
		}
		if(Skills[selectingSkillType][selectingSkillLevel].Selecting()!=NULL &&
			!UseSkills[me_or_girl].SkillValid(Skills[selectingSkillType][selectingSkillLevel].Selecting()) &&
			Key.Pushed(KEYNAME.ENTER)
		){
			UseSkills[me_or_girl].LearnNewSkill( Skills[selectingSkillType][selectingSkillLevel].Selecting() );
		}
	}	
	
	if(me_or_girl==0){
		DrawString(540,55,"（少女）",RED);
		if(Key.Pushed(KEYNAME.SPACE)){
			if(UseSkills[0].GetSkillNum()!=0){
				Girl.SkillCopy(&UseSkills[me_or_girl]);
				me_or_girl=1;
			}
		}
	}else{
		DrawString(540,55,"（主人公）",RED);
		if(Key.Pushed(KEYNAME.SPACE)){
			if(UseSkills[1].GetSkillNum()!=0){
				Me.SkillCopy(&UseSkills[me_or_girl]);
				scene=SELECT_BATTLE;
				tempframe=frame+1;
			}
		}
	}
	
	if(Key.Pushed(KEYNAME.DELETE_KEY)){
		UseSkills[me_or_girl].DeleteSkill();
	}
	UseSkills[me_or_girl].Draw();
	
}

void CMain::SelectBattle(){
	static int selectBattleBackGroundGraph=LoadGraph("noseResource/battleSelect.png");
	static int selectableGraph[10]={
		LoadGraph("noseResource/selectable1.png"),LoadGraph("noseResource/selectable2.png"),
		LoadGraph("noseResource/selectable3.png"),LoadGraph("noseResource/selectable4.png"),
		LoadGraph("noseResource/selectable5.png"),LoadGraph("noseResource/selectable6.png"),
		LoadGraph("noseResource/selectable7.png"),LoadGraph("noseResource/selectable8.png"),
		LoadGraph("noseResource/selectable9.png"),LoadGraph("noseResource/selectable10.png")
	};
	static int unselectableGraph[10]={
		LoadGraph("noseResource/unselectable1.png"),LoadGraph("noseResource/unselectable2.png"),
		LoadGraph("noseResource/unselectable3.png"),LoadGraph("noseResource/unselectable4.png"),
		LoadGraph("noseResource/unselectable5.png"),LoadGraph("noseResource/unselectable6.png"),
		LoadGraph("noseResource/unselectable7.png"),LoadGraph("noseResource/unselectable8.png"),
		LoadGraph("noseResource/unselectable9.png"),LoadGraph("noseResource/unselectable10.png")
	};
	static int selectingGraph=LoadGraph("noseResource/selecting.png");
	
	static int selectingLevelW=0;
	static int selectingLevelH=0;
	
	static bool confirm=false;
	if(tempframe==frame){
		selectingLevelW=0;
		selectingLevelH=0;
		confirm=false;
	}
	DrawExtendGraph(0,0,WINDOW_WIDTH,WINDOW_HEIGHT,backPic,true);
	DrawGraph(0,0,selectBattleBackGroundGraph,true);

	UseSkills[0].Draw(5,130);
	UseSkills[1].Draw(260,130);

	for(int i=0;i<=battleLevelLimit;i++){
		DrawGraph(520+i%2*120,10+i/2*92,selectableGraph[i],true);
	}
	for(int i=battleLevelLimit+1;i<10;i++){
		DrawGraph(520+i%2*120,10+i/2*92,unselectableGraph[i],true);
	}
	DrawExtendGraph(520+selectingLevelW*120,10+selectingLevelH*92,520+selectingLevelW*120+100,10+selectingLevelH*92+80,selectingGraph,true);

	if(!confirm){
		NumSelect_UD(&selectingLevelH,0,battleLevelLimit/2);
		NumSelect_LR(&selectingLevelW,0,battleLevelLimit%2);
		if(Key.Pushed(KEYNAME.BACK)){
			scene=SELECT_SKILL;
		}
		if(Key.Pushed(KEYNAME.ENTER)){
			confirm=true;
		}
	}else{
		static int yes_or_no=0;
		static int yes_noPic[2]={
			LoadGraph("noseResource/yes.png"),
			LoadGraph("noseResource/no.png")
		};
		DrawGraph(0,0,yes_noPic[yes_or_no],true);
		NumSelect_LR(&yes_or_no,0,1);
		if(Key.Pushed(KEYNAME.ENTER)){
			if(yes_or_no==0){
				scene=BATTLE;
				SetEnemies(selectingLevelW*2+selectingLevelH);
				Battles.StartBattle( (battleLevelLimit==selectingLevelW*2+selectingLevelH)&&(nowSkillLevel[M_A]!=9) );
				tempframe=frame+1;
			}else{
				confirm=false;
			}
		}
	}

}
void CMain::SetEnemies(int _level){
	switch(_level){
	case 0:
		Battles.SetEnemy(&REDRAMP);
		Battles.SetEnemy(&REDRAMP,&YELLOWRAMP,&REDRAMP);
		break;
	case 1:
		Battles.SetEnemy(&REDRAMP,&REDRAMP,&REDRAMP,&REDRAMP,&REDRAMP);
		Battles.SetEnemy(&YELLOWRAMP,&BLUERAMP,&YELLOWRAMP);
		break;
	case 2:
		Battles.SetEnemy(&BLUERAMP,&BLUERAMP);
		Battles.SetEnemy(&YELLOWRAMP,&PURPLERAMP,&YELLOWRAMP);
		break;
	case 3:
		Battles.SetEnemy(&BLACK_FIRERAMP);
		break;
	case 4:
		Battles.SetEnemy(&WHITE_THUNDERRAMP);
		break;
	case 5:

		break;
	case 6:
		
		break;
	case 7:
		
		break;
	case 8:
		
		break;
	case 9:
		
		break;
	}
}
void CMain::SetAlly(int _level){
	switch(_level){
	case 0:

		break;
	case 1:

		break;
	case 2:
		
		break;
	case 3:
		
		break;
	case 4:
		
		break;
	case 5:
		

		break;
	case 6:
		
		break;
	case 7:
		
		break;
	case 8:
		
		break;
	case 9:
		
		break;
	}
}