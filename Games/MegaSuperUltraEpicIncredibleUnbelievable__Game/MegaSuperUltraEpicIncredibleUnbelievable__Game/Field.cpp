#include "Field.h"


Field::Field ( )
{
	InitializeFields ( );
}
void Field::InitializeFields ( )
{
	sign = ' ';
	color1 = 0;
	color2 = 15;
	PosX = 0;
	PosY = 0;
}
void Field::DrawField ( )
{
	HANDLE hCon;
	COORD cPos;
	cPos.X = PosX;
	cPos.Y = PosY;
	hCon = GetStdHandle (STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition (hCon , cPos);
	SetColor (color1 , color2);

	cout << sign;
}
void Field::SetColor (int text , int background)
{
	HANDLE hStdOut = GetStdHandle (STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute (hStdOut , (WORD)( ( background << 4 ) | text ));
}

Field::~Field ( )
{
}
