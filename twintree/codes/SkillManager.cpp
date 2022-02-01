#include"SkillManager.h"

//////////////コンストラクタ///////////////////
CSkillManager::CSkillManager()
	:Skills("noseResource/battleMenuHaikei.png","noseResource/battleMenuSelect.png",0,60,250,30,1,10,WHITE,RED),
	skillNum(0)
{
	for(int i=0;i<10;i++){
		skill[i] = NULL;
		useAble[i]=true;
		nonAbleCase[i]=BECAUSE_SHORTAGE;
	}
	selectable=true;
}
CSkillManager::CSkillManager(int _x,int _y)
	:Skills("noseResource/battleMenuHaikei.png","noseResource/battleMenuSelect.png",_x,_y,250,30,1,10,WHITE,RED),
	skillNum(0),
	x(_x),
	y(_y)
{
	for(int i=0;i<10;i++){
		skill[i] = NULL;
		useAble[i]=true;
		nonAbleCase[i]=BECAUSE_SHORTAGE;
	}
	selectable=true;
}
///////////////パブリック関数///////////////

void CSkillManager::Init(){
	for(int i=0;i<10;i++){
		skill[i] = NULL;
		useAble[i]=true;
	}
	skillNum=0;
}

void CSkillManager::Selectable(){
	Skills.Selectable();
}
void CSkillManager::UnSelectable(){
	Skills.UnSelectable();
}

void CSkillManager::BstInfuluence(BadStatus _bstType){
	if(_bstType==TOUSYOU){
		int a=0;
		int selectableNum[10];
		for(int i=0;i<skillNum;i++){
			if(useAble[i] && skill[i]->GetSkillType()==P_ATK){
				selectableNum[a]=i;
				a++;
			}
		}
		
		int b=GetRand(2)+1;
		if(a < b ){
			b=a;
		}
		int n=0;
		while(b>0){
			n=GetRand(a-1);
			if(useAble[selectableNum[n]] && skill[selectableNum[n]]->GetSkillType()==P_ATK){
				useAble[selectableNum[n]]=false;
				nonAbleCase[selectableNum[n]]=BECAUSE_TOUSYOU;
				b--;
			}
		}
	}
	else if(_bstType==MAHUU){
		for(int i=0;i<skillNum;i++){
			if(skill[i]->GetSkillType()!=P_ATK){
				useAble[i]=false;
				nonAbleCase[i]=BECAUSE_MAHUU;
			}
		}
	}

}
void CSkillManager::RecoverBstInfuluence(){
	for(int i=0;i<skillNum;i++){
		useAble[i]=true;
	}
}

void CSkillManager::Draw(int _nowHP,int _nowMP,BadStatus nowBst){
	Skills.Draw();
	DrawConsumePoint(nowBst);
	SetUseAble(_nowHP,_nowMP);
}
void CSkillManager::Draw(){
	Skills.Draw();
	DrawConsumePoint();
}
void CSkillManager::Draw(int _x,int _y){
	Skills.Draw(_x,_y);
	DrawConsumePoint(_x,_y);
}
bool CSkillManager::Selected(int _nowHP,int _nowMP,BadStatus nowBst){
	Draw(_nowHP,_nowMP,nowBst);
	return Skills.Selected();
}

void CSkillManager::LearnNewSkill(CSkill* _newSkill){
	
	if(skillNum >= 10){
		//ChangeSkill();
	}
	else{
		skill[skillNum] = _newSkill;
		useAble[skillNum] =true;
		skillNum++;
		Skills.AddNewString( _newSkill->GetName().c_str() , 1 , skillNum);
	}

}
void CSkillManager::DeleteSkill(){
	if(skillNum>0){
		skillNum--;
		skill[skillNum]=NULL;
		Skills.DeleteString();
	}
}

int CSkillManager::GetSkillNum(){
	return this->skillNum;
}

bool CSkillManager::UseAble(int _num){
	return useAble[_num];
}
bool CSkillManager::SelectingUseAble(){
	return useAble[Skills.SelectSpot().second-1];
}

bool CSkillManager::SkillValid(CSkill* _skill){
	for(int i=0;i<10;i++){
		if(skill[i]==_skill){
			return true;
		}
	}
	return false;
}

CSkill* CSkillManager::Selecting(){
	return skill[Skills.SelectSpot().second-1];
}

CSkill* CSkillManager::GetSkill(int _num){
	return skill[_num];
}
CSkill* CSkillManager::GetSkill(const char* _name){
	
	for(int i=0;i<10;i++){
		if(skill[i]->GetName().c_str() ==_name){
			return skill[i];
		}
	}
	return skill[0];
}

void CSkillManager::operator=(CSkillManager _obj){
	for(int i=0;i<_obj.GetSkillNum();i++){
		if(_obj.GetSkill(i)!=NULL){
			if(!SkillValid(_obj.GetSkill(i))){
				this->LearnNewSkill(_obj.GetSkill(i));
			}
		}else{
			skill[i]=NULL;
		}
	}
}
//////////////プライベート関数////////////////
void CSkillManager::ChangeSkill(CSkill* _newSkill){
	
	Skills.Draw();
	if( Skills.Selected() ){
		skill[Skills.SelectSpot().second] = _newSkill;
	}

}

void CSkillManager::SetUseAble(int _nowHP,int _nowMP){
	for(int i=0;i<skillNum;i++){
		if(skill[i]->GetSkillType() == CSkill::SkillType::PHYSIC_ATK){
			if(skill[i]->GetConsumePoint() > _nowHP && useAble[i]){
				useAble[i] =false;
				nonAbleCase[i]=BECAUSE_SHORTAGE;
			}
			if(!useAble[i] && nonAbleCase[i]==BECAUSE_SHORTAGE &&skill[i]->GetConsumePoint() < _nowHP ){
				useAble[i]=true;
			}
		}else{
			if(skill[i]->GetConsumePoint() > _nowMP && useAble[i]){
				useAble[i] = false;
				nonAbleCase[i]=BECAUSE_SHORTAGE;
			}
			if(!useAble[i] && nonAbleCase[i]==BECAUSE_SHORTAGE && skill[i]->GetConsumePoint() > _nowMP ){
				useAble[i]=true;
			}
		}
		
	}
	for(int i=0;i<skillNum;i++){
		if(useAble[i]){
			Skills.Active(i);
		}else{
			Skills.NonActive(i);
		}
	}
}
void CSkillManager::DrawConsumePoint(){
	for(int i=0;i<10;i++){
		if(skill[i]!=NULL){
			if(skill[i]->GetSkillType()==CSkill::SkillType::PHYSIC_ATK){
				DrawString(x+205, y + (i+0.5)*30-7,"HP",GREEN);
					DrawFormatString(x+230, y + (i+0.5)*30-7,RED,"%d",skill[i]->GetConsumePoint()*5); 
			}else{
				DrawString(x+205, y + (i+0.5)*30-7,"MP",BLUE);
				DrawFormatString(x+230, y + (i+0.5)*30-7,RED,"%d",skill[i]->GetConsumePoint()); 	
			}
		}
	}
}
void CSkillManager::DrawConsumePoint(int _x,int _y){
	for(int i=0;i<10;i++){
		if(skill[i]!=NULL){
			if(skill[i]->GetSkillType()==CSkill::SkillType::PHYSIC_ATK){
				DrawString(_x+205, _y + (i+0.5)*30-7,"HP",GREEN);
					DrawFormatString(_x+230, _y + (i+0.5)*30-7,RED,"%d",skill[i]->GetConsumePoint()); 
			}else{
				DrawString(_x+205, _y + (i+0.5)*30-7,"MP",BLUE);
				DrawFormatString(_x+230, _y + (i+0.5)*30-7,RED,"%d",skill[i]->GetConsumePoint()); 	
			}
		}
	}
}
void CSkillManager::DrawConsumePoint(BadStatus nowBst){
	for(int i=0;i<10;i++){
		if(skill[i]!=NULL){
			if(skill[i]->GetSkillType()==CSkill::SkillType::PHYSIC_ATK){
				DrawString(205, 60 + (i+0.5)*30-7,"HP",GREEN);
				if(nowBst==RESSYOU){
					DrawFormatString(230, 60 + (i+0.5)*30-7,RED,"%d",skill[i]->GetConsumePoint()*5); 
				}else{
					DrawFormatString(230, 60 + (i+0.5)*30-7,RED,"%d",skill[i]->GetConsumePoint()); 
				}
			}else{
				DrawString(205, 60 + (i+0.5)*30-7,"MP",BLUE);
				DrawFormatString(230, 60 + (i+0.5)*30-7,RED,"%d",skill[i]->GetConsumePoint()); 	
			}
		}
	}
}