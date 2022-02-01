#pragma once

#include"DxLib.h"
#include"Suken.h"

class CTxt{
	public:
		void EffectDraw( int type);
		void CardEffectDraw(CardType CardType,int piNum,bool go_or_return=false);
		void CardConfirmDraw();
		void Draw( int player , int Case , int Num , int time );
};