#pragma once
#include <iostream>
#include <windows.h>
using namespace std;
class Player
{

	int PosX;
	int PosY;
	char sign = '@';
	short color1=3;
	short color2=15;
public:
	Player ( );
	Player (int x , int y) :PosX (x) , PosY (y){}
	void DrawPlayer ();
	COORD GetCord ( ) { COORD x = { PosX , PosY }; return x; }
	void SetColor2 (int _color2){ color2 = _color2; }
	void SetColor1 (int _color1){ color1 = _color1; }
	int GetColor1 ( ){ return color1; }
	void SetSign (char _sign){ sign = _sign; }
	void SetCord (int x , int y){ PosX = x; PosY = y; }
	char GetHeroSign ( ){ return sign; }
	~Player ( );
};

