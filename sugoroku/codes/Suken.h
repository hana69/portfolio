#pragma once

#include<string>

//////////////////�������C�u����ver0

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

//�}�X�֌W
#define GO_AHEAD GREEN 
#define GO_BACK RED
#define REST LIGHTBLUE
#define RETURN_START PURPLE
#define GET_CARD YELLOW
#define STOP GRAY
#define GOAL BROWN
#define BRANK BLACK
#define START BLUE

/////////////////////////Case�֌W///////////////////////////////////
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

///////////////////////�J�[�h�֌W//////////////////////////
enum CardType{//�J�[�h�̎��
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
	"[�󂫃X���b�g]",
	"1�i�ރJ�[�h",
	"2�i�ރJ�[�h",
	"3�i�ރJ�[�h",
	"4�i�ރJ�[�h",
	"5�i�ރJ�[�h",
	"6�i�ރJ�[�h",
	"10�i��?�J�[�h",
	"�ޓ��J�[�h",
	"�΃J�[�h",
};

const std::string CARD_TXT[CARD_TYPE_MAX] = {
	"�����ɂ̓J�[�h������܂���",
	"�P�}�X�i�ރJ�[�h�ł��@���i�񂾃}�X�̎w���ɂ͏]���܂���",
	"�Q�}�X�i�ރJ�[�h�ł��@���i�񂾃}�X�̎w���ɂ͏]���܂���",
	"�R�}�X�i�ރJ�[�h�ł��@���i�񂾃}�X�̎w���ɂ͏]���܂���",
	"�S�}�X�i�ރJ�[�h�ł��@���i�񂾃}�X�̎w���ɂ͏]���܂���",
	"�T�}�X�i�ރJ�[�h�ł��@���i�񂾃}�X�̎w���ɂ͏]���܂���",
	"�U�}�X�i�ރJ�[�h�ł��@���i�񂾃}�X�̎w���ɂ͏]���܂���",
	"�P�O�}�X�i�ނ��߂�J�[�h�ł��@���i��/�߂����}�X�̎w���ɂ͏]���܂���",
	"���̃v���C���[�̃J�[�h�𓐂ރJ�[�h�ł��@�������ł͐ޓ��͔ƍ߂ł�",
	"�ꖇ�����Q�b�g�ł��Ȃ����̃J�[�h�B�g���Ă��Ȃ��Ȃ�Ȃ�"
};

const char piNum[100]="3141592653589793238462643383279502884197169399375105820";

enum ConfirmCase{//�����m�F����̂�
	USE,    //�g�����̊m�F�@�u�{���ɂ��̃J�[�h���g���܂����H�v
	RELEASE,//�̂Ă鎞�̊m�F�@�u�{���ɂ��̃J�[�h���̂Ă܂����H�v
	GET,    //�Q�b�g�������ɏ����g�����܂��Ă����ꍇ�̊m�F�@�u���߂�v���A�u�J�[�h���̂Ă�v
	CONFIRMCASE_MAX
};


	
#define SPOTMAX 5
//�J�[�h��V�����Q�b�g�������ɁA���̃J�[�h���ǂ�������
#define NOT_RELEASE 1//�󂫂��������̂ŉ����̂ĂȂ�����
#define RELEASE_NEW_CARD 2 //�V�����Q�b�g�����J�[�h���̂Ă�
#define	RELEASE_OLD_CARD 3//���X�������J�[�h���̂Ă�

////////////////////�v���C���[�֌W//////////////////////////

enum Status{
	NORMAL_S,
	REST_S,
	STOP_S,
};

//////////////////////�T�C�R���֌W///////////////////////////
#define DICE_X 540
#define DICE_Y 380

///////////////////////�Q�b�^�[�p////////////////////////////

#define TURN 10

///////////////////////�}�b�v�֌W/////////////////////////
#define DATAWIDTH 40
#define DATAHIGHT 40

#define MAPMAX 7

#define SCROLLSPEED 3
#define SC_LIMIT_LEFT 200
#define SC_LIMIT_RIGHT 1250
#define SC_LIMIT_TOP 300
#define SC_LIMIT_BOTTOM 950

////////////////////////�I��p//////////////////////////////////

#define SELECTINTERVAL 10
#define ENTERTIME 60

/////////////////////////���֌W//////////////////////////////

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

class CIntData{///�}�C�i�X�ɂ͖��Ή�
public:
	//������2000(�s) *2(���E) =4000����
	//�e�L�X�g�ɕۑ��A�y�ѓǂݍ��ݏo����N���X�ł��B
	//�܂��A�N���X���쐬���ɁA�ǂݍ��ރt�@�C������������
	//ReadData �ŁA�ǂݍ��݁i4000�S�āj
	//WriteData�@�ŁA�������݁i4000�S�āj
	//NewMake�ŁA�V�K�쐬�܂��̓t�@�C���̏����������܂�
	//ReadData �ŁA�t�@�C�����ǂݍ��߂Ȃ������ꍇ�A
	//�����I�ɐV�����t�@�C�����쐬���܂�
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
	char BACK;//KEY_INPUT_BACK  // �o�b�N�X�y�[�X�L�[ 
	char TAB;//KEY_INPUT_TAB  // �^�u�L�[ 
	char RETURN;//KEY_INPUT_RETURN  // �G���^�[�L�[
	char LSHIFT;//KEY_INPUT_LSHIFT  // ���V�t�g�L�[ 
	char RSHIFT;//KEY_INPUT_RSHIFT  // �E�V�t�g�L�[ 
	char LCONTROL;//KEY_INPUT_LCONTROL  // ���R���g���[���L�[ 
	char RCONTROL;//KEY_INPUT_RCONTROL  // �E�R���g���[���L�[ 
	char ESCAPE;//KEY_INPUT_ESCAPE  // �G�X�P�[�v�L�[ 
	char SPACE;//KEY_INPUT_SPACE  // �X�y�[�X�L�[ 
	char LEFT;//KEY_INPUT_LEFT  // ���L�[ 
	char UP;//KEY_INPUT_UP  // ��L�[ 
	char RIGHT;//KEY_INPUT_RIGHT  // �E�L�[ 
	char DOWN;//KEY_INPUT_DOWN  // ���L�[ 
	char INSERT;//KEY_INPUT_INSERT  // �C���T�[�g�L�[ 
	char Delete;//KEY_INPUT_DELETE  // �f���[�g�L�[
	char LALT;//KEY_INPUT_LALT  // ���`�k�s�L�[ 
	char RALT;//KEY_INPUT_RALT  // �E�`�k�s�L�[ 
	char SCROLL;//KEY_INPUT_SCROLL  // ScrollLock�L�[
	char CAPSLOCK;//KEY_INPUT_CAPSLOCK  // CaspLock�L�[ 
	char PAUSE;//KEY_INPUT_PAUSE  // PauseBreak�L�[
	char MINUS ; // �|�L�[ 
	char YEN ;  // ���L�[ 
	char PREVTRACK ; // �O�L�[ 
	char PERIOD ; // �D�L�[ 
	char SLASH ; // �^�L�[ 
	char SEMICOLON ; // �G�L�[ 
	char COLON ; // �F�L�[ 
	char LBRACKET ; // �m�L�[ 
	char RBRACKET ; // �n�L�[ 
	char AT ; // ���L�[ 
	char BACKSLASH ; // �_�L�[ 
	char COMMA ; // �C�L�[ 
	char F1 ; // �e�P�L�[ 
	char F2 ; // �e�Q�L�[ 
	char F3 ; // �e�R�L�[ 
	char F4 ; // �e�S�L�[ 
	char F5 ; // �e�T�L�[ 
	char F6 ; // �e�U�L�[ 
	char F7 ; // �e�V�L�[ 
	char F8 ; // �e�W�L�[ 
	char F9 ; // �e�X�L�[ 
	char F10 ; // �e�P�O�L�[ 
	char F11 ; // �e�P�P�L�[ 
	char F12 ; // �e�P�Q�L�[
	char A ; // �`�L�[ 
	char B ; // �a�L�[ 
	char C ; // �b�L�[ 
	char D ; // �c�L�[ 
	char E ; // �d�L�[ 
	char F ; // �e�L�[ 
	char G ; // �f�L�[ 
	char H ; // �g�L�[ 
	char I ; // �h�L�[ 
	char J ; // �i�L�[ 
	char K ; // �j�L�[ 
	char L ; // �k�L�[ 
	char M ; // �l�L�[ 
	char N ; // �m�L�[ 
	char O ; // �n�L�[ 
	char P ; // �o�L�[ 
	char Q ; // �p�L�[ 
	char R ; // �q�L�[ 
	char S ; // �r�L�[ 
	char T ; // �s�L�[ 
	char U ; // �t�L�[ 
	char V ; // �u�L�[ 
	char W ; // �v�L�[ 
	char X ; // �w�L�[ 
	char Y ; // �x�L�[ 
	char Z ; // �y�L�[ 
	char Key0 ; // �O�L�[ 
	char Key1 ; // �P�L�[ 
	char Key2 ; // �Q�L�[ 
	char Key3 ; // �R�L�[ 
	char Key4 ; // �S�L�[ 
	char Key5 ; // �T�L�[ 
	char Key6 ; // �U�L�[ 
	char Key7 ; // �V�L�[ 
	char Key8 ; // �W�L�[ 
	char Key9 ; // �X�L�[ 
	void ALLKEYCHECK();
};