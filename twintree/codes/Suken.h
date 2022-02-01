#pragma once

#include<string>
/////ゲーム用定数/////
enum Element{
	NO_ELEMENT,
	FIRE,
	ICE,
	WIND,
	THUNDER,
	ELEMENT_MAX
};
static std::string ElementString[ELEMENT_MAX]={
	"無",
	"炎",
	"氷",
	"風",
	"雷"
};
enum Parameter{
	P_ATK,
	P_GARD,
	M_ATK,
	M_GARD,
	SPEED
};
static const std::string parameterS[SPEED+1]={
	"こうげき力",
	"ぼうぎょ力",
	"魔法こうげき力",
	"魔法ぼうぎょ力",
	"すばやさ"
};

enum BadStatus{
	NO_BST,
	YAKEDO,
	TOUSYOU,
	RESSYOU,
	MAHI,
	DOKU,
	NEMURI,
	MAHUU,
};
static const std::string bstString[MAHUU+1]={
	"なし",
	"火傷",
	"凍傷",
	"裂傷",
	"麻痺",
	"毒",
	"眠り",
	"魔封"
};
static const std::string bstMessage[MAHUU+1]={
	"",
	"は火傷（やけど）をおった",
	"は凍傷（とうしょう）になった",
	"は裂傷（れっしょう）をおった",
	"は麻痺（まひ）した",
	"は毒（どく）におかされた",
	"はねむってしまった",
	"は魔法（まほう）をふうじられた"

};
static const std::string bstRecoverMessage[MAHUU+1]={
	"",
	"の火傷（やけど）がなおった",
	"の凍傷（とうしょう）がなおった",
	"の裂傷（れっしょう）がなおった",
	"の麻痺（まひ）がなおった",
	"の毒（どく）がぬけた",
	"はねむりからめざめた",
	"の魔封（まふう）はとけた"
};
static const std::string bstEffectMessage[MAHUU+1]={
	"",
	"は火傷（やけど）によるダメージをうけた",
	"は凍傷（とうしょう）によるダメージをうけた",
	"は裂傷（れっしょう）によるダメージをうけた",
	"は麻痺（まひ）している",
	"は毒（どく）によるダメージをうけた",
	"はねむっている",
	"は魔法をふうじられている"
};
static double BuffPercent(int _num){
	switch(_num){
	case 5:
		return 2.7;
		break;
	case 4:
		return 2.4;
		break;
	case 3:
		return 2.0;
		break;
	case 2:
		return 1.7;
		break;
	case 1:
		return 1.3;
		break;
	case 0:
		return 1.0;
		break;
	case -1:
		return 1.0/1.3;
		break;
	case -2:
		return 1.0/1.7;
		break;
	case -3:
		return 1.0/2.0;
		break;
	case -4:
		return 1.0/2.4;
		break;
	case -5:
		return 1.0/2.7;
		break;
	}
	return 1.0;
}

//////////////////数研ライブラリver0

#define IDI_ICON1 101

#define WINDOW_WIDTH 752
#define WINDOW_HEIGHT 480

#define RED GetColor( 255 , 0 , 0 )
#define GREEN GetColor( 0 , 255 , 0 )
#define BLUE GetColor( 0 , 0 , 255 )
#define BLACK GetColor( 0 , 0 , 0 )
#define WHITE GetColor( 255 , 255 , 255 )
#define GRAY GetColor( 128 , 128 , 128 )
#define YELLOW GetColor( 255 , 255 , 0)
#define LIGHTBLUE GetColor( 128 , 255 , 255 )
#define PURPLE GetColor( 128 , 0 , 128)
#define BROWN GetColor(128,64,0)

////////////////////////////////////////////////////////////////
class CBox{
public:
	CBox();
	CBox( int _Left , int _Top , int _Width , int _Height , int Color );

	int Left;
	int Top;
	int Width;
	int Height;
	int Color;

	void Draw();
private:
	
};

class CCommandButton{
public:
	CCommandButton();
	CCommandButton( int _left , int _right , int _width , int _height );
	int Left;
	int Top;
	int Width;
	int Height;
	int ForeColor;
	int BGColor; //BackGroundColor
	int FontSize;

	char *Caption;

	void (*Func)();

	void Update();
	void Draw();
	void Judge();
	void Click();
private:
};

class CIntData{///マイナスには未対応
public:
	//数字を2000(行) *2(左右) =4000個分を
	//テキストに保存、及び読み込み出来るクラスです。
	//まず、クラスを作成時に、読み込むファイル名を代入して
	//ReadData で、読み込み（4000個全て）
	//WriteData　で、書き込み（4000個全て）
	//NewMakeで、新規作成またはファイルの初期化をします
	//ReadData で、ファイルが読み込めなかった場合、
	//自動的に新しくファイルを作成します
	CIntData(char *_DataName);
	char *DataName;
	void NewMake();
	void WriteData();
	void ReadData();
	int RightData[2000];
	int CenterData[2000];
	int LeftData[2000];
};

/*
class ObjectManager{
public:
	ObjectManager();
	void Update();
	void Add( void *fucntion() );
private:
	void* *p;
	int Counter;
};

void AddObject( void *fucntion() );
*/

void KEYCHECK(char &CC , bool INPUT );

class CKeyPush{
public:
	char BACK;//KEY_INPUT_BACK  // バックスペースキー 
	char TAB;//KEY_INPUT_TAB  // タブキー 
	char RETURN;//KEY_INPUT_RETURN  // エンターキー
	char LSHIFT;//KEY_INPUT_LSHIFT  // 左シフトキー 
	char RSHIFT;//KEY_INPUT_RSHIFT  // 右シフトキー 
	char LCONTROL;//KEY_INPUT_LCONTROL  // 左コントロールキー 
	char RCONTROL;//KEY_INPUT_RCONTROL  // 右コントロールキー 
	char ESCAPE;//KEY_INPUT_ESCAPE  // エスケープキー 
	char SPACE;//KEY_INPUT_SPACE  // スペースキー 
	char LEFT;//KEY_INPUT_LEFT  // 左キー 
	char UP;//KEY_INPUT_UP  // 上キー 
	char RIGHT;//KEY_INPUT_RIGHT  // 右キー 
	char DOWN;//KEY_INPUT_DOWN  // 下キー 
	char INSERT;//KEY_INPUT_INSERT  // インサートキー 
	char Delete;//KEY_INPUT_DELETE  // デリートキー
	char LALT;//KEY_INPUT_LALT  // 左ＡＬＴキー 
	char RALT;//KEY_INPUT_RALT  // 右ＡＬＴキー 
	char SCROLL;//KEY_INPUT_SCROLL  // ScrollLockキー
	char CAPSLOCK;//KEY_INPUT_CAPSLOCK  // CaspLockキー 
	char PAUSE;//KEY_INPUT_PAUSE  // PauseBreakキー
	char MINUS ; // －キー 
	char YEN ;  // ￥キー 
	char PREVTRACK ; // ＾キー 
	char PERIOD ; // ．キー 
	char SLASH ; // ／キー 
	char SEMICOLON ; // ；キー 
	char COLON ; // ：キー 
	char LBRACKET ; // ［キー 
	char RBRACKET ; // ］キー 
	char AT ; // ＠キー 
	char BACKSLASH ; // ＼キー 
	char COMMA ; // ，キー 
	char F1 ; // Ｆ１キー 
	char F2 ; // Ｆ２キー 
	char F3 ; // Ｆ３キー 
	char F4 ; // Ｆ４キー 
	char F5 ; // Ｆ５キー 
	char F6 ; // Ｆ６キー 
	char F7 ; // Ｆ７キー 
	char F8 ; // Ｆ８キー 
	char F9 ; // Ｆ９キー 
	char F10 ; // Ｆ１０キー 
	char F11 ; // Ｆ１１キー 
	char F12 ; // Ｆ１２キー
	char A ; // Ａキー 
	char B ; // Ｂキー 
	char C ; // Ｃキー 
	char D ; // Ｄキー 
	char E ; // Ｅキー 
	char F ; // Ｆキー 
	char G ; // Ｇキー 
	char H ; // Ｈキー 
	char I ; // Ｉキー 
	char J ; // Ｊキー 
	char K ; // Ｋキー 
	char L ; // Ｌキー 
	char M ; // Ｍキー 
	char N ; // Ｎキー 
	char O ; // Ｏキー 
	char P ; // Ｐキー 
	char Q ; // Ｑキー 
	char R ; // Ｒキー 
	char S ; // Ｓキー 
	char T ; // Ｔキー 
	char U ; // Ｕキー 
	char V ; // Ｖキー 
	char W ; // Ｗキー 
	char X ; // Ｘキー 
	char Y ; // Ｙキー 
	char Z ; // Ｚキー 
	char Key0 ; // ０キー 
	char Key1 ; // １キー 
	char Key2 ; // ２キー 
	char Key3 ; // ３キー 
	char Key4 ; // ４キー 
	char Key5 ; // ５キー 
	char Key6 ; // ６キー 
	char Key7 ; // ７キー 
	char Key8 ; // ８キー 
	char Key9 ; // ９キー 
	void ALLKEYCHECK();
};