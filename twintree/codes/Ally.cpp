#include"Ally.h"
/////////////////////CAlly/////////////////////////////////

CAlly::CAlly(const char* _name ,int _hp,int _sp,int _pA,int _pG,int _mA,int _mG,int _speed)
	:name(_name),
	 defensive(false),
	 hpMax(_hp),
	 hp(_hp),
	 spMax(_sp),
	 sp(_sp),
	 level(1),exp(0),
	 damage(0)
{
	status[P_ATK]=_pA;
	status[P_GARD]=_pG;
	status[M_ATK]=_mA;
	status[M_GARD]=_mG;
	status[SPEED]=_speed;
	for(int i=P_ATK;i<=SPEED;i++){
		rank[i]=0;
	}
	for(int i=0;i<Parameter::SPEED+1;i++){
		for(int j=0;j<2;j++){
			statusGraph[i][j]=0;
		}
	}
	nowBst=NO_BST;
	recoveredBst=NO_BST;
	bstTurn=0;
}
/////////////パブリック関数///////////////

void CAlly::Init(){
	hp=hpMax;
	sp=spMax;
	Skills.Init();
}
void CAlly::BattleInit(){
	defensive=false;
	for(int i=P_ATK;i<=SPEED;i++){
		rank[i]=0;
	}
	nowBst=NO_BST;
	recoveredBst=NO_BST;
	bstTurn=0;
}

void CAlly::AddSkill(CSkill* _newSkill){
	Skills.LearnNewSkill(_newSkill);
}
CSkill* CAlly::SelectingSkill(){
	return Skills.Selecting();
}
int CAlly::HavingSkillNum(){
	return Skills.GetSkillNum();
}
bool CAlly::SkillWasSelected(){
	if(Skills.Selected(hp,sp,nowBst)){
		if(Skills.Selecting()->GetValid() && Skills.SelectingUseAble()){
			return true;
		}
	}
	return false;
}

void CAlly::ConsumeP(CSkill* _usedSkill){
	if(_usedSkill->GetSkillType() == CSkill::PHYSIC_ATK){
		if(nowBst==RESSYOU){
			hp -= _usedSkill->GetConsumePoint()*5;
		}else{
			hp -= _usedSkill->GetConsumePoint();
		}
	}else{
		sp -= _usedSkill->GetConsumePoint();
	}
}

void CAlly::Gard(){
	defensive = true;
}
void CAlly::CancellGard(){
	defensive=false;
}

std::string CAlly::GetName(){
	return name;
}

int CAlly::GetRank(Parameter _para){
	return rank[_para];
}
int CAlly::GetStatus(Parameter _para){
	return status[_para];
}
int CAlly::RealParameter(Parameter _para){
	switch(nowBst){
	case BadStatus::YAKEDO:
		if(_para==P_ATK){
			return status[_para]*BuffPercent(rank[_para])*2/3;
		}
		break;
	case BadStatus::RESSYOU:
		if(_para==P_ATK){
			return status[_para]*BuffPercent(rank[_para])*2/3;
		}
		break;
	case BadStatus::MAHI:
		if(_para==SPEED){
			return status[_para]*BuffPercent(rank[_para])*1/3;
		}
		if(_para==M_GARD){
			return status[_para]*BuffPercent(rank[_para])*2/3;
		}
		break;
	case BadStatus::NEMURI:
		if(_para==P_GARD){
			return status[_para]*BuffPercent(rank[_para])*2/3;
		}
		break;
	}
	return status[_para]*BuffPercent(rank[_para]);
}

bool CAlly::Defending(){
	return defensive;
}

int CAlly::GetDamage(){
	return damage;
}

void CAlly::SkillCopy(CSkillManager* _skills){
	Skills=*_skills;
}

CSkill::SkillResult CAlly::GiveBuff(int _num, Parameter _para){
	if(rank[_para]<5){
		rank[_para]+=_num;
		if(rank[_para]>5){
			rank[_para]=5;
		}
		return CSkill::SUCCESSED;
	}else{
		return CSkill::FAILED;
	}
}
CSkill::SkillResult CAlly::GiveBst(CSkill* _givenSkill){
	int n=GetRand(100);
	if( nowBst==NO_BST){
		if(_givenSkill->GetBstPer() > n+rank[SPEED]*6 ){
			nowBst =_givenSkill->GetBstType();
			return CSkill::SUCCESSED;
		}
		else{
			return CSkill::AVOIDED;
		}
	}else{
		return CSkill::FAILED;
	}
}
CSkill::SkillResult CAlly::GiveBstRecover(CSkill* _givenSkill){
	if(nowBst==NO_BST){
		return CSkill::FAILED;
	}else{
		switch(_givenSkill->GetBstRecoverType()){
		case CSkill::BstRecoverType::ALL:
			recoveredBst = nowBst;
			nowBst=NO_BST;
			bstTurn=0;
			Skills.RecoverBstInfuluence();
			return CSkill::SUCCESSED;
			break;
		case CSkill::BstRecoverType::ELEMENT:
			if( nowBst==YAKEDO||
				nowBst==TOUSYOU||
				nowBst==RESSYOU||
				nowBst==MAHI
			){
				recoveredBst = nowBst;
				nowBst=NO_BST;
				bstTurn=0;
				Skills.RecoverBstInfuluence();
				return CSkill::SUCCESSED;
			}else{
				return CSkill::FAILED;
			}
			break;
		case CSkill::BstRecoverType::NOT_ELE:
			if( nowBst==YAKEDO||
				nowBst==TOUSYOU||
				nowBst==RESSYOU||
				nowBst==MAHI
			){
				return CSkill::FAILED;
			}else{	
				recoveredBst = nowBst;
				nowBst=NO_BST;
				bstTurn=0;
				Skills.RecoverBstInfuluence();
				return CSkill::SUCCESSED;
			}
			break;
		}
	}
	return CSkill::FAILED;
}

BadStatus CAlly::NowBst(){
	return nowBst;
}
bool CAlly::BstRecover(){
	bstTurn++;
	switch(nowBst){
	case NEMURI:
		if(bstTurn<=1){
			return false;
		}else{
			int n=GetRand(99);
			if(n > bstTurn*25){
				return false;
			}else{
				recoveredBst=NEMURI;
				nowBst=NO_BST;
				bstTurn=0;
				return true;
			}
		}
		break;
	case MAHUU:
		if(bstTurn<=2){
			return false;
		}else{
			int n=GetRand(99);
			if(n > bstTurn*20){
				return false;
			}else{
				recoveredBst=MAHUU;
				Skills.RecoverBstInfuluence();
				nowBst=NO_BST;
				bstTurn=0;
				return true;
			}
		}
		break;
	}
	return false;
}
BadStatus CAlly::RecoveredBst(){
	return recoveredBst;
}
void CAlly::BstEffect(){
	switch(nowBst){
	case BadStatus::YAKEDO:
		damage = hpMax/10;
		damage *= /*乱数*/(GetRand(10)+95);
		damage /= 100;
		hp-=damage;
		if(hp<=0){
			damage+=hp-1;
			hp=1;
		}
		break;
	case BadStatus::TOUSYOU:
		damage = hpMax/10;
		damage *= /*乱数*/(GetRand(10)+95);
		damage /= 100;
		hp-=damage;
		if(hp<=0){
			damage+=hp-1;
			hp=1;
		}
		if(bstTurn == 1){
			Skills.BstInfuluence(TOUSYOU);
		}
		break;
	case BadStatus::RESSYOU:
		damage = hpMax/10;
		damage *= /*乱数*/(GetRand(10)+95);
		damage /= 100;
		hp-=damage;
		if(hp<=0){
			damage+=hp-1;
			hp=1;
		}
		break;
	case BadStatus::MAHI:

		break;
	case BadStatus::DOKU:
		damage = hpMax/8;
		damage *= /*乱数*/(GetRand(10)+95);
		damage /= 100;
		hp-=damage;
		if(hp<=0){
			damage+=hp-1;
			hp=1;
		}
		break;
	case BadStatus::NEMURI:

		break;
	case BadStatus::MAHUU:
		if(bstTurn == 1){
			Skills.BstInfuluence(MAHUU);
		}
		break;
	}
}
/////////////プライベート関数/////////////
void CAlly::DeleteSkill(){}

void CAlly::LoadStatusGraph(){
	if(statusGraph[0][0]==0){
		statusGraph[Parameter::P_ATK][0]=LoadGraph("noseResource/atackUp.png");
		statusGraph[Parameter::P_ATK][1]=LoadGraph("noseResource/atackDown.png");

		statusGraph[Parameter::P_GARD][0]=LoadGraph("noseResource/gardUp.png");
		statusGraph[Parameter::P_GARD][1]=LoadGraph("noseResource/gardDown.png");

		statusGraph[Parameter::M_ATK][0]=LoadGraph("noseResource/m_atackUp.png");
		statusGraph[Parameter::M_ATK][1]=LoadGraph("noseResource/m_atackDown.png");

		statusGraph[Parameter::M_GARD][0]=LoadGraph("noseResource/m_gardUp.png");
		statusGraph[Parameter::M_GARD][1]=LoadGraph("noseResource/m_gardDown.png");

		statusGraph[Parameter::SPEED][0]=LoadGraph("noseResource/speedUp.png");
		statusGraph[Parameter::SPEED][1]=LoadGraph("noseResource/speedDown.png");
	}
}

//////////////////////CMe//////////////////////////////////////
////////////コンストラクタ///////////
CMe::CMe(const char* _name ,int _hp,int _sp,int _physic_A,int _physic_G,int _mA,int _mG,int _speed)
	:CAlly(_name , _hp, _sp,_physic_A, _physic_G,_mA, _mG,_speed)
{}
////////////パブリック関数/////////
void CMe::DrawInfo(){
	
	DrawStatusGraph();
	DrawBox(257,271,317,331,BLACK,true);//アイコン的なやつを入れる枠
	DrawBox(257,271,317,331,WHITE,false);//アイコン的なやつを入れる枠

	DrawBox(321, 279,483,301,BLACK,true);
	DrawBox(321, 279,483,301,WHITE,false);
	if(hpMax!=0 && hp>0){
		DrawBox( 322, 280 , 322+160*hp/hpMax , 300 , GREEN , true );
	}
	DrawFormatString( 322 , 280 , WHITE , "%d/%d" , hp , hpMax );
	
	DrawBox(321, 309,483,331,BLACK,true);
	DrawBox(321, 309,483,331,WHITE,false);
	if(spMax!=0 && sp>0){
		DrawBox( 322 , 310 , 322+160*sp/spMax , 330 , BLUE , true );
	}
	DrawFormatString( 322 , 310 , WHITE , "%d/%d" , sp , spMax );
}

void CMe::GiveDamage(CSkill* _givenSkill,int _atk){

	if(_givenSkill->GetSkillType()==CSkill::PHYSIC_ATK){
		if(defensive){
			damage = _givenSkill->GetAmount() * _atk / RealParameter(P_GARD) *3/5;
		}else{
			damage = _givenSkill->GetAmount() * _atk / RealParameter(P_GARD) *8/5;
		}
	}else{
		if(defensive){
			damage = _givenSkill->GetAmount() * _atk / RealParameter(M_GARD) *7/5;
		}else{
			damage = _givenSkill->GetAmount() * _atk / RealParameter(M_GARD) *11/5;
		}
	}
	damage *= /*乱数*/(GetRand(10)+95);
	damage /= 100;
	hp -= damage;
	if(hp<=0){
		hp=0;
	}
}
void CMe::DrawDamage(){
	if(damageGiven){	
		if( (hp*100)/hpMax>50){
			DrawFormatString(277,293,WHITE,"-%d",damage,false);
		}else if((hp*100)/hpMax>20){
			DrawFormatString(277,293,YELLOW,"-%d",damage,false);
		}else{
			DrawFormatString(277,293,RED,"-%d",damage,false);
		}
	}
	else{
		DrawString(272,293,"MISS",WHITE);
	}
}
void CMe::DrawBstDamage(){
	if(	nowBst==YAKEDO||
		nowBst==TOUSYOU||
		nowBst==RESSYOU||
		nowBst==DOKU){
		if( (hp*100)/hpMax>50){
			DrawFormatString(277,293,WHITE,"-%d",damage,false);
		}else if((hp*100)/hpMax>20){
			DrawFormatString(277,293,YELLOW,"-%d",damage,false);
		}else{
			DrawFormatString(277,293,RED,"-%d",damage,false);
		}
	}
}
CSkill::SkillResult CMe::GiveRecover(CSkill* _givenSkill,int _m_a){
	if(hp==hpMax){
		return CSkill::FAILED;
	}
	if(defensive){//防御中被回復量アップ
		recoverAmount = _givenSkill->GetAmount() * _m_a/RealParameter(M_GARD)*4/3;
	}else{
		recoverAmount =  _givenSkill->GetAmount() * _m_a/RealParameter(M_GARD);
	}
	hp+=recoverAmount;
	if(hp>hpMax){
		hp=hpMax;
	}
	return CSkill::SUCCESSED;
}
bool CMe::AtackGiven(CSkill* _skill){
	int per=GetRand(100);
	if(per+rank[SPEED]*6 < _skill->GetHitPer()){
		return damageGiven=true;
	}else{
		return damageGiven=false;
	}
}
////////////プライベート関数/////////
void CMe::DrawStatusGraph(){
	LoadStatusGraph();
	for(int i=0;i<Parameter::SPEED+1;i++){
		if(rank[i]>0){
			DrawGraph(257+i*40,338,statusGraph[i][0],true);
			DrawFormatString(280+i*40,343,WHITE,"%d",rank[i]);
		}
		if(rank[i]<0){
			DrawGraph(257+i*40,338,statusGraph[i][1],true);
			DrawFormatString(280+i*40,343,WHITE,"%d",-rank[i]);
		}
	}
}
//////////////////////////CGirl///////////////////////////
///////////コンストラクタ////////////
CGirl::CGirl(const char* _name ,int _hp,int _sp,int _pA,int _pG,int _mA,int _mG,int _speed)
	:CAlly(_name , _hp, _sp, _pA,_pG,_mA, _mG, _speed)
{}
////////////パブリック関数/////////
void CGirl::DrawInfo(){
	DrawStatusGraph();

	DrawBox(517,271,577,331,BLACK,true);//アイコン的なやつを入れる枠
	DrawBox(517,271,577,331,WHITE,false);//アイコン的なやつを入れる枠
	
	DrawBox(581, 279,743,301,BLACK,true);
	DrawBox(581, 279,743,301,WHITE,false);
	if(hpMax!=0 && hp>0){
		DrawBox( 582, 280 , 582+160*hp/hpMax , 300 , GREEN , true );
	}
	DrawFormatString( 582 , 280 , WHITE , "%d/%d" , hp , hpMax );
	
	DrawBox(581, 309,743,331,BLACK,true);
	DrawBox(581, 309,743,331,WHITE,false);
	if(spMax!=0 && sp>0){
		DrawBox( 582, 310 , 582+160*sp/spMax , 330 , BLUE , true );
	}
	DrawFormatString( 582 , 310 , WHITE , "%d/%d" , sp , spMax );
}

void CGirl::GiveDamage(CSkill* _givenSkill,int atk){

	if(_givenSkill->GetSkillType()==CSkill::PHYSIC_ATK){
		if(defensive){
			damage = _givenSkill->GetAmount() * atk / status[P_GARD] *2/5;
		}else{
			damage = _givenSkill->GetAmount() * atk / status[P_GARD] *11/5;
		}
	}else{
		if(defensive){
			damage = _givenSkill->GetAmount() * atk / status[M_GARD] *2/5;
		}else{
			damage = _givenSkill->GetAmount() * atk / status[M_GARD] *10/5;
		}
	}
	damage *= (/*乱数*/(GetRand(10)+95));
	damage /= 100;
	hp -= damage;
	if(hp<=0){
		hp = 0;
	}
}

void CGirl::DrawDamage(){
	if(damageGiven){
		if( (hp*100)/hpMax > 50){
			DrawFormatString(537,293,WHITE,"-%d",damage,false);
		}else if( (hp*100)/hpMax >20){
			DrawFormatString(537,293,YELLOW,"-%d",damage,false);
		}else{
			DrawFormatString(537,293,RED,"-%d",damage,false);
		}
	}else{
		DrawString(532,293,"MISS",WHITE);
	}
}
void CGirl::DrawBstDamage(){
	if(	nowBst==YAKEDO||
		nowBst==TOUSYOU||
		nowBst==RESSYOU||
		nowBst==DOKU){
		if( (hp*100)/hpMax > 50){
			DrawFormatString(537,293,WHITE,"-%d",damage,false);
		}else if( (hp*100)/hpMax >20){
			DrawFormatString(537,293,YELLOW,"-%d",damage,false);
		}else{
			DrawFormatString(537,293,RED,"-%d",damage,false);
		}
	}
}

CSkill::SkillResult CGirl::GiveRecover(CSkill* _givenSkill,int _m_a){
	if(hp==hpMax){
		return CSkill::FAILED;
	}
	if(defensive){//防御中被回復量アップ
		recoverAmount = _givenSkill->GetAmount() * _m_a/RealParameter(M_GARD)* 2;
	}else{
		recoverAmount =  _givenSkill->GetAmount() * _m_a/RealParameter(M_GARD)* 3/2;
	}
	recoverAmount *= (/*乱数*/(GetRand(10)+95)/100);
	hp+=recoverAmount;
	if(hp>hpMax){
		hp=hpMax;
	}
	return CSkill::SUCCESSED;
}

bool CGirl::AtackGiven(CSkill* _skill){
	int per=GetRand(100)+5;
	if(per+rank[SPEED]*6 < _skill->GetHitPer()){
		return damageGiven=true;
	}else{
		return damageGiven=false;
	}
}
////////////プライベート関数/////////
void CGirl::DrawStatusGraph(){
	LoadStatusGraph();
	for(int i=0;i<Parameter::SPEED+1;i++){
		if(rank[i]>0){
			DrawGraph(517+i*40,338,statusGraph[i][0],true);
			DrawFormatString(540+i*40,343,WHITE,"%d",rank[i]);
		}
		if(rank[i]<0){
			DrawGraph(517+i*40,338,statusGraph[i][1],true);
			DrawFormatString(540+i*40,343,WHITE,"%d",-rank[i]);
		}
	}
}