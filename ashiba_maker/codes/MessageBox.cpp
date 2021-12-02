#include"MessageBox.h"

/////////////////////�R���X�g���N�^/////////////////////
CMessageBox::CMessageBox(int _x , int _y , int _width , int _height){
	x=_x;
	y=_y;

	width =_width;
	height=_height;
	for(int i=0;i<5;i++){
		message[i] = "";
	}
	lineNum=0;

	limitX = width/17*2;
	limitY = height/20;
}

////////////////////�p�u���b�N�֐�//////////////////////
void CMessageBox::Draw()
{
	
	int nowStrLong=message[lineNum].size();
	int amari=0;
	std::string temp_s;
	
	while( nowStrLong > limitX ){//���������E�𒴂��Ă���ꍇ���̕������̍s�ֈڂ�
		amari=nowStrLong-limitX;
		temp_s = message[lineNum].substr((nowStrLong-amari+1)/2*2,amari);
		message[lineNum].erase((nowStrLong-amari+1)/2*2,amari);
		StartNewLine();
		message[lineNum]=temp_s;
		nowStrLong = message[lineNum].size();
	}

	DrawBox( x , y , x+width , y+height , BLACK , true );//�g���̓���
	DrawBox( x , y , x+width , y+height , GRAY , false );//�g��

	for(int i=0;i<=lineNum;i++){
		DrawString(x,y+3+i*20,message[i].c_str(),WHITE);//����
	}
	
}

void CMessageBox::Call(const char* _str){
	Delete();
	message[lineNum] = _str;
	active = true;
}

void CMessageBox::Add(const char* _str){
	message[lineNum] += _str;
	active=true;
}

void CMessageBox::Delete(){
	for(int i=0;i<=lineNum;i++){
		message[i]="";
	}
	active=false;
	lineNum=0;
}

void CMessageBox::StartNewLine(){
	
	if( lineNum < limitY-1 ){
		lineNum++;
	}else{
		for(int i=0;i<limitY-1;i++){
			message[i]=message[i+1];
		}
	}
}

void CMessageBox::SetLimitX(int _x){
	if( _x < width/17 ){
		limitX=_x*2;
	}
}
void CMessageBox::SetLimitY(int _y){
	if( _y < height/20 ){
		limitY=_y;
	}
}