#include"ArmManager.h"

////////////////コンストラクタ/////////////
CArmManager::CArmManager():
	ArmMenu( "noseResource/battleMenuHaikei.png","noseResource/battleMenuSelect.png", 128 , 60 , 128 , 30 , 3 ,10 , WHITE , RED ),
	arm_fp( fopen( "noseResource/ArmData.txt" , "r" ) ),
	FIRST_WOOD(arm_fp),
	JAPANESE_DICTIONARY(arm_fp),
	HONOO_NO_KEN(arm_fp)
{	
	fclose( arm_fp );

	havingArmNum=0;
	ArmMenu.AddNewString( "もどる" , 3 , 10 );

	//fscanf( arm_fp , "%s %d %d %d", FIRST_WOOD.name.c_str() , &(FIRST_WOOD.atk),&(FIRST_WOOD.dff),&(FIRST_WOOD.element) );

}
///////////////パブリック関数//////////////
void CArmManager::Awake(){
	armInfoPic=LoadGraph( "noseResource/ArmInfo.png" );
	AddArm( &FIRST_WOOD );
	AddArm( &JAPANESE_DICTIONARY );
	AddArm( &HONOO_NO_KEN);
}

void CArmManager::AddArm( CArm* _newArm){

	havingArmNum++;
	havingArm[(havingArmNum-1)/3][(havingArmNum-1)%3] = _newArm;
	ArmMenu.AddNewString( _newArm -> name.c_str() );

}

void CArmManager::DeleteArm(int _x,int _y){
	
	for(int i = _x-1;i<3;i++){
		for(int j=_y-1;j<10;j++){
			if(j < 10){
				havingArm[i][j] = havingArm[i][j+1];
			}else{
				havingArm[i][j] = havingArm[i+1][0];
			}
		}
	}

}

bool CArmManager::ReturnSelected(){
	if( ArmMenu.Selected() ){
		if( ArmMenu.SelectingString() == "もどる" ){
			return true;
		}
	}
	return false;
}

void CArmManager::Draw(){
	ArmMenu.Draw();
	DrawInfo();
}

void CArmManager::DrawInfo(int _x,int _y){
	DrawGraph( 0 , 60 , armInfoPic , true );
	if( havingArm[_x-1][_y-1].GetName() != "" ){
		havingArm[_x-1][_y-1].DrawInfo();
	}
}

void CArmManager::DrawInfo(){
	DrawInfo(ArmMenu.SelectSpot().first,ArmMenu.SelectSpot().second);
}