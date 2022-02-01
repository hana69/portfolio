#include"Battle.h"
#include<new>

///////�R���X�g���N�^//////
CBattle::CBattle()
:	Message(0,360,752,120),
	confirm("noseResource/battleMenuHaikei.png","noseResource/battleMenuSelect.png",0,300,250,30,1,2,WHITE,RED),
	fight_escape("noseResource/battleMenuHaikei.png","noseResource/battleMenuSelect.png",0,300,250,30,1,2,WHITE,RED),
	skill_item_gard("noseResource/battleMenuHaikei.png","noseResource/battleMenuSelect.png",0,300,250,30,1,2,WHITE,RED),
	NOT_USED("NotUsed","�̂��Ƃ�[����","�X�L�����I���ł�","�X�L�����I���ł�",0,CSkill::BuffType::MA_BUFF,CSkill::ALLY,0)
{

}
CBattle::CBattle(CAlly *_me_p,CAlly *_girl_p):
	Message(0,360,752,120),
	confirm("noseResource/battleMenuHaikei.png","noseResource/battleMenuSelect.png",0,300,250,30,1,2,WHITE,RED),
	fight_escape("noseResource/battleMenuHaikei.png","noseResource/battleMenuSelect.png",0,300,250,30,1,2,WHITE,RED),
	skill_item_gard("noseResource/battleMenuHaikei.png","noseResource/battleMenuSelect.png",0,300,250,30,1,2,WHITE,RED),
	NOT_USED("NotUsed","�̂��Ƃ�[����","�X�L�����I���ł�","�X�L�����I���ł�",0,CSkill::BuffType::MA_BUFF,CSkill::ALLY,0)
{

	ally[ME] = _me_p;
	ally[GIRL] = _girl_p;
	
	myTurn = ME;
	scene = GETTING_READY;
	allySelectScene = FIGHT_ESCAPE;

	for(int i=0;i<7;i++){
		order[i]=(Order)i;
	}
	orderMax=0;

	for(int i=0;i<2;i++){
		allyUseSkill[i] = &NOT_USED;
		allySkillTarget[i] = ALLY_ME_ST;
	}
	for(int i=0;i<5;i++){
		enemyUseSkill[i] = &NOT_USED;
		enemySkillTarget[i] = ALLY_ME_ST;
	}
	for(int i=1;i<=5;i++){
		new(&enemy[i])CEnemy();
	}
	movingNum=0;

	battleEndFlag = false;
	skillSuccessFlag=true;
	firstEnemyNum = 0;
	enemyNum = 0;
	nowTargetNum=1;
	frame=tempframe = 0;

	targetPic=0;
	cursorPic=0;
	haikeiPic=0;

	confirm.AddNewString("�͂�");
	confirm.AddNewString("������");

	fight_escape.AddNewString("��������");
	fight_escape.AddNewString("�ɂ���");

	skill_item_gard.AddNewString("�킴");
	skill_item_gard.AddNewString("�ڂ�����");

}

////////////�p�u���b�N�֐�///////////////
void CBattle::StartBattle(){
	if(targetPic==0){
		targetPic=LoadGraph("noseResource/target.png");
	}
	if(cursorPic==0){
		cursorPic=LoadGraph("noseResource/cursor.png");
	}
	if(haikeiPic==0){
		haikeiPic=LoadGraph("noseResource/haikei_normal.png");
	}
	
	scene = BATTLE;
	tempframe = frame;
	battleEndFlag = false;
	Message.Call("�Ă��������ꂽ�I");
	enemyNum=firstEnemyNum;
	for(int i=1;i<=enemyNum;i++){
		enemy[i].Init();
	}
	myTurn=GIRL;
	SetPosition();
}

void CBattle::AddEnemy(CEnemy* _Enemy){
	if(firstEnemyNum<5){
		if( scene == GETTING_READY ){
			firstEnemyNum++;
			enemy[firstEnemyNum] = *_Enemy;
			tempframe = frame+1;
		}
	}
}

bool CBattle::Ended(){
	return battleEndFlag;
}

void CBattle::Init(){
	myTurn = ME;
	scene = GETTING_READY;
	allySelectScene = FIGHT_ESCAPE;

	for(int i=0;i<7;i++){
		order[i]=(Order)i;
	}
	orderMax=0;

	for(int i=0;i<2;i++){
		allyUseSkill[i] = &NOT_USED;
		allySkillTarget[i] = ALLY_ME_ST;
	}
	for(int i=0;i<5;i++){
		enemyUseSkill[i] = &NOT_USED;
		enemySkillTarget[i] = ALLY_ME_ST;
	}
	for(int i=1;i<=5;i++){
		new(&enemy[i])CEnemy();
	}
	movingNum=0;

	battleEndFlag = false;
	skillSuccessFlag=true;
	firstEnemyNum = 0;
	enemyNum = 0;
	nowTargetNum=1;
	frame=tempframe = 0;

}
void CBattle::main(){
	
	DrawExtendGraph(-50,-120,WINDOW_WIDTH,360,haikeiPic,true);
	
	switch(scene){
	case GETTING_READY:
		break;

	case BATTLE:
		EnemyDraw();
		AllyDraw();
		Battle();
		break;
	case RESULT:
		Message.Call("�G��|�����I");
		firstEnemyNum=1;
		if( frame-tempframe > 0 && Key.Pushed(KEYNAME.ENTER) ){
			scene=GETTING_READY;
			battleEndFlag = true;
			frame=tempframe=0;
		}
		break;

	}
	Message.Draw();
	
	frame++;
}

///////////�v���C�x�[�g�֐�//////////////

void CBattle::SetPosition(){
	switch(firstEnemyNum){
	case 1:
		enemy[1].SetPosition(3);
		break;
	case 2:
		for(int i=1;i<=firstEnemyNum;i++){
			enemy[i].SetPosition(i+1);
		}
		break;
	case 3:
		for(int i=1;i<=firstEnemyNum;i++){
			enemy[i].SetPosition(i+1);
		}
		break;
	case 4:
		for(int i=1;i<=firstEnemyNum;i++){
			enemy[i].SetPosition(i);
		}
		break;
	case 5:
		for(int i=1;i<=firstEnemyNum;i++){
			enemy[i].SetPosition(i);
		}
		break;
	}
}

void CBattle::EnemyDraw(){
	for(int i=1;i<=firstEnemyNum;i++){
		enemy[i].Draw();
	}
}

void CBattle::AllyDraw(){
	
	for(int i=0;i<2;i++){
		ally[i] -> DrawInfo();
	}

	switch(myTurn){
	case ME:
		DrawGraph(270,240,cursorPic,true);
		break;
	case GIRL:
		DrawGraph(535,240,cursorPic,true);
		break;
	case NOT_MY_TURN:
		break;
	}

}

void CBattle::DecideAlly(){
	
	static bool confirmFlag=false;

	if(myTurn!=NOT_MY_TURN){

		switch(allySelectScene){

		case FIGHT_ESCAPE:
			fight_escape.Draw();
			
			if( fight_escape.Selected() ){
				if( fight_escape.SelectingString() == "��������" ){
					allySelectScene = SKILL_ITEM_GARD;
					tempframe = frame+1;
				}
				else if( fight_escape.SelectingString() == "�ɂ���" ){
					allySelectScene = ESCAPE;
					confirmFlag = true;
					tempframe = frame+1;
				}
			}

			break;

		case ESCAPE:

			if( confirmFlag==true ){
			
				Message.Call( "�{���ɂɂ��܂����H" );
				confirm.Draw();

				if( confirm.Selected() ){
					if( confirm.SelectingString()=="�͂�" ){
						confirmFlag = false;
						tempframe = frame+1;
					}
					else if( confirm.SelectingString()=="������" ){
						allySelectScene = FIGHT_ESCAPE;
						confirmFlag = false;
						tempframe = frame+1;
					}
				}

			}
			else{
				Escape();
			}
			break;

		case SKILL_ITEM_GARD:
			if(frame==tempframe){
				Message.Call(ally[myTurn]->GetName().c_str());
				Message.Add("�͂ǂ�����H");
				skill_item_gard.ResetSpot();
				ally[myTurn]->CancellGard();
			}
			skill_item_gard.Draw();
			if( skill_item_gard.Selected() ){
				if( skill_item_gard.SelectingString()=="�킴" ){
					tempframe=frame+1;
					allySelectScene = SKILL_SELECT;
				}
				else if(skill_item_gard.SelectingString()=="�ڂ�����"){
					ally[myTurn] -> Gard();
					FinishSelect();
					tempframe=frame+1;
				}
			}

			break;
		case SKILL_SELECT:
			Message.Call("�ǂ̂킴�������H");
			Message.StartNewLine();
			if(ally[myTurn]->SelectingSkill()!=NULL){
				Message.Add(ally[myTurn]->SelectingSkill() ->GetName().c_str());
				if(ally[myTurn]->SelectingSkill()->GetHurigana()!="()"){
					Message.Add(ally[myTurn]->SelectingSkill()->GetHurigana().c_str());
				}
				Message.StartNewLine();
				Message.Add(ally[myTurn]->SelectingSkill()->GetExplain().c_str());
				if(ally[myTurn]->NowBst()==TOUSYOU){
					Message.StartNewLine();
					Message.Add("�������i�Ƃ����傤�j�ɂ�肢�����̃X�L���������Ȃ�");
				}else if(ally[myTurn]->NowBst()==RESSYOU && ally[myTurn]->SelectingSkill()->GetSkillType()==P_ATK ){
					Message.StartNewLine();
					Message.Add("���􏝁i������傤�j�ɂ��g�o�����������傤�Ђ��Ă��܂�");
				}else if(ally[myTurn]->NowBst()==MAHUU && ally[myTurn]->SelectingSkill()->GetSkillType()!=P_ATK){
					Message.StartNewLine();
					Message.Add("���@���ӂ������Ă��邽�߂��̃X�L���͂����Ȃ�");
				}
			}

			if(ally[myTurn] -> SkillWasSelected() ){
				if(ally[myTurn]->SelectingSkill()!=NULL){
					allyUseSkill[myTurn] = ally[myTurn] -> SelectingSkill();
					allySelectScene = TARGET_SELECT;
					tempframe=frame+1;
				}
			}

			if(Key.Pushed(KEYNAME.BACK)){
				allySelectScene = SKILL_ITEM_GARD;
				ally[myTurn]->CancellGard();
				tempframe = frame+1;
			}

			
			
			break;

		case ESCAPE_SUCCESS:
			if(frame==tempframe){
				Message.Call("�ɂ����ꂽ");
			}
			break;
		case TARGET_SELECT:
			
			if(frame==tempframe){
				Message.Call("�ǂ̂����Ăɂ����H");
			}

			if(Key.Pushed(KEYNAME.BACK)){
				allySelectScene = SKILL_SELECT;
				allyUseSkill[myTurn] = &NOT_USED;
				tempframe=frame+1;
			}

			DecideAllySkillTarget();

			break;
		}

	}
}
	void CBattle::DecideAllySkillTarget(){

		if(frame==tempframe){
			nowTargetNum=1;
			while(!enemy[nowTargetNum].GetLive()){//�����Ă��鑊��������I�ɑI������
				nowTargetNum++;
				if(nowTargetNum>=5){
					break;
				}
			}
		}

		switch(allyUseSkill[myTurn]->GetTargetType()){
			case CSkill::ENEMY:
				DrawEnemyTargetIcon(nowTargetNum);
				SelectEnemy();
				if(Key.Pushed(KEYNAME.ENTER)){
					allySkillTarget[myTurn] = (SkillTarget)(nowTargetNum-1);
					FinishSelect();
				}
				break;
			case CSkill::ENEMY_ALL:
				for(int i=1;i<=firstEnemyNum;i++){
					if(enemy[i].GetLive()){
						DrawEnemyTargetIcon(i);
					}
				}
				if(Key.Pushed(KEYNAME.ENTER)){
					allySkillTarget[myTurn] = ENEMY_ALL_ST;
					FinishSelect();
				}
				break;
			case CSkill::ALLY:
				if(frame==tempframe){
					nowTargetNum=0;
				}
				DrawFormatString(0,0,YELLOW,"%d",nowTargetNum);
				NumSelect_LR(&nowTargetNum,0,1);
				DrawAllyTargetIcon(nowTargetNum);
				if(Key.Pushed(KEYNAME.ENTER)){
					allySkillTarget[myTurn] = (SkillTarget)(nowTargetNum+6);
					FinishSelect();
				}
				break;
			case CSkill::ALLY_ALL:
				DrawAllyTargetIcon(0);
				DrawAllyTargetIcon(1);
				if(Key.Pushed(KEYNAME.ENTER)){
					allySkillTarget[myTurn] = ALLY_ALL_ST;
					FinishSelect();
				}
				break;
		}

	}
		void CBattle::SelectEnemy(){
			DrawFormatString(0,0,RED,"%d",nowTargetNum);
			if(Key.Pushed(KEYNAME.RIGHT)){
				nowTargetNum++;
				if(nowTargetNum>firstEnemyNum){
					nowTargetNum=1;
				}
				while(enemy[nowTargetNum].GetLive()==false){
					nowTargetNum++;
					if(nowTargetNum>firstEnemyNum){
						nowTargetNum=1;
					}
				}	
			}
			if(Key.Pushed(KEYNAME.LEFT)){
				nowTargetNum--;
				if(nowTargetNum<1){
					nowTargetNum = firstEnemyNum;
				}
				while(enemy[nowTargetNum].GetLive()==false){
					nowTargetNum--;
					if(nowTargetNum<1){
						nowTargetNum=firstEnemyNum;
					}
				}
			}

		}
		void CBattle::DrawEnemyTargetIcon(int _targetNum){
			switch(firstEnemyNum){
			case 1:
				DrawGraph( 265+(2)*76 , 135 , targetPic , true );
				break;
			case 2:
				DrawGraph( 265+(_targetNum)*76 , 135 , targetPic , true );
				break;
			case 3:
				DrawGraph( 265+(_targetNum)*76 , 135 , targetPic , true );
				break;
			case 4:
				DrawGraph( 265+(_targetNum-1)*76 , 135 , targetPic , true );
				break;
			case 5:
				DrawGraph( 265+(_targetNum-1)*76 , 135 , targetPic , true );				
				break;
			}
		}
		void CBattle::DrawAllyTargetIcon(int _position){
			if(_position==0){
				DrawGraph(262,276,targetPic,true);
			}else{
				DrawGraph(522,276,targetPic,true);
			}
		}
		void CBattle::FinishSelect(){
			tempframe=frame+1;
			allySelectScene = SKILL_ITEM_GARD;
			battleScene=MOVEMENT_INFULUENCE;
		}

	void CBattle::Escape(){
	
	bool success;
	if( frame==tempframe && Escapable() ){
		Message.Call("�ɂ�������");
		success = true;
	}else{
		Message.Call("�ɂ����Ȃ�����");
		success = false;
	}

	if( frame - tempframe > 30 || Key.Pushed(KEYNAME.ENTER)){
		if(success){
			tempframe=frame+1;
			allySelectScene = ESCAPE_SUCCESS;
		}else{
			tempframe=frame+1;
			allySelectScene = SKILL_ITEM_GARD;
		}
	}

}
		bool CBattle::Escapable(){
			int per=0;
			int enemyAverage=0;
			int allyAverage=0;

			for( int i=1;i<=enemyNum;i++ ){
				enemyAverage += enemy[i].RealParameter(SPEED);
			}
			enemyAverage /= enemyNum;
			
			for(int i=0;i<2;i++){
				allyAverage += ally[i]->RealParameter(SPEED);
			}
			allyAverage /= 2;

			if(enemyAverage > allyAverage+50){
				per = 0;
			}
			else if( enemyAverage > allyAverage ){
				per = 30 - enemyAverage + allyAverage;
			}
			else if( enemyAverage < allyAverage ){
				per = 70 - enemyAverage + allyAverage;
			}
			else if(enemyAverage < allyAverage-50 ){
				per = 100;
			}

			int rand=GetRand(100);

			if( rand > per ){
				return true;
			}else{
				return false;
			}

		}

void CBattle::DecideEnemy(int _num){
	if(enemy[_num].GetLive()){
		enemyUseSkill[_num] = enemy[_num].UseSkill();
	}
	DecideEnemySkillTarget(_num);
}
	void CBattle::DecideEnemySkillTarget(int _num){
		if(enemy[_num].GetLive()){
			switch(enemyUseSkill[_num]->GetTargetType()){
			case CSkill::ALLY://�G�ɂƂ��Ă�Ally�͓G
				enemySkillTarget[_num] = (SkillTarget)GetRand(firstEnemyNum-1);
				while(enemy[enemySkillTarget[_num]+1].GetLive()==false){
					enemySkillTarget[_num] = (SkillTarget)GetRand(firstEnemyNum-1);
				}
				break;
			case CSkill::ALLY_ALL:
				enemySkillTarget[_num] = ENEMY_ALL_ST;
				break;
			case CSkill::ENEMY:
				enemySkillTarget[_num] = (SkillTarget)(GetRand(1)+6); 
				break;
			case CSkill::ENEMY_ALL:
				enemySkillTarget[_num] = ALLY_ALL_ST;
				break;
			}
		}
	}

void CBattle::Battle(){
	
	static bool first=true;
	if(first){
		for(int i=1;i<=firstEnemyNum;i++){
			enemy[i].TurnInit();
		}
		ResetAllySelect();
		JudgeOrder();
		orderMax=2+enemyNum;
		movingNum=0;
		first=false;
		
		battleScene=BST_EFFECT;
		tempframe=frame;
	}
	static bool f=false;
	int n=GetRand(2)*100;
	switch(battleScene){
	case BST_EFFECT:
		if(frame==tempframe){
			f=BstEffect();
			if(order[movingNum]<2){
				myTurn = (MyTurn)order[movingNum];
			}
		}
		if(f==true){
			BstDrawDamage();
			if(frame-tempframe>60){
				tempframe=frame+1;
				battleScene=DECIDE_MOVEMENT;
				f=true;//��Ⴢ̏����p
			}
		}else{
			tempframe=frame+1;
			battleScene=DECIDE_MOVEMENT;
			f=true;//��Ⴢ̏����p
		}
		break;
	case DECIDE_MOVEMENT:
		if(order[movingNum]<2){//�������s������Ԃ̂Ƃ�
			if(ally[order[movingNum]]->NowBst()==NEMURI){
				battleScene = MOVEMENT_INFULUENCE;
				skillSuccessFlag=false;
			}
			else if(ally[order[movingNum]]->NowBst()==MAHI && f==true){
				if(n*( BuffPercent( ally[order[movingNum]]->GetRank(M_GARD) ) ) < 100 ){
					battleScene = MOVEMENT_INFULUENCE;
					skillSuccessFlag=false;
					Message.StartNewLine();
					Message.Add("��Ⴡi�܂Ёj�ɂ�肤�����Ȃ�����");
				}else{
					f=false;
				}
			}
			else{
				DecideAlly();
			}
		}else{//�G���s������Ԃ̎�	
			if(enemy[order[movingNum]-1].NowBst()==NEMURI){
				skillSuccessFlag=false;
			}else if(enemy[order[movingNum]-1].NowBst()==MAHI && f==true){
				if(n*( BuffPercent( enemy[order[movingNum]-1].GetRank(M_GARD) ) ) <= 100){
					skillSuccessFlag=false;
					Message.StartNewLine();
					Message.Add("��Ⴡi�܂Ёj�ɂ�肤�����Ȃ�����");
				}else{
					DecideEnemy(order[movingNum]-1);
					tempframe=frame+1;
				}
			}
			else{
				DecideEnemy(order[movingNum]-1);
				tempframe=frame+1;
			}
			battleScene = MOVEMENT_INFULUENCE;
		}
		break;
	case MOVEMENT_INFULUENCE:
		if(frame==tempframe){
			MovementInfuluence();
		}
		if((frame < tempframe+30) && skillSuccessFlag==true){//�X�L���g�p�������A30�t���[�������_���[�W��\�� 
			if( order[movingNum] <= 1 ){//�s�������̂������̎�
				if( allyUseSkill[order[movingNum]] -> GetName() != "NotUsed"){
					if(
					   allyUseSkill[order[movingNum]] -> GetSkillType() == CSkill::MAJIC_ATK
					|| allyUseSkill[order[movingNum]] -> GetSkillType() == CSkill::PHYSIC_ATK
					) {
						DrawDamage(allySkillTarget[order[movingNum]]);
					}
				}
			}
			else{//�s�������̂��G�̎�
				if(enemyUseSkill[order[movingNum]-1] -> GetSkillType() == CSkill::MAJIC_ATK
				|| enemyUseSkill[order[movingNum]-1] -> GetSkillType() == CSkill::PHYSIC_ATK
					){ 
					DrawDamage(enemySkillTarget[order[movingNum]-1]);
				}
			}
		}
		else{//30�t���[���o�ߌ� �������̓X�L���s���̎�
			if(Key.Pushed(KEYNAME.ENTER)){
				battleScene=BST_EFFECT;
				movingNum++;
				tempframe = frame+1;
				enemyNum=firstEnemyNum;
				for(int i=1;i<=firstEnemyNum;i++){
					if(enemy[i].GetLive()==false){
						enemyNum--;
					}
				}
				if(enemyNum<=0){//�G�����Ȃ��Ȃ�����
					scene=RESULT;
					first=true;
				}
				if(movingNum >= orderMax){//�ꏄ�����烊�Z�b�g
					first=true;
				}else if(order[movingNum]>=2){//�����G�̍s������Ԃ̂Ƃ�
					while(!enemy[order[movingNum]-1].GetLive()){//����ł���G�̏��Ԃ��Ƃ΂�
						movingNum++;
						if(movingNum>=orderMax){//�ꏄ�����烊�Z�b�g
							first=true;
							break;
						}
						if(order[movingNum]<2){//�݂����̔ԂɂȂ�����break
							break;
						}
					}
				}
			}
		}
		break;
	}
	
}
	void CBattle::JudgeOrder(){

	int temp=0;
	bool end[7]={};
	for(int i=0;i<2+enemyNum;i++){
		for(int j=0;j<2+firstEnemyNum;j++){
			if(!end[j]){
				if(j<2){	
					if(temp < ally[j]->RealParameter(SPEED)){
						temp = ally[j]->RealParameter(SPEED);
						order[i]=(Order)j;
					}else if(temp==ally[j]->RealParameter(SPEED)){
						bool f=GetRand(1);
						if(f){
							temp=ally[j]->RealParameter(SPEED);
							order[i]=(Order)j;
						}
					}	
				}else{
					if(enemy[j-1].GetLive()){
						if(temp<enemy[j-1].RealParameter(SPEED)){
							temp=enemy[j-1].RealParameter(SPEED);
							order[i]=(Order)j;
						}else if(temp==enemy[j-1].RealParameter(SPEED)){
							bool f=GetRand(1);
							if(f){
								temp=enemy[j-1].RealParameter(SPEED);
								order[i]=(Order)j;
							}
						}
					}
				}
				
			}
		}
		end[order[i]]=true;
		temp=0;
	}
}
	bool CBattle::BstEffect(){
		if(order[movingNum]<2){//�������s������Ԃ̂Ƃ�
			if(ally[order[movingNum]]->NowBst()==NO_BST){//��Ԉُ�łȂ��Ȃ烁�b�Z�[�W��\�����������ɏI��
				return false;
			}
			if(ally[order[movingNum]]->BstRecover()){//���̃^�[���ɏ�Ԉُ킪������
				Message.Call(ally[order[movingNum]]->GetName().c_str());
				Message.Add(bstRecoverMessage[ally[order[movingNum]]->RecoveredBst()].c_str());
				return true;
			}else{//���̃^�[���ɏ�Ԉُ킪����Ȃ�����
				Message.Call(ally[order[movingNum]]->GetName().c_str());
				Message.Add(bstEffectMessage[ally[order[movingNum]]->NowBst()].c_str());
				ally[order[movingNum]]->BstEffect();
				return true;
			}
		}else{//�G���s������Ԃ̎�	
			if(enemy[order[movingNum]-1].NowBst()==NO_BST){//��Ԉُ�łȂ��Ȃ烁�b�Z�[�W��\�����������ɏI��
				return false;
			}
			if(enemy[order[movingNum]-1].BstRecover()){//���̃^�[���ɏ�Ԉُ킪������
				Message.Call(enemy[order[movingNum]-1].GetName().c_str());
				Message.Add(bstRecoverMessage[enemy[order[movingNum]-1].RecoveredBst()].c_str());
				return true;
			}else{//���̃^�[���ɏ�Ԉُ킪����Ȃ�����
				Message.Call(enemy[order[movingNum]-1].GetName().c_str());
				Message.Add(bstEffectMessage[enemy[order[movingNum]-1].NowBst()].c_str());
				enemy[order[movingNum]-1].BstEffect();
				return true;
			}
		}
	}
		void CBattle::BstDrawDamage(){
			if(order[movingNum]<2){//�������s������Ԃ̂Ƃ�
				ally[order[movingNum]]->DrawBstDamage();	
			}else{//�G���s������Ԃ̎�
				enemy[order[movingNum]-1].DrawBstDamage();
			}
		}
	void CBattle::MovementInfuluence(){
		#define ALLY_SKILL allyUseSkill[order[movingNum]]
		#define ENEMY_SKILL enemyUseSkill[order[movingNum]-1]

		if(order[movingNum]<2){//�������s������Ԃ̂Ƃ�
			if(ALLY_SKILL->GetName()=="NotUsed"){//�X�L�����g���Ă��Ȃ��Ƃ�
				if(ally[order[movingNum]]->Defending()){//�h�䒆�Ȃ�
					Message.Call(ally[order[movingNum]]->GetName().c_str());
					Message.Add("�݂͂��܂����Ă���");
				}
			}else{//�X�L�����g���Ă���Ƃ�
				ally[order[movingNum]]->ConsumeP(ALLY_SKILL);
				SkillInfuluence(ALLY_SKILL,ally[order[movingNum]]);
			}
		}else{//�G���s������Ԃ̎�
			if(enemy[order[movingNum]-1].GetLive()==true){
				SkillInfuluence(ENEMY_SKILL,&enemy[order[movingNum]-1]);
			}	
		}

	}				
		void CBattle::SkillInfuluence(CSkill* _skill,CAlly* _ally){	
			#define A_ST allySkillTarget[order[movingNum]]//�����X�L���̑Ώ�
			SkillUseMessage(ALLY_SKILL,ally[order[movingNum]]->GetName());
			skillSuccessFlag=true;
			switch(_skill->GetSkillType()){
				case CSkill::PHYSIC_ATK:
					GiveDamage(_skill,_ally,&enemy[A_ST+1]);
					break;
				case CSkill::MAJIC_ATK:
					GiveDamage(_skill,_ally,&enemy[A_ST+1]);
					break;
				case CSkill::BUFF:
					GiveBuff(_skill,A_ST);
					GiveBst(_skill,A_ST);
					break;
				case CSkill::RECOVER:
					GiveRecover(_skill,_ally,A_ST);
					GiveBst(_skill,A_ST);
					break;
				case CSkill::BAD_STATUS:
					GiveBst(_skill,A_ST);
					break;
				case CSkill::BST_RECOVER:
					GiveBstRecover(_skill,A_ST);
					break;

			}
		}
		void CBattle::SkillInfuluence(CSkill* _skill,CEnemy* _enemy){
			#define E_ST enemySkillTarget[order[movingNum]-1]
			switch(_skill->GetSkillType()){
				case CSkill::PHYSIC_ATK:
					if(_enemy->NowSkillUseAble()){
						_enemy->ConsumeP();
						SkillUseMessage(ENEMY_SKILL,_enemy->GetName());
						GiveDamage(_skill , _enemy , ally[E_ST-6]);
						skillSuccessFlag=true;
					}else{
						SkillUseFailedMessage(ENEMY_SKILL,_enemy);
						skillSuccessFlag=false;
					}
					break;
				case CSkill::MAJIC_ATK:
					if(_enemy->NowSkillUseAble()){
						_enemy->ConsumeP();
						SkillUseMessage(ENEMY_SKILL,_enemy->GetName());
						GiveDamage(_skill , _enemy , ally[E_ST-6]);
						skillSuccessFlag=true;
					}else{
						SkillUseFailedMessage(ENEMY_SKILL,_enemy);
						skillSuccessFlag=false;
					}
					break;
				case CSkill::BUFF:
					if(_enemy->NowSkillUseAble()){
						_enemy->ConsumeP();
						SkillUseMessage(ENEMY_SKILL,_enemy->GetName());
						GiveBuff(_skill,E_ST);
						GiveBst(_skill,E_ST);
						skillSuccessFlag=true;
					}else{
						SkillUseFailedMessage(ENEMY_SKILL,_enemy);
						skillSuccessFlag=false;
					}
					break;
				case CSkill::RECOVER:
					if(_enemy->NowSkillUseAble()){
						_enemy->ConsumeP();
						SkillUseMessage(ENEMY_SKILL,_enemy->GetName());
						GiveRecover(_skill,_enemy,E_ST);
						GiveBst(_skill,E_ST);
						skillSuccessFlag=true;
					}else{
						SkillUseFailedMessage(ENEMY_SKILL,_enemy);
						skillSuccessFlag=false;
					}
					break;
				case CSkill::BAD_STATUS:
					if(_enemy->NowSkillUseAble()){
						_enemy->ConsumeP();
						SkillUseMessage(ENEMY_SKILL,_enemy->GetName());
						GiveBst(_skill,E_ST);
						skillSuccessFlag=true;
					}else{
						SkillUseFailedMessage(ENEMY_SKILL,_enemy);
						skillSuccessFlag=false;
					}
					break;
				case CSkill::BST_RECOVER:
					if(_enemy->NowSkillUseAble()){
						_enemy->ConsumeP();
						SkillUseMessage(ENEMY_SKILL,_enemy->GetName());
						GiveBstRecover(_skill,E_ST);
						skillSuccessFlag=true;
					}else{
						SkillUseFailedMessage(ENEMY_SKILL,_enemy);
						skillSuccessFlag=false;
					}
					break;
			}
		}
			void CBattle::SkillUseMessage(CSkill* _skill,std::string _userName){
				if( _skill->GetSkillType() == CSkill::SkillType::PHYSIC_ATK ){
					Message.Call(_userName.c_str());
					Message.Add("��");
					Message.Add(_skill->GetName().c_str());
				}else{
					Message.Call(_userName.c_str());
					Message.Add("��");
					Message.Add(_skill->GetName().c_str());
					Message.Add("���ƂȂ���");
				}
			}	
			void CBattle::SkillUseFailedMessage(CSkill* _skill,CEnemy* _enemy){
				if( _skill->GetSkillType() == CSkill::SkillType::PHYSIC_ATK ){
					if(_skill->UseSuccess(_enemy->GetHP()) ){
						Message.Call(_enemy->GetName().c_str());
						Message.Add("�͓����i�Ƃ����傤�j�ɂ��");
						Message.Add(_skill->GetName().c_str());
						Message.Add("�������Ȃ�");
					}else{
						Message.Call(_enemy->GetName().c_str());
						Message.Add("��");
						Message.Add(_skill->GetName().c_str());
						Message.Add("��������݂����A�g�o������Ȃ�����");
					}
				}else{
					if(_skill->UseSuccess(_enemy->GetSP()) ){
						Message.Call(_enemy->GetName().c_str());
						Message.Add("�͖����i�܂ӂ��j�ɂ��");
						Message.Add(_skill->GetName().c_str());
						Message.Add("�������Ȃ�");
					}else{
						Message.Call(_enemy->GetName().c_str());
						Message.Add("��");
						Message.Add(_skill->GetName().c_str());
						Message.Add("���ƂȂ��悤�Ƃ������A�l�o������Ȃ�����");
					}
				}
			}
			void CBattle::GiveDamage(CSkill* _skill,CAlly* _ally,CEnemy* _enemy){
				if( allySkillTarget[order[movingNum]] < 5 ){//�G�P�̂��Ώۂ̎�
					if(_skill->GetSkillType()==CSkill::SkillType::PHYSIC_ATK){
						if(_enemy->AtackGiven(_skill)){
							_enemy->GiveDamage(_skill ,_ally->RealParameter(P_ATK) );
							DamageMessage(_enemy->GetName(),_enemy->GetDamage());
							if(_enemy->GiveBst(_skill)==CSkill::SkillResult::SUCCESSED){
								BstMessage(_enemy->GetName().c_str(),_skill);
							}
						}else{
							SkillAvoidedMessage(_enemy->GetName().c_str());
						}
					}else{
						if(_enemy->AtackGiven(_skill)){
							_enemy->GiveDamage(_skill ,_ally->RealParameter(M_ATK) );
							DamageMessage(_enemy->GetName(),_enemy->GetDamage());
							if(_enemy->GiveBst(_skill)==CSkill::SkillResult::SUCCESSED){
								BstMessage(_enemy->GetName().c_str(),_skill);
							}
						}
						else{
							SkillAvoidedMessage(_enemy->GetName().c_str());
						}
					}
				}else{//�G�S�̂��Ώۂ̎�
					for(int i=1;i<=firstEnemyNum;i++){
						if(_skill->GetSkillType()==CSkill::SkillType::PHYSIC_ATK){
							if(enemy[i].GetLive() && enemy[i].AtackGiven(_skill)){
								enemy[i].GiveDamage(_skill , _ally->RealParameter(P_ATK) );
								DamageMessage(enemy[i].GetName(),enemy[i].GetDamage());
								if(enemy[i].GiveBst(_skill)==CSkill::SkillResult::SUCCESSED){
									BstMessage(enemy[i].GetName().c_str(),_skill);
								}
							}
						}else{
							if(enemy[i].GetLive() && enemy[i].AtackGiven(_skill)){
								enemy[i].GiveDamage(_skill , _ally->RealParameter(M_ATK) );
								DamageMessage(enemy[i].GetName(),enemy[i].GetDamage());
								if(enemy[i].GiveBst(_skill)==CSkill::SkillResult::SUCCESSED){
									BstMessage(enemy[i].GetName().c_str(),_skill);
								}
							}
						}
					}
				}
			}
			void CBattle::GiveDamage(CSkill* _skill,CEnemy* _enemy,CAlly* _ally){
				if( enemySkillTarget[order[movingNum]-1] == 6 || enemySkillTarget[order[movingNum]-1] == 7 ){
					if(_skill->GetSkillType()==CSkill::SkillType::PHYSIC_ATK){
						if(_ally->AtackGiven(_skill)){
							_ally -> GiveDamage( _skill ,  _enemy->RealParameter(P_ATK));
							DamageMessage( _ally -> GetName() , _ally -> GetDamage() );
							if(_ally->GiveBst(_skill)==CSkill::SkillResult::SUCCESSED){
								BstMessage(_ally->GetName().c_str(),_skill);
							}
						}else{
							SkillAvoidedMessage(_ally-> GetName().c_str() );
						}
					}else{
						if(_ally -> AtackGiven(_skill) ){
							_ally -> GiveDamage( _skill ,  _enemy->RealParameter(M_ATK));
							DamageMessage( _ally -> GetName() , _ally -> GetDamage() );
							if(_ally->GiveBst(_skill)==CSkill::SkillResult::SUCCESSED){
								BstMessage(_ally->GetName().c_str(),_skill);
							}
						}else{
							SkillAvoidedMessage(_ally ->GetName().c_str());
						}
					}
				}
				else{
					if(_skill->GetSkillType()==CSkill::SkillType::PHYSIC_ATK){
						for(int i=0;i<2;i++){
							if(ally[i]->AtackGiven(_skill)){
								ally[i] -> GiveDamage( _skill ,  _enemy->RealParameter(P_ATK));
								DamageMessage( ally[i] -> GetName() , ally[i] -> GetDamage() );
								if(ally[i]->GiveBst(_skill)==CSkill::SkillResult::SUCCESSED){
									BstMessage(ally[i]->GetName().c_str(),_skill);
								}
							}else{
								SkillAvoidedMessage(ally[i] ->GetName().c_str());
							}
						}
					}
					else{
						for(int i=0;i<2;i++){
							if(ally[i]->AtackGiven(_skill)){
								ally[i] -> GiveDamage( _skill ,  _enemy->RealParameter(M_ATK));
								DamageMessage( ally[i] -> GetName() , ally[i] -> GetDamage() );
								if(ally[i]->GiveBst(_skill)==CSkill::SkillResult::SUCCESSED){
									BstMessage(ally[i]->GetName().c_str(),_skill);
								}
							}else{
								SkillAvoidedMessage(ally[i] ->GetName().c_str());
							}
						}
					}

				}
				
			}
				void CBattle::DamageMessage(std::string _targetName,int _damage){
					Message.StartNewLine();
					Message.Add(_targetName.c_str());
					Message.Add("��");
					Message.Add( std::to_string((long long)_damage).c_str() );
					Message.Add("�̃_���[�W");
				}			
			void CBattle::GiveBuff(CSkill* _skill,SkillTarget _st){
				if(_st < 5){//�G���Ώۂ̂Ƃ�
					switch(enemy[_st+1].GiveBuff(_skill->GetAmount(),(Parameter)_skill->GetBuffType())){//BuffType��Parameter�ƌ݊���������
					case CSkill::SUCCESSED:
						BuffMessage( enemy[_st+1].GetName().c_str(),_skill );
						break;
					case CSkill::FAILED:
						BuffFailedMessage( enemy[_st+1].GetName().c_str(),_skill);
						break;
					}
				}else if(_st==5){//�G�S�̂��Ώۂ̂Ƃ�
					for(int i=1;i<=firstEnemyNum;i++){
						if(enemy[i].GetLive()){
							switch(enemy[i].GiveBuff(_skill->GetAmount(),(Parameter)_skill->GetBuffType())){
							case CSkill::SUCCESSED:
								BuffMessage( enemy[_st+1].GetName().c_str(),_skill );
								break;
							case CSkill::FAILED:
								BuffFailedMessage( enemy[_st+1].GetName().c_str(),_skill);
								break;
							}
						}
					}
					BuffMessage("�Ă����񂽂�",_skill);
				}else if(_st < 8){//�������Ώۂ̎�
					switch(ally[_st-6]->GiveBuff(_skill->GetAmount(),(Parameter)_skill->GetBuffType())){
					case CSkill::SUCCESSED:
						BuffMessage(ally[_st-6]->GetName().c_str(),_skill);
						break;
					case CSkill::FAILED:
						BuffFailedMessage(ally[_st-6]->GetName().c_str(),_skill);
						break;
					}
					
				}else{//�����S�̂��Ώۂ̎�
					for(int i=0;i<2;i++){
						switch(ally[i]->GiveBuff(_skill->GetAmount(),(Parameter)_skill->GetBuffType())){
						case CSkill::SUCCESSED:
							BuffMessage(ally[i]->GetName().c_str(),_skill);
							break;
						case CSkill::FAILED:
							BuffMessage(ally[i]->GetName().c_str(),_skill);
							break;
						}
					}
					
				}
			}
				void CBattle::BuffMessage(const char* _targetName , CSkill* _skill){	
					Message.StartNewLine();
					Message.Add( _targetName );
					Message.Add( _skill->Message().c_str() );
				}
				void CBattle::BuffFailedMessage(const char* _targetName ,CSkill* _skill){
					Message.StartNewLine();
					Message.Add(_targetName);
					Message.Add("��");
					Message.Add(parameterS[_skill->GetBuffType()].c_str());
					Message.Add("�͂��ꂢ���傤������Ȃ�");
				}
			void CBattle::GiveRecover(CSkill* _skill,CEnemy* _user,SkillTarget _st){
				if(_st < 5){//�G���Ώۂ̂Ƃ�
					enemy[_st+1].GiveRecover(_skill,_user->RealParameter(M_ATK));
					RecoverMessage( enemy[_st+1].GetName().c_str(),_skill );
				}else if(_st==5){//�G�S�̂��Ώۂ̂Ƃ�
					for(int i=1;i<=firstEnemyNum;i++){
						if(enemy[i].GetLive()){
							enemy[i].GiveRecover(_skill,_user->RealParameter(M_ATK));
						}
					}
					RecoverMessage("�Ă����񂽂�",_skill );
				}else if(_st < 8){//�������Ώۂ̎�
					ally[_st-6]->GiveRecover(_skill,_user->RealParameter(M_ATK));
					RecoverMessage( ally[_st-6]->GetName().c_str(),_skill );
				}else{//�����S�̂��Ώۂ̎�
					for(int i=0;i<2;i++){
						ally[i]->GiveRecover(_skill,_user->RealParameter(M_ATK));
					}
					RecoverMessage("�݂������񂽂�",_skill );
				}
			}
			void CBattle::GiveRecover(CSkill* _skill,CAlly* _user,SkillTarget _st){
				if(_st < 5){//�G���Ώۂ̂Ƃ�
					enemy[_st+1].GiveRecover(_skill,_user->RealParameter(M_ATK));
					RecoverMessage( enemy[_st+1].GetName().c_str(),_skill );
				}else if(_st==5){//�G�S�̂��Ώۂ̂Ƃ�
					for(int i=1;i<=firstEnemyNum;i++){
						if(enemy[i].GetLive()){
							enemy[i].GiveRecover(_skill,_user->RealParameter(M_ATK));
						}
					}
					RecoverMessage("�Ă����񂽂�",_skill );
				}else if(_st < 8){//�������Ώۂ̎�
					ally[_st-6]->GiveRecover(_skill,_user->RealParameter(M_ATK));
					RecoverMessage( ally[_st-6]->GetName().c_str(),_skill );
				}else{//�����S�̂��Ώۂ̎�
					for(int i=0;i<2;i++){
						ally[i]->GiveRecover(_skill,_user->RealParameter(M_ATK));
					}
					RecoverMessage("�݂������񂽂�",_skill );
				}
			}
				void CBattle::RecoverMessage(const char* _target,CSkill* _skill){
					Message.StartNewLine();
					Message.Add(_target);
					Message.Add(_skill->Message().c_str());
				}
			void CBattle::GiveBst(CSkill* _skill,SkillTarget _st){
				if(_st < 5){//�G���Ώۂ̂Ƃ�
					switch(enemy[_st+1].GiveBst(_skill)){
					case CSkill::SUCCESSED:
						BstMessage(enemy[_st+1].GetName().c_str(),_skill);
						break;
					case CSkill::FAILED:
						if(_skill->GetSkillType()==CSkill::SkillType::BAD_STATUS){//��Ԉُ�Z�ȊO�̋Z�̒ǉ����ʂƂ��Ă̔��莞�ɂ͎��s���Ă����b�Z�[�W���o���Ȃ�
							SkillFailedMessage(enemy[_st+1].GetName().c_str());
						}
						break;
					case CSkill::AVOIDED:
						if(_skill->GetSkillType()==CSkill::SkillType::BAD_STATUS){//����
							SkillAvoidedMessage(enemy[_st+1].GetName().c_str());
						}
						break;
					}
				}
				else if(_st==5){//�G�S�̂��Ώۂ̂Ƃ�
					for(int i=1;i<=firstEnemyNum;i++){
						if(enemy[i].GetLive()){
							switch(enemy[i].GiveBst(_skill)){
								case CSkill::SUCCESSED:
									BstMessage(enemy[i].GetName().c_str(),_skill);
									break;
								case CSkill::FAILED:
									if(_skill->GetSkillType()==CSkill::SkillType::BAD_STATUS){//��Ԉُ�Z�ȊO�̋Z�̒ǉ����ʂƂ��Ă̔��莞�ɂ͎��s���Ă����b�Z�[�W���o���Ȃ�
										SkillFailedMessage(enemy[i].GetName().c_str());
									}
									break;
								case CSkill::AVOIDED:
									if(_skill->GetSkillType()==CSkill::SkillType::BAD_STATUS){//����
										SkillAvoidedMessage(enemy[i].GetName().c_str());
									}
									break;
							}
						}
					}
				}
				else if(_st < 8){//�������Ώۂ̎�
					switch(ally[_st-6]->GiveBst(_skill)){
						case CSkill::SUCCESSED:
							BstMessage(ally[_st-6]->GetName().c_str(),_skill);
							break;
						case CSkill::FAILED:
							if(_skill->GetSkillType()==CSkill::SkillType::BAD_STATUS){//��Ԉُ�Z�ȊO�̋Z�̒ǉ����ʂƂ��Ă̔��莞�ɂ͎��s���Ă����b�Z�[�W���o���Ȃ�
								SkillFailedMessage(ally[_st-6]->GetName().c_str());
							}
							break;
						case CSkill::AVOIDED:
							if(_skill->GetSkillType()==CSkill::SkillType::BAD_STATUS){//����
								SkillAvoidedMessage(ally[_st-6]->GetName().c_str());
							}
							break;
					}
				}
				else{//�����S�̂��Ώۂ̎�
					for(int i=0;i<2;i++){
						switch(ally[i]->GiveBst(_skill)){
							case CSkill::SUCCESSED:
								BstMessage(ally[i]->GetName().c_str(),_skill);
								break;
							case CSkill::FAILED:
								if(_skill->GetSkillType()==CSkill::SkillType::BAD_STATUS){//��Ԉُ�Z�ȊO�̋Z�̒ǉ����ʂƂ��Ă̔��莞�ɂ͎��s���Ă����b�Z�[�W���o���Ȃ�
									SkillFailedMessage(ally[i]->GetName().c_str());
								}
								break;
							case CSkill::AVOIDED:
								if(_skill->GetSkillType()==CSkill::SkillType::BAD_STATUS){//����
									SkillAvoidedMessage(ally[i]->GetName().c_str());
								}
								break;
						}
					}
				}
			}
				void CBattle::BstMessage(const char* _target,CSkill* _skill){
					Message.StartNewLine();
					Message.Add(_target);
					Message.Add(bstMessage[_skill->GetBstType()].c_str());
				}
			void CBattle::GiveBstRecover(CSkill* _skill,SkillTarget _st){
				if(_st < 5){//�G���Ώۂ̂Ƃ�
					switch(enemy[_st+1].GiveBstRecover(_skill)){
					case CSkill::SUCCESSED:
						BstRecoverMessage(enemy[_st+1].GetName().c_str(),enemy[_st+1].RecoveredBst(),_skill);
						break;
					case CSkill::FAILED:
						SkillFailedMessage(enemy[_st+1].GetName().c_str());
						break;
					}
				}else if(_st==5){//�G�S�̂��Ώۂ̂Ƃ�
					for(int i=1;i<=firstEnemyNum;i++){
						if(enemy[i].GetLive()){
							switch(enemy[i].GiveBstRecover(_skill)){
							case CSkill::SUCCESSED:
								BstRecoverMessage(enemy[i].GetName().c_str(),enemy[i].RecoveredBst(),_skill);
								break;
							case CSkill::FAILED:
								SkillFailedMessage(enemy[i].GetName().c_str());
								break;
							}
						}
					}
				}else if(_st<8){//�������Ώۂ̎�
					switch(ally[_st-6]->GiveBstRecover(_skill)){
						case CSkill::SUCCESSED:
							BstRecoverMessage(ally[_st-6]->GetName().c_str(),ally[_st-6]->RecoveredBst(),_skill);
							break;
						case CSkill::FAILED:
							SkillFailedMessage(ally[_st-6]->GetName().c_str());
							break;
					}
				}else {//�����S�̂��Ώۂ̎�
					for(int i=0;i<2;i++){
						switch(ally[i]->GiveBstRecover(_skill)){
							case CSkill::SUCCESSED:
								BstRecoverMessage(ally[i]->GetName().c_str(),ally[i]->RecoveredBst(),_skill);
								break;
							case CSkill::FAILED:
								SkillFailedMessage(ally[i]->GetName().c_str());								
								break;
						}
					}
				}
			}
				void CBattle::BstRecoverMessage(const char* _targetName,BadStatus _recoveredBst,CSkill* _skill){
					Message.StartNewLine();
					Message.Add(_targetName);
					Message.Add(bstRecoverMessage[_recoveredBst].c_str());
				}
			void CBattle::SkillFailedMessage(const char* _targetName){
				Message.StartNewLine();
				Message.Add(_targetName);
				Message.Add("�ɂ͂��܂����܂�Ȃ�����");
			}
			void CBattle::SkillAvoidedMessage(const char* _targetName){
				Message.StartNewLine();
				Message.Add(_targetName);
				Message.Add("�ɂ͂�����Ȃ�����");
			}
	void CBattle::DrawDamage(SkillTarget _target){		
		if(_target < ENEMY_ALL_ST){
			enemy[_target+1].DrawDamage();
		}else if(_target==ENEMY_ALL_ST){
			for(int i=1;i<=firstEnemyNum;i++){
				enemy[i].DrawDamage();
			}
		}else if(_target < ALLY_ALL_ST){
			ally[_target-6]->DrawDamage();
		}else{
			for(int i=0;i<2;i++){
				ally[i]->DrawDamage();
			}
		}
	}
	void CBattle::ResetAllySelect(){
		allySelectScene=SKILL_ITEM_GARD;
		for(int i=0;i<2;i++){
			allyUseSkill[i] = &NOT_USED;
		}
	}