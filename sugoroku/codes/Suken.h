#pragma once

#include<string>

//////////////////数研ライブラリver0

#define IDI_ICON1 101

#define WINDOW_WIDTH 640
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

//マス関係
#define GO_AHEAD GREEN 
#define GO_BACK RED
#define REST LIGHTBLUE
#define RETURN_START PURPLE
#define GET_CARD YELLOW
#define STOP GRAY
#define GOAL BROWN
#define BRANK BLACK
#define START BLUE

/////////////////////////Case関係///////////////////////////////////
#define MAXCASE 5
#define MENUCASE 10
#define HOWTOCase 20
#define MAPLOOKCASE 30


enum SelectCase{
	NOT_SELECT,
	TITLE,
	SELECT_PLAYNUM,
	SELECT_STAGE,
};

const SelectCase minus1_S[4] ={
	NOT_SELECT,
	TITLE,
	TITLE,
	SELECT_PLAYNUM,
};

enum LoopCase{
	NOT_LOOP,
	JUDGE_STATUS,
	SELECT_MOVEMENT,
	USE_CARD,
	ROLL_DICE,
	MOVE,
	DRAW_TEXT,
	EFFECT,
	JUDGE_GOAL
};

enum MenuCase{
	NOT_MENU,
	MENU,
	MAPLOOK,
};

enum HowToCase{
	NOT_HOWTO,
	HOWTO_1,
	HOWTO_2
};

enum ResultCase{
	NOT_RESULT,
	CELEBRATE_GOAL,
	RANKING
};

enum OptionCase{
	NOT_OPTION,
	OPTION
};

const LoopCase plus1_L[9]={
	JUDGE_STATUS,
	SELECT_MOVEMENT,
	USE_CARD,
	ROLL_DICE,
	MOVE,
	DRAW_TEXT,
	EFFECT,
	JUDGE_GOAL,
	JUDGE_STATUS
};

const LoopCase minus1_L[8]={
	NOT_LOOP,
	JUDGE_STATUS,
	JUDGE_STATUS,
	SELECT_MOVEMENT,
	SELECT_MOVEMENT,
	ROLL_DICE,
	MOVE,
	DRAW_TEXT,
};

///////////////////////カード関係//////////////////////////
enum CardType{//カードの種類
	NO_CARD,
	GO_ONE,
	GO_TWO,
	GO_THREE,
	GO_FOUR,
	GO_FIVE,
	GO_SIX,
	GO_TEN_OR_RETURN_TEN,
	STEAL,
	PI,
	CARD_TYPE_MAX
};

const std::string CARD_NAME[CARD_TYPE_MAX] = {
	"[空きスロット]",
	"1進むカード",
	"2進むカード",
	"3進むカード",
	"4進むカード",
	"5進むカード",
	"6進むカード",
	"10進む?カード",
	"窃盗カード",
	"πカード",
};

const std::string CARD_TXT[CARD_TYPE_MAX] = {
	"ここにはカードがありません",
	"１マス進むカードです　※進んだマスの指示には従いません",
	"２マス進むカードです　※進んだマスの指示には従いません",
	"３マス進むカードです　※進んだマスの指示には従いません",
	"４マス進むカードです　※進んだマスの指示には従いません",
	"５マス進むカードです　※進んだマスの指示には従いません",
	"６マス進むカードです　※進んだマスの指示には従いません",
	"１０マス進むか戻るカードです　※進んだ/戻ったマスの指示には従いません",
	"他のプレイヤーのカードを盗むカードです　※現実では窃盗は犯罪です",
	"一枚しかゲットできない幻のカード。使ってもなくならない"
};

const char piNum[100]="3141592653589793238462643383279502884197169399375105820";

enum ConfirmCase{//何を確認するのか
	USE,    //使う時の確認　「本当にこのカードを使いますか？」
	RELEASE,//捨てる時の確認　「本当にこのカードを捨てますか？」
	GET,    //ゲットした時に所持枠が埋まっていた場合の確認　「諦める」か、「カードを捨てる」
	CONFIRMCASE_MAX
};


	
#define SPOTMAX 5
//カードを新しくゲットした時に、そのカードをどうしたか
#define NOT_RELEASE 1//空きがあったので何も捨てなかった
#define RELEASE_NEW_CARD 2 //新しくゲットしたカードを捨てた
#define	RELEASE_OLD_CARD 3//元々あったカードを捨てた

////////////////////プレイヤー関係//////////////////////////

enum Status{
	NORMAL_S,
	REST_S,
	STOP_S,
};

//////////////////////サイコロ関係///////////////////////////
#define DICE_X 540
#define DICE_Y 380

///////////////////////ゲッター用////////////////////////////

#define TURN 10

///////////////////////マップ関係/////////////////////////
#define DATAWIDTH 40
#define DATAHIGHT 40

#define MAPMAX 7

#define SCROLLSPEED 3
#define SC_LIMIT_LEFT 200
#define SC_LIMIT_RIGHT 1250
#define SC_LIMIT_TOP 300
#define SC_LIMIT_BOTTOM 950

////////////////////////選択用//////////////////////////////////

#define SELECTINTERVAL 10
#define ENTERTIME 60

/////////////////////////音関係//////////////////////////////

enum SoundType{
	TITLE_SOUND,
	SUGOROKU_SOUND,
	RESULT_SOUND
};

#define BGMMAX 3

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