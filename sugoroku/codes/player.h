#pragma once

#include "DxLib.h"
#include "Suken.h"
#include "mouse.h"
#include "player.h"
#include "key.h"
#include"card.h"

class CPlayer{
	public:

		void Move( int Num , int Frame , int Time ,int Max, int debugmode);
		void Draw( int scroolX,int scrollY);
		void DrawMini(int frame);
		void Effect(int type,bool piValid , int time,int turn);

		void JudgeGoal(int goal);

		void GetAndReleaseCard(CardType Type,int time,int turn);

		bool PiGot();
		bool PiLost();

		int place;//何マス目にいるか
		int x;//プレイヤーのｘ座標
		int y;//プレイヤーのｙ座標
		Status status;//プレイヤーの状態（一回休みなど)

		int cardGetType;//テキストを表示させるため、カードの手に入れ方を保存しておく
		bool effectEnded;
		int tempTime;

		int playerPic;//プレイヤーの画像
		int miniPic[2];//ミニマップに表示する画像

		int overNum;//ゴールを超えた分の目の数
		bool overFlag;//このターンにゴールを超えるならtrue
		bool returnFlag;//戻っているならtrue

		bool moveEndFlag;

		bool goaled;

		bool piGetFlag;
		bool piLostFlag;

		CCard Card;

		int ranking;

		int cardUseCount;
		int returnStartCount;
		int moveNumCount;

		int bonusPoint[5];
		int totalPoint;

		struct{
			int move;
			int go_three;
			int return_three;
			int stop;
			int return_start;
			int yasumi;
		}sound;
	private:
		
};

class CPlayerManager{
	public:	
		int GetPiNum();

		void Awake();

		void Init(int firatX,int firstY);

		void SetPlace(int Num,int X, int Y );

		void CardEffect(CardType Type,int frame,LoopCase Case,int goal,int debugmode);//カードの効果はプレイヤーに反映されるのでplayermanagerで管理

		void PlayerSelect();//選ばれたプレイヤーはselect.playerに保存

		void SetSpotNum(int turnPlayer);//他のプレイヤーを選ぶときに、自分を除く３人にする

		struct{
			int player;//選ばれたプレイヤー
			int spot;//今選んでいる場所
			bool endFlag;//選択が終わっていればtrue
			int selectSpotPic;//選択場所を示す青緑の四角形
			int spotNum[10];//その場所にどのプレイヤーが割り当てられているか　たとえばプレイヤー１が他のプレイヤーを選ぶ場合[0]=2,[1]=3,[2]=4となる
			CKey Key;
			CMouse Mouse[10];
		}select;

		bool cardSelectedFlag;

		int EndNumSelect();

		void SetTurn();
	
		bool CardIsUsed();

		void Manage(LoopCase Case , int PlaceType , int frame,int time,int DiceNum,int PlaceMax,int debugmode);
		void Draw(int ScrollX , int ScrollY );
		void DrawMini(int ScrollX , int ScrollY,int frame);
		void PlayNumSelect(int frame);
		
		void CardDraw();

		int GetTurn();
		int GetX(int Num);
		int GetY(int Num);
		int GetStatus(int Num);
		int GetPlace(int Num);
		int GetCardEffect();

		bool Get_go_or_return();

		CardType GetUsedCardNum();

		bool CardConfirm();

		bool EffectEnded();

		bool Goaled();

		void DrawNowPlace(int goal);

		void SetRanking(int goal);
		void DrawRanking(int time);

	private:
		
		CardType stoleCard;

		int turn;//どのプレイヤーが行動するか
		int playerMax;//プレイ人数
		int interval;

		void Loop();

		void SetBonusPoint();

		bool cardUsedFlag;//そのターンにカードが使われていたらtrue
		bool cardConfirm;//カードを使うかの確認中はtrue
		bool cardEffect;//カードの効果を反映している間はtrue

		int cursorPic;//プレイヤーの上にある三角の画像

		bool go_or_return;//10進む？カードで進んだか戻ったかを記憶させておく 進んだらtrue　((Txtで文字を書くために必要
		bool canUse;//カードがつかえるかどうか　falseなら使えない 窃盗カードで盗むカードがない場合などに使用

		int temptime;

		int tempRank;

		bool piValid;
		int nowPiRank;

		int drawingLine;
		int nowRanking;
		bool rankPlusFlag;
		
		int resultPic[4];

		int pointPlusSound;

		CMouse PMouse[4];
		CPlayer player[4];
		CKey PKey;
};