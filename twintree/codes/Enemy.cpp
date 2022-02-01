#include"Enemy.h"

/////////コンストラクタ///////
CEnemy::CEnemy():
level(0),hp(0),sp(0),name("てき"),exp(0)
{
	for(int i=0;i<5;i++){
		per[i] = 100;
	}
	for(int i=0;i<=MAHUU;i++){
		bstPer[i]=100;
	}
	picture=0;
	hpMax=hp;
	damage=0;
	position=1;
	live=false;
	thisTurnDeath=true;
	nowBst=NO_BST;
	recoveredBst=NO_BST;
	bstTurn=0;
	usedSkillNum=0;
}

CEnemy::CEnemy(FILE* _enemyData,const char* _picName){
	char c[100];
	fscanf(_enemyData ,
	   "%s  %d    %d   %d               %d              %d             %d               %d              %d     %d       %d %d %d %d %d    %d %d %d %d %d %d %d" ,
		c , &hp , &sp ,&status[P_ATK] , &status[P_GARD],&status[M_ATK],&status[M_GARD], &status[SPEED], &exp , &level , &per[NO_ELEMENT] , &per[FIRE] , &per[ICE] , &per[WIND] , &per[THUNDER],&bstPer[YAKEDO],&bstPer[TOUSYOU],&bstPer[RESSYOU],&bstPer[MAHI],&bstPer[DOKU],&bstPer[NEMURI],&bstPer[MAHUU] );
	name=c;
	hpMax=hp;
	spMax=sp;
	live=true;
	thisTurnDeath=false;
	damage=0;
	nowBst=NO_BST;
	recoveredBst=NO_BST;
	for(int i=P_ATK;i<=SPEED;i++){
		rank[i]=0;
	}
	bstTurn=0;
	usedSkillNum=0;
	picture=0;
	picName=_picName;
}

/////////パブリック関数/////////

void CEnemy::Init(){
	hp=hpMax;
	sp=spMax;
	live=true;
	thisTurnDeath=false;
	damage=0;
	nowBst=NO_BST;
	recoveredBst=NO_BST;
	bstTurn=0;
	for(int i=P_ATK;i<=SPEED;i++){
		rank[i]=0;
	}
	usedSkillNum=0;
}
void CEnemy::TurnInit(){
	thisTurnDeath=false;
}
void CEnemy::AddSkill(CSkill* _newSkill,int _per){
	Skills.LearnNewSkill(_newSkill);
	usePercent[Skills.GetSkillNum()-1] = _per;
}
CSkill* CEnemy::UseSkill(){
	int rand=GetRand(100);
	int temp=0;
	
	for(int i=0;i<10;i++){
		temp+=usePercent[i];
		if(rand<=temp){
			usedSkillNum=i;
			return Skills.GetSkill(i);
		}
	}
	usedSkillNum=1;
	return Skills.GetSkill(1);
}

bool CEnemy::NowSkillUseAble(){
	return Skills.UseAble(usedSkillNum);
}

void CEnemy::SetPosition(int _p){
	position = _p;
}

int CEnemy::GetRank(Parameter _para){
	return rank[_para];
}
int CEnemy::GetStatus(Parameter _para){
	return status[_para];
}
int CEnemy::RealParameter(Parameter _para){
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

void CEnemy::ConsumeP(){
	if(Skills.GetSkill(usedSkillNum)->GetSkillType() == CSkill::PHYSIC_ATK){
		if(nowBst==RESSYOU){
			hp -= Skills.GetSkill(usedSkillNum)->GetConsumePoint()*5;
		}else{
			hp -= Skills.GetSkill(usedSkillNum)->GetConsumePoint();
		}
	}else{
		sp -= Skills.GetSkill(usedSkillNum)->GetConsumePoint();
	}
}

int CEnemy::GetHP(){
	return hp;
}
int CEnemy::GetSP(){
	return sp;
}

CSkill::SkillResult CEnemy::GiveBuff(int _num, Parameter _para){
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

int CEnemy::GetExp(){
	return exp;
}
std::string CEnemy::GetName(){
	return name;
}
bool CEnemy::GetLive(){
	return live;
}

void CEnemy::Draw(){
	if(picName!="" && picture==0){
		picture=LoadGraph(picName.c_str());
	}
	if(picture==0){
		DrawBox(255+(position-1)*76,110,325+(position-1)*76,210,BLACK,true);
		if(live){
			DrawBox(255+(position-1)*76,110,325+(position-1)*76,210,BLUE,false);
		}else{
			DrawBox(255+(position-1)*76,110,325+(position-1)*76,210,RED,false);
		}
	}else{
		DrawExtendGraph(255+(position-1)*76,110,325+(position-1)*76,210,picture,true);
	}
	DrawHPGage();
}

void CEnemy::GiveDamage(CSkill* _givenSkill,int _atk){
	thisTurnDeath=false;
	
	if(_givenSkill->GetSkillType()==CSkill::SkillType::PHYSIC_ATK){
		damage = _givenSkill->GetAmount()*per[_givenSkill->GetElement()]/100 * _atk /RealParameter(P_GARD);
	}else{
		damage = _givenSkill->GetAmount()*per[_givenSkill->GetElement()]/100 * _atk /RealParameter(M_GARD);
	}
	damage *= /*乱数*/(GetRand(10)+95);
	damage/=100;
	hp -= damage;

	if(hp<=0){
		hp=0;
		live=false;
		thisTurnDeath=true;
	}
}
int CEnemy::GetDamage(){
	return damage;
}
void CEnemy::DrawDamage(){
	if(hpMax!=0 && (hp>0 || thisTurnDeath ) ){
		if(damageGiven){
			if( (hp*100/hpMax) > 50){
				DrawFormatString( 255+(position-1)*76 , 150 , WHITE , "-%d" , damage);
			}else if( (hp*100/hpMax) > 20 ){
				DrawFormatString( 255+(position-1)*76 , 150 , YELLOW , "-%d", damage);
			}else{
				DrawFormatString( 255+(position-1)*76 , 150 , RED , "-%d" , damage);
			}
		}else{
			DrawString( 270+(position-1)*76 , 150 ,"MISS", WHITE);
		}
	}
}
void CEnemy::DrawBstDamage(){
	if(	nowBst==YAKEDO||
		nowBst==TOUSYOU||
		nowBst==RESSYOU||
		nowBst==DOKU){
		if( (hp*100/hpMax) > 50){
			DrawFormatString( 255+(position-1)*76 , 150 , WHITE , "-%d" , damage);
		}else if( (hp*100/hpMax) > 20 ){
			DrawFormatString( 255+(position-1)*76 , 150 , YELLOW , "-%d", damage);
		}else{
			DrawFormatString( 255+(position-1)*76 , 150 , RED , "-%d" , damage);
		}
	}
}
CSkill::SkillResult CEnemy::GiveRecover(CSkill* _givenSkill,int m_a){
	if(hp==hpMax){
		return CSkill::FAILED;
	}
	recoverAmount = _givenSkill->GetAmount()*(m_a / RealParameter(M_GARD) );//被回復側の魔法防御力が高いほど回復量は減る
	recoverAmount *= (/*乱数*/(GetRand(10)+95)/100);
	hp+=recoverAmount;
	if(hp>hpMax){
		hp=hpMax;
	}
	return CSkill::SUCCESSED;
}
CSkill::SkillResult CEnemy::GiveBst(CSkill* _givenSkill){
	int n=GetRand(100);
	if( _givenSkill->GetBstType()==NO_BST){
		if( _givenSkill->GetBstPer() > n+rank[SPEED]*6*bstPer[_givenSkill->GetBstType()]/100 ){
			nowBst = _givenSkill->GetBstType();
			return CSkill::SUCCESSED;
		}else{
			return CSkill::AVOIDED;
		}
	}else{
		return CSkill::FAILED;
	}
}
CSkill::SkillResult CEnemy::GiveBstRecover(CSkill* _givenSkill){
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

BadStatus CEnemy::NowBst(){
	return nowBst;
}
bool CEnemy::BstRecover(){
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
				nowBst=NO_BST;
				Skills.RecoverBstInfuluence();
				bstTurn=0;
				return true;
			}
		}
		break;
	}
	return false;
}
BadStatus CEnemy::RecoveredBst(){
	return recoveredBst;
}
void CEnemy::BstEffect(){
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

bool CEnemy::AtackGiven(CSkill* _skill){
	int per=GetRand(100);
	if(per < _skill->GetHitPer()){
		return damageGiven=true;
	}else{
		return damageGiven=false;
	}
}
/////////////プライベート関数//////////////

void CEnemy::DrawHPGage(){
	DrawBox( 255+(position-1)*76 , 80 , 325+(position-1)*76 , 100 , WHITE , false );
	if(hpMax!=0 && hp>0){
		DrawBox( 256+(position-1)*76 , 81 , 256+(position-1)*76+68*hp/hpMax , 99 , GREEN , true );
	}
	DrawFormatString(255+(position-1)*76,82,WHITE,"%d/%d",hp,hpMax);
}