#pragma once
#include <iostream>
#include <conio.h>
#include <ctime>
#include <Windows.h>

using namespace std;
class Field
{
	char sign;
	int PosX;
	int PosY;
	int color1;
	int color2;
	bool canChange = 1;
public:
	Field ( );
	void DrawField ( );
	void SetPos (int x , int y){ PosX = x; PosY = y; }
	void SetColor (int text,int background );
	void SetColorsField (int _color1 , int _color2){ color1 = _color1; color2 = _color2; }
	void InitializeFields ( );
	int GetColor2 ( ){ return color2; }
	int GetColor1 (){ return color1; }
	bool CanChange ( ){ return canChange; }
	void setCanChange (bool arg){ canChange = arg; }
	void SetSign (char _sign){ sign = _sign; }
	char GetSign ( ){ return sign; }
	int GetPosX (){ return PosX; }
	int GetPosY (){ return PosY; }
	~Field ( );
};

