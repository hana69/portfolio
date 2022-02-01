#include "Suken.h"
#include "DxLib.h"
#include <cstring>
#include "windows.h"//execute用

void KEYCHECK(char &CC ,int INPUT  ){
	switch(CC){
		case 0:
		CC =INPUT;
		break;
		case 1:
		CC++ ;
		break;
		case 2:
		CC = 2 * INPUT ;
		break;
	}
	return;
}


void SukenExecute(char *URL){//New
		OSVERSIONINFO OSver;
		OSver.dwOSVersionInfoSize =sizeof(OSVERSIONINFO);
		GetVersionEx(&OSver);
		if(OSver.dwMajorVersion < 6 ){//XP以下
			ShellExecute( NULL, "open", "IExplore",URL, NULL,SW_SHOWNORMAL );
		}else{//Vista以上
			ShellExecute( NULL, "open",URL, NULL, NULL,SW_SHOWNORMAL );
		}
}

int Power2(int x, int y){
    int i,result;
    for( i=1, result = 1; i <= y; i++) {result *= x;}
    return result;
}

int Clng ( char *Str ,int n ){
	char s[10];int ns = 0; int ret = 0;
	while(!(Str[n] == '\0' )  && ns < 10){
		switch (Str[n]){
		case '0': s[ns] = 0 ;ns++;break;case '1': s[ns] = 1 ;ns++;break;  
		case '2': s[ns] = 2 ;ns++;break;case '3': s[ns] = 3 ;ns++;break;  
		case '4': s[ns] = 4 ;ns++;break;case '5': s[ns] = 5 ;ns++;break;  
		case '6': s[ns] = 6 ;ns++;break;case '7': s[ns] = 7 ;ns++;break;  
		case '8': s[ns] = 8 ;ns++;break;case '9': s[ns] = 9 ;ns++;break;   
		}
		n++;
	}
	int ss = 0;ns--;
	while(ns >= 0){
		ret += s[ns] * Power2(10,ss);
		ns--; ss++;
	}
	return ret ;
}

int ClngFrom ( char *Str ,char Word ){
	char s[10];int ns = 0; int ret = 0;
	int n = 0;
	while(!(Str[n] == '\0' || Str[n] == Word )  && ns < 10){n++;}
	while(!(Str[n] == '\0' )  && ns < 10){
		switch (Str[n]){
		case '0': s[ns] = 0 ;ns++;break;case '1': s[ns] = 1 ;ns++;break;  
		case '2': s[ns] = 2 ;ns++;break;case '3': s[ns] = 3 ;ns++;break;  
		case '4': s[ns] = 4 ;ns++;break;case '5': s[ns] = 5 ;ns++;break;  
		case '6': s[ns] = 6 ;ns++;break;case '7': s[ns] = 7 ;ns++;break;  
		case '8': s[ns] = 8 ;ns++;break;case '9': s[ns] = 9 ;ns++;break;   
		}
		n++;
	}
	int ss = 0;ns--;
	while(ns >= 0){
		ret += s[ns] * Power2(10,ss);
		ns--; ss++;
	}
	return ret ;
}

int ClngTo ( char *Str ,char Word ){
	char s[10];int ns = 0; int ret = 0;
	int n = 0;
	while(!(Str[n] == '\0' || Str[n] == Word)  && ns < 10){
		switch (Str[n]){
		case '0': s[ns] = 0 ;ns++;break; case '1': s[ns] = 1 ;ns++;break;  
		case '2': s[ns] = 2 ;ns++;break; case '3': s[ns] = 3 ;ns++;break;  
		case '4': s[ns] = 4 ;ns++;break; case '5': s[ns] = 5 ;ns++;break;  
		case '6': s[ns] = 6 ;ns++;break; case '7': s[ns] = 7 ;ns++;break;  
		case '8': s[ns] = 8 ;ns++;break; case '9': s[ns] = 9 ;ns++;break;   
		}
		n++;
	}
	int ss = 0;ns--;
	while(ns >= 0){
		ret += s[ns] * Power2(10,ss);
		ns--; ss++;
	}
	return ret ;
}

CIntData::CIntData(char *_DataName){
	int Len;
	Len = std::strlen (_DataName);
	DataName = new char [Len + 1];
	std::strcpy(DataName , _DataName);
	DataName[Len] = '\0';
}

void CIntData::NewMake(){
	FILE *fp;
	fp = fopen( DataName , "w+");/////////////書き込み
	if (fp == NULL){
		DataName = "iMaGiNaRy.imr";
		fp = fopen( DataName , "w+");
	}
	for(int i = 0; i <2000 ;i++){
	fputs("0:0\r\n" , fp);//書き込み
	}
	fclose(fp);
}

void CIntData::ReadData(){
	FILE *fp;	
	char s[64];
	fp = fopen( DataName , "a"); //ファイルを強引に作成or確保
	if (fp == NULL){
		DataName = "iMaGiNaRy.imr";
		fp = fopen( DataName , "a");
	}	
	fclose(fp);
	fp = fopen( DataName , "r+");/////////////読み込み
	int n = 0;
	while (fgets(s, 64, fp) != NULL && n < 2000) {
		LeftData[n] = ClngTo(s,':');
		RightData[n] = ClngFrom(s,':');
		n++;
	}
	fclose(fp);
	if(n == 0){NewMake ();ReadData() ;}
}

void CIntData::WriteData(){
	FILE *fp;	
	fp = fopen( DataName , "a"); //ファイルを強引に作成or確保
	if (fp == NULL){
		DataName = "iMaGiNaRy.imr";
		fp = fopen( DataName , "a");
	}	
	fclose(fp);
	fp = fopen( DataName , "r+");/////////////読み込み
 
	for(int i=0;i<2000;i++){/////////////書き込み	
	fprintf( fp, "%d:%d\r\n",LeftData[i],RightData[i] );
	}
	fclose(fp);

}


CBox::CBox(){
	Color = GetColor( 128 , 128 , 128 );
}

void CBox::Draw(){
	DrawBox( Left , Top , Left + Width , Top + Height , Color , TRUE );
}

//CommandButton::CommandButton(){
//	Left = 32;
//	Top = 32;
//	Width = 32;
//	Height = 32;
//	FontSize = 24;
//	ForeColor = GetColor( 0 , 0 , 0 );
//	BGColor = GetColor( 128 , 128 , 128 );
//}
//
//CommandButton::CommandButton( int _left , int _right , int _width , int _height ){
//	Left = _left;
//	Top = _right;
//	Width = _width;
//	Height = _height;
//	FontSize = 24;
//	ForeColor = GetColor( 0 , 0 , 0 );
//	BGColor = GetColor( 128 , 128 , 128 );
//}
//
//void CommandButton::Draw(){
//	int StringWidth;
//
//	SetFontSize( FontSize );
//	StringWidth = GetDrawFormatStringWidth( "%s" , Caption );
//	DrawBox( Left , Top , Left + Width , Top + Height , BGColor , TRUE );
//	DrawFormatString( Left + ((Width - StringWidth)/2) , Top + ((Height - FontSize)/2) , ForeColor , "%s" , Caption );
//}
//
//void CommandButton::Judge(){
//if( !(GetMouseInput() & MOUSE_INPUT_LEFT) ){
//	return;
//}
//
//	int x;
//	int y;
//	
//	GetMousePoint( &x , &y );
//
//	if ( x > Left && y > Top && x < Left+Width && y < Top + Height ){
//		if( Func != NULL ){
//			Func();
//		} else {
//			Click();
//		}
//	}
//}
//
//void CommandButton::Update(){
//	Draw();
//	Judge();
//}
//
//void CommandButton::Click(){
//
//}
//
//
//
//CCircle::CCircle(){
//	Left = 32;
//	Top = 32;
//	Radius = 8;
//	Color = RED;
//}
//
//void CCircle::Draw(){
//	DrawCircle( Left , Top , Radius , Color , true );
//}
//
//

//Vector GetIntersection( int a1 , int b1 , int a2 , int b2 ){
//	Vector Point;
//
//	if( a1 != a2 ){
//		Point.x = ( b2 - b1 ) / ( a1 - a2 );
//	} else {
//		Point.x = NULL;
//		Point.y = NULL;
//		return Point;
//	}
//
//	Point.y = (a1 * Point.x) + b1;
//
//	return Point;
//}