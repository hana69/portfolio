#include"Skill.h"

////////CSkill////////////////////////////////
CSkill::CSkill()
	:name(""),
	 explain(""),
	 valid(false)
{}
CSkill::CSkill(const char*){
	valid=true;
}
CSkill::CSkill(const char* _name,const char* _hurigana,const char* _explain,TargetType _targetType,int _consumeP)
	:name(_name),
	 explain(_explain),
	 hurigana(_hurigana),
	 valid(true),
	 targetType(_targetType),
	 consumePoint(_consumeP)
{
	bstType=NO_BST;
	bstPer=0;
}

CSkill::CSkill(const char* _name,const char* _hurigana,const char* _explain,TargetType _targetType,int _consumeP,BadStatus _bstType,int _bstPer)
	:name(_name),
	 explain(_explain),
	 hurigana(_hurigana),
	 valid(true),
	 targetType(_targetType),
	 consumePoint(_consumeP),
	 bstType(_bstType),
	 bstPer(_bstPer)
{}

std::string CSkill::GetName(){
	return name;
}
std::string CSkill::GetHurigana(){
	return hurigana;
}
std::string CSkill::GetExplain(){
	return explain;
}
int CSkill::GetConsumePoint(){
	return consumePoint;
}
CSkill::TargetType CSkill::GetTargetType(){
	return this->targetType;
}

std::string CSkill::Message(){
	return "";
}
CSkill::BuffType CSkill::GetBuffType(){
	return PA_BUFF;
}
CSkill::BstRecoverType CSkill::GetBstRecoverType(){
	return BstRecoverType::ALL;
}
Element CSkill::GetElement(){
	return NO_ELEMENT;
}

int CSkill::GetAmount(){
	return 0;
}

BadStatus CSkill::GetBstType(){
	return bstType;
}
int CSkill::GetBstPer(){
	return bstPer;
}

int CSkill::GetHitPer(){
	return 0;
}

bool CSkill::UseSuccess(int _nowPoint){
	return _nowPoint>=consumePoint;
}

bool CSkill::GetValid(){
	return valid;
}

	////////CPhysicAtack//////////////////////////
	CPhysicAtack::CPhysicAtack(FILE* _fp)
		:CSkill("")
	{
		char _name[100],_hurigana[100],_explain[100],_element[100],_targetType[100],_bstType[100];
		fscanf(_fp,
			"%s   %s         %s      %d      %s       %s          %d            %d      %s       %d",
			_name,_hurigana,_explain,&damage,_element,_targetType,&consumePoint,&hitPer,_bstType,&bstPer
			);
		name=_name;
		explain=_explain;
		hurigana=_hurigana;
		for(int i=0;i<ELEMENT_MAX;i++){
			if(_element==ElementString[i]){
				element=(Element)i;
				break;
			}
		}
		for(int i=0;i<=ALLY_ALL;i++){
			if(_targetType==TargetTypeString[i]){
				targetType=(TargetType)i;
				break;
			}
		}
		for(int i=0;i<=MAHUU;i++){
			if(_bstType == bstString[i]){
				bstType =  (BadStatus)i;
				break;
			}
		}
	}
	int CPhysicAtack::GetAmount(){
		return damage;
	}
	Element CPhysicAtack::GetElement(){
		return element;
	}
	CSkill::SkillType CPhysicAtack::GetSkillType(){
		return PHYSIC_ATK;
	}
	int CPhysicAtack::GetHitPer(){
		return hitPer;
	}
	////////CMajicAtack//////////////////////////
	CMajicAtack::CMajicAtack(FILE* _fp)
		:CSkill("")
	{
		char _name[100],_hurigana[100],_explain[100],_element[100],_targetType[100],_bstType[100];
		fscanf(_fp,
			"%s   %s        %s       %d      %s       %s          %d            %d      %s       %d",
			_name,_hurigana,_explain,&damage,_element,_targetType,&consumePoint,&hitPer,_bstType,&bstPer
			);
		name=_name;
		explain=_explain;
		hurigana=_hurigana;
		for(int i=0;i<ELEMENT_MAX;i++){
			if(_element==ElementString[i]){
				element=(Element)i;
				break;
			}
		}
		for(int i=0;i<=ALLY_ALL;i++){
			if(_targetType==TargetTypeString[i]){
				targetType=(TargetType)i;
				break;
			}
		}
		for(int i=0;i<=MAHUU;i++){
			if(_bstType == bstString[i]){
				bstType =  (BadStatus)i;
				break;
			}
		}
	}
	int CMajicAtack::GetAmount(){
		return damage;
	}
	CSkill::SkillType CMajicAtack::GetSkillType(){
		return MAJIC_ATK;
	}
	Element CMajicAtack::GetElement(){
		return element;
	}
	int CMajicAtack::GetHitPer(){
		return hitPer;
	}
	///////CBuff////////////////////////////
	CBuff::CBuff(FILE* _fp)
		:CSkill("")
	{
		char _name[100],_hurigana[100],_explain[100],_message[100],_buffType[100],_targetType[100],_bstType[100];
		fscanf(_fp,
			"%s    %s       %s       %s       %d      %s        %s          %d            %s       %d",
			_name,_hurigana,_explain,_message,&amount,_buffType,_targetType,&consumePoint,_bstType,&bstPer
			);
		name=_name;
		hurigana=_hurigana;
		explain=_explain;
		message=_message;
		for(int i=0;i<=SPD_BUFF;i++){
			if(_buffType==BuffTypeString[i]){
				type=(BuffType)i;
				break;
			}
		}
		for(int i=0;i<=ALLY_ALL;i++){
			if(_targetType==TargetTypeString[i]){
				targetType=(TargetType)i;
				break;
			}
		}
		for(int i=0;i<=MAHUU;i++){
			if(_bstType == bstString[i]){
				bstType =  (BadStatus)i;
				break;
			}
		}
	}
	CBuff::CBuff(const char* _name,const char* _hurigana,const char* _explain,const char* _message,int _amount,BuffType _type,TargetType _targetType,int _consumeP )
		:CSkill(_name,_hurigana,_explain,_targetType,_consumeP),
		message(_message),
		amount(_amount),
		type(_type)
	{}
	int CBuff::GetAmount(){
		return amount;
	}
	CSkill::SkillType CBuff::GetSkillType(){
		return BUFF;
	}

	CBuff::BuffType CBuff::GetBuffType(){
		return type;
	}

	std::string CBuff::Message(){
		return message;
	}

	/////////////CRecover///////////////////
	CRecover::CRecover(FILE* _fp)
		:CSkill("")
	{
		char _name[100],_hurigana[100],_explain[100],_message[100],_targetType[100],_bstType[100];
		fscanf(_fp,
			"%s   %s        %s       %s       %d      %s          %d            %s       %d",
			_name,_hurigana,_explain,_message,&amount,_targetType,&consumePoint,_bstType,&bstPer
			);
		name=_name;
		hurigana=_hurigana;
		explain=_explain;
		message=_message;
		for(int i=0;i<=ALLY_ALL;i++){
			if(_targetType==TargetTypeString[i]){
				targetType=(TargetType)i;
				break;
			}
		}
		for(int i=0;i<=MAHUU;i++){
			if(_bstType == bstString[i]){
				bstType =  (BadStatus)i;
				break;
			}
		}
	}
	
	int CRecover::GetAmount(){
		return amount;
	}
	CSkill::SkillType CRecover::GetSkillType(){
		return RECOVER;
	}

	std::string CRecover::Message(){
		return message;
	}
	/////////////CBadStatus///////////////////
	CBadStatus::CBadStatus(FILE* _fp)
		:CSkill("")
	{
		char _name[100],_hurigana[100],_explain[100],_targetType[100],_bstType[100];
		fscanf(_fp,
			"%s   %s        %s       %s          %d            %s       %d",
			_name,_hurigana,_explain,_targetType,&consumePoint,_bstType,&bstPer
		);
		name=_name;
		hurigana=_hurigana;
		explain=_explain;
		for(int i=0;i<=ALLY_ALL;i++){
			if(_targetType==TargetTypeString[i]){
				targetType=(TargetType)i;
				break;
			}
		}
		for(int i=0;i<=MAHUU;i++){
			if(_bstType == bstString[i]){
				bstType =  (BadStatus)i;
				break;
			}
		}
	}
	
	CSkill::SkillType CBadStatus::GetSkillType(){
		return BAD_STATUS;
	}
	////////////CBstRecoverType//////////////
	CBstRecover::CBstRecover(FILE* _fp)
		:CSkill("")
	{
		char _name[100],_hurigana[100],_explain[100],_targetType[100],_bstRecoverType[100];
		fscanf(_fp,
			"%s   %s        %s       %s          %d            %s       ",
			_name,_hurigana,_explain,_targetType,&consumePoint,_bstRecoverType
		);
		name=_name;
		hurigana=_hurigana;
		explain=_explain;
		for(int i=0;i<=ALLY_ALL;i++){
			if(_targetType==TargetTypeString[i]){
				targetType=(TargetType)i;
				break;
			}
		}
		for(int i=0;i<=MAHUU;i++){
			if(_bstRecoverType == bstRecoverString[i]){
				type =  (BstRecoverType)i;
				break;
			}
		}
	}
	CSkill::SkillType CBstRecover::GetSkillType(){
		return BST_RECOVER;
	}

	CSkill::BstRecoverType CBstRecover::GetBstRecoverType(){
	return type;
}