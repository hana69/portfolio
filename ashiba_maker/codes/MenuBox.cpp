#include"MenuBox.h"
//////////////////////コンストラクタ//////////////////////////////////////

CMenuBox::CMenuBox(const char* _haikeiFile,const char* _selectFile,int _x , int _y , int _cellX , int _cellY,int _cellXNum,int _cellYNum,int _color,int _stringColor){
	
	haikeiFile = _haikeiFile;
	haikeiGraph=0;

	selectFile = _selectFile;
	selectGraph=0;

	x = _x;
	y = _y;

	cellX = _cellX;
	cellY = _cellY;

	cellXNum = _cellXNum;
	cellYNum = _cellYNum;

	color = _color;
	activeColor= _stringColor;
	nonActiveColor = GRAY;

	selectSpot.first = 1;
	selectSpot.second = 1;
	
	selectable=true;

	strMax = 0;

	for(int i=0;i<100;i++){
		str[i] = "";
		active[i]=true;
	}

}
//////////////////////デストラクタ///////////////////

CMenuBox::~CMenuBox(){
	
}

//////////////////////パブリック関数///////////////////////////////////////
void CMenuBox::Selectable(){
	selectable=true;
}
void CMenuBox::UnSelectable(){
	selectable=false;
}

void CMenuBox::Draw(){
	if(haikeiGraph==0 && haikeiFile!=""){
	//	haikeiGraph=LoadGraph( haikeiFile.c_str() );
	}
	if( selectGraph==0 && selectFile!=""){
	//	selectGraph=LoadGraph( selectFile.c_str() );
	}
	DrawFrame();
	if(selectable){
		Select();
	}
}
void CMenuBox::Draw(int _x,int _y){
	if(haikeiGraph==0 && haikeiFile!=""){
//		haikeiGraph=LoadGraph( haikeiFile.c_str() );
	}
	if( selectGraph==0 && selectFile!=""){
//		selectGraph=LoadGraph( selectFile.c_str() );
	}
	DrawFrame(_x,_y);
	if(selectable){
		Select();
	}
}

void CMenuBox::AddNewString(const char* _s){
	if( strMax >= cellXNum*cellYNum ){
		return;
	}

	str[strMax] = _s;
	strMax++;
}
void CMenuBox::AddNewString(const char* _s ,  int _x , int _y ){
	if( _x <= cellXNum && _y <= cellYNum ){
		if(str[(_x-1)*cellYNum+_y-1]==""){
			strMax++;
		}
		str[(_x-1)*cellYNum+_y-1]= _s;
	}
}
void CMenuBox::DeleteString(){
	if(strMax>0){
		strMax--;
		str[strMax] = "";
	}
}

void CMenuBox::NonActive(int _num){
	active[_num]=false;
}
void CMenuBox::Active(int _num){
	active[_num]=true;
}

void CMenuBox::ResetSpot(){
	selectSpot.first=1;
	selectSpot.second=1;
}

bool CMenuBox::Selected(){
	if( Key.Pushed(KEYNAME.ENTER,CKey::DECIDE_SOUND) ||
		Key.Pushed(KEYNAME.Z)       )
	{
		return true;
	}else{
		return false;
	}
}
P CMenuBox::SelectSpot(){
	return selectSpot;
}

std::string CMenuBox::SelectingString(){
	return str[(selectSpot.first-1)*cellYNum+(selectSpot.second-1)];
}

///////////////////////プライベート関数///////////////////////////////////

void CMenuBox::DrawFrame(){
	if(haikeiGraph!=0){
		DrawExtendGraph(x,y,x+cellX*cellXNum,y+cellY*cellYNum,haikeiGraph,true);
	}
	
	for(int i=0;i<cellXNum;i++){
		for(int j=0;j<cellYNum;j++){
			DrawBox( x + i*cellX ,y + j*cellY , x + (i+1)*cellX , y + (j+1)*cellY , color , false);	
		}
	}
	if(selectable){
		if(selectGraph!=0){
			DrawExtendGraph( x+(selectSpot.first-1)*cellX , y+(selectSpot.second-1)*cellY, x+selectSpot.first*cellX , y+selectSpot.second*cellY,selectGraph,true);
		}else{
			DrawBox( x+(selectSpot.first-1)*cellX , y+(selectSpot.second-1)*cellY, x+selectSpot.first*cellX , y+selectSpot.second*cellY,WHITE,true);
		}
	}

	int drawingstrNum=0;
	for(int i=0;i<cellXNum;i++){
		for(int j=0;j<cellYNum;j++){
			if(active[drawingstrNum]){
				DrawFormatString(x+ i*cellX +3, y + (j+0.5)*cellY-7 , activeColor , "%s", str[drawingstrNum].c_str());	
			}else{
				DrawFormatString(x+ i*cellX +3, y + (j+0.5)*cellY-7 , nonActiveColor , "%s", str[drawingstrNum].c_str());	
			}
			drawingstrNum++;	
		}
	}

}
void CMenuBox::DrawFrame(int _x,int _y){
	if(haikeiGraph!=0){
		DrawExtendGraph(_x,_y,_x+cellX*cellXNum,_y+cellY*cellYNum,haikeiGraph,true);
	}
	
	for(int i=0;i<cellXNum;i++){
		for(int j=0;j<cellYNum;j++){
			DrawBox( _x + i*cellX ,_y + j*cellY , _x + (i+1)*cellX , _y + (j+1)*cellY , color , false);	
		}
	}
	if(selectable){
		if(selectGraph!=0){
			DrawExtendGraph( _x+(selectSpot.first-1)*cellX , _y+(selectSpot.second-1)*cellY, _x+selectSpot.first*cellX , _y+selectSpot.second*cellY,selectGraph,true);
		}else{
			DrawBox( _x+(selectSpot.first-1)*cellX , _y+(selectSpot.second-1)*cellY, _x+selectSpot.first*cellX , _y+selectSpot.second*cellY,WHITE,true);
		}
	}

	int drawingstrNum=0;
	for(int i=0;i<cellXNum;i++){
		for(int j=0;j<cellYNum;j++){
			if(active[drawingstrNum]){
				DrawFormatString(_x+ i*cellX +3, _y + (j+0.5)*cellY-7 , activeColor , "%s", str[drawingstrNum].c_str());	
			}else{
				DrawFormatString(_x+ i*cellX +3, _y + (j+0.5)*cellY-7 , nonActiveColor , "%s", str[drawingstrNum].c_str());	
			}
			drawingstrNum++;	
		}
	}

}
bool CMenuBox::Select(){
	
	if( Key.Pushed(KEYNAME.DOWN,CKey::SELECT_SOUND) ||
		Key.Hold(KEYNAME.DOWN,CKey::SELECT_SOUND)     )
	{
		selectSpot.second++;
		if(selectSpot.second > cellYNum){
			selectSpot.second = 1;
		}
	}
	if( Key.Pushed(KEYNAME.UP,CKey::SELECT_SOUND) ||
		Key.Hold(KEYNAME.UP,CKey::SELECT_SOUND)   )
	{
		selectSpot.second--;
		if(selectSpot.second < 1){
			selectSpot.second = cellYNum;
		}
	}

	if( Key.Pushed(KEYNAME.RIGHT,CKey::SELECT_SOUND) ||
		Key.Hold(KEYNAME.RIGHT,CKey::SELECT_SOUND) )
	{
		selectSpot.first++;
		if(selectSpot.first > cellXNum){
			selectSpot.first = 1;
		}
	}
	if( Key.Pushed(KEYNAME.LEFT,CKey::SELECT_SOUND)	||
		Key.Hold(KEYNAME.LEFT,CKey::SELECT_SOUND) )
	{
		selectSpot.first--;
		if(selectSpot.first < 1){
			selectSpot.first = cellXNum;
		}
	}
	
	return false;
}
