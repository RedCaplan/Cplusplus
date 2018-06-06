#pragma once
#include <iostream>
#include <Windows.h>
#include <string>
#include <conio.h>
using namespace std;
class ChessFiguresG
{
protected:
	struct Space
	{
		int StartX;
		int StartY;
		int color1 = 0;
		int color2 = 0;
		string piece = " ";
		int White;
	};
	Space GameField[8][8];

	const int FieldSizeY = 7;
	const int FieldSizeX = 10;
	const char wall = 178;
public:
	void SetColor (int color1 , int color2);
	void SetPos (int x , int y);
	void DrawRook (int x, int y );
	void DrawBishop (int x , int y);
	void DrawKing (int x , int y);
	void DrawQueen (int x , int y);
	void DrawKnight (int x , int y);
	void DrawPawn (int x , int y);
	void DrawMap ( );
	void ClearField (int x , int y);
	void DrawField (string,int i,int j );
	ChessFiguresG ( );
	~ChessFiguresG ( );
};

