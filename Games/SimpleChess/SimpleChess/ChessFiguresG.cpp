#include "ChessFiguresG.h"
#define FieldSizeY 7
#define FieldSizeX 10

ChessFiguresG::ChessFiguresG ( )
{
}
void ChessFiguresG::SetColor (int text , int background)
{
	HANDLE hStdOut = GetStdHandle (STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute (hStdOut , (WORD)( ( background << 4 ) | text ));
}
void ChessFiguresG::SetPos (int x , int y)
{
	HANDLE hwnd = GetStdHandle (STD_OUTPUT_HANDLE);
	COORD pos = { x , y };
	SetConsoleCursorPosition (hwnd , pos);
}
void ChessFiguresG::DrawMap ( )
{
	
	for ( int i = 0; i < FieldSizeX * 8 + 2; i++ )
	{

		SetPos (i , 0);
		cout << wall;
		SetPos (i , FieldSizeY * 8 + 2);
		cout << wall;
	}
	for ( int i = 0; i < FieldSizeY * 8 + 2; i++ )
	{
		SetPos (0 , i);
		cout << wall;
		SetPos (FieldSizeX * 8 + 2 , i);
		cout << wall;
	}
}
void ChessFiguresG::DrawRook (int x , int y)
{

	//char arr[FieldSizeY][FieldSizeX] =
	//{
	//	{ 32 , 32 , 32 , 32 , 32 , 32 , 32 , 32 , 32 , 32 } ,
	//	{ 32 , 32 , 32 , 32 , 32 , 32 , 32 , 32 , 32 , 32 } ,
	//	{ 32 , 32 , 254 , 254 ,254 , 254 , 254 , 32 , 32 , 32 } ,
	//	{ 32 , 32 , 32 , 254 , 254 , 254 , 32 , 32 , 32 , 32 } ,
	//	{ 32 , 32 , 32 , 254 , 254 , 254 , 32 , 32 , 32 , 32 } ,
	//	{ 32 , 32 , 254 , 254 , 254 , 254 , 254 , 32 , 32 , 32 } ,
	//	{ 32 , 32 , 32 , 32 , 32 , 32 , 32 , 32 , 32 , 32 } ,
	//};
	char arr[FieldSizeY][FieldSizeX] =
	{
		{ 32 , 32 , 32 , 32 , 32 , 32 , 32 , 32 , 32 , 32 } ,
		{ 32 , 32 , 32 , 32 , 32 , 32 , 32 , 32 , 32 , 32 } ,
		{ 32 , 32 , 178 , 32 ,178, 32 , 178 , 32 ,  32 } ,
		{ 32 , 32 , 32 , 178 , 178 , 178 , 32 , 32 , 32 , 32 } ,
		{ 32 , 32 , 32 , 178 , 178 , 178 , 32 , 32 , 32 , 32 } ,
		{ 32 , 32 , 178 , 178 , 178 , 178 , 178 ,  32,32 , 32 } ,
		{ 32 , 32 , 32 , 32 , 32 , 32 , 32 , 32 , 32 , 32 } ,
	};
	for ( int i = 0; i < FieldSizeY; i++ )
	{
		SetPos (x , y+i);
		for ( int j = 0; j < FieldSizeX; j++ )
		{
			cout << arr[i][j];
		}
	}
}
void ChessFiguresG::DrawBishop (int x , int y)
{

	//char arr[FieldSizeY][FieldSizeX] =
	//{
	//	{ 32 , 32 , 32 , 32 , 32 , 32 , 32 , 32 , 32 , 32 } ,
	//	{ 32 , 32 , 32 , 32 , 32 , 32 , 32 , 32 , 32 , 32 } ,
	//	{ 32 , 32 , 32 , 32 , 254 , 32 , 32 , 32 , 32 , 32 } ,
	//	{ 32 , 32 , 32 , 254 , 254 , 254 , 32 , 32 , 32 , 32 } ,
	//	{ 32 , 32 , 32 , 178 , 32 , 178 , 32 , 32 , 32 , 32 } ,
	//	{ 32 , 32 , 254 , 254 , 254 , 254 , 254 , 32 , 32 , 32 } ,
	//	{ 32 , 32 , 32 , 32 , 32 , 32 , 32 , 32 , 32 , 32 } ,
	//};
	char arr[FieldSizeY][FieldSizeX] =
	{
		{ 32 , 32 , 32 , 32 , 32 , 32 , 32 , 32 , 32 , 32 } ,
		{ 32 , 32 , 32 , 32 , 32 , 32 , 32 , 32 , 32 , 32 } ,
		{ 32 , 32 , 32 , 32 , 'O' , 32 , 32 , 32 , 32 , 32 } ,
		{ 32 , 32 , 32 , '/' , '|' , '\\' , 32 , 32 , 32 , 32 } ,
		{ 32 , 32 , '.' , '\\' , '|' , '/' , '.' , 32 , 32 , 32 } ,
		{ 32 , 32 , 178 , 178 , 178 , 178 , 178 , 32 , 32 , 32 } ,
		{ 32 , 32 , 32 , 32 , 32 , 32 , 32 , 32 , 32 , 32 } ,
	};
	for ( int i = 0; i < FieldSizeY; i++ )
	{
		SetPos (x , y + i);
		for ( int j = 0; j < FieldSizeX; j++ )
		{
			cout << arr[i][j];
		}
	}
}
void ChessFiguresG::DrawKing (int x , int y)
{

	/*char arr[FieldSizeY][FieldSizeX] =
	{
		{ 32 , 32 , 32 , 32 , 32 , 32 , 32 , 32 , 32 , 32 } ,
		{ 32 , 32 , 32 , 32 , 206 , 32 , 32 , 32 , 32 , 32 } ,
		{ 32 , 32 , 32 , 254 , 254 , 254 , 32 , 32 , 32 , 32 } ,
		{ 32 , 32 , 32 , 254 , 254 , 254 , 32 , 32 , 32 , 32 } ,
		{ 32 , 32 , 32 , 254 , 254 , 254 , 32 , 32 , 32 , 32 } ,
		{ 32 , 32 , 254 , 254 , 254 , 254 , 254 , 32 , 32 , 32 } ,
		{ 32 , 32 , 32 , 32 , 32 , 32 , 32 , 32 , 32 , 32 } ,
	};*/
	char arr[FieldSizeY][FieldSizeX] =
	{
		{ 32 , 32 , 32 , 32 , 32 , 32 , 32 , 32 , 32 , 32 } ,
		{ 32 , 32 , '_' , '_' , 206 , '_' , '_' , 32 , 32 , 32 } ,
		{ 32 , 32 , '\\' , 176 , 177, 176 , '/' , 32 , 32 , 32 } ,
		{ 32 , 32 , 32 , '|' , 177 , '|' , 32 , 32 , 32 , 32 } ,
		{ 32 , 32 , '/' , 177 , 177 , 177 , '\\' , 32 , 32 , 32 } ,
		{ 32 , 32 , 178 , 178 , 178 , 178 , 178 , 32 , 32 , 32 } ,
		{ 32 , 32 , 32 , 32 , 32 , 32 , 32 , 32 , 32 , 32 } ,

	};
	for ( int i = 0; i < FieldSizeY; i++ )
	{
		SetPos (x , y + i);
		for ( int j = 0; j < FieldSizeX; j++ )
		{
			cout << arr[i][j];
		}
	}
}
void ChessFiguresG::DrawQueen (int x , int y)
{

	/*char arr[FieldSizeY][FieldSizeX] =
	{
		{ 32 , 32 , 32 , 32 , 32 , 32 , 32 , 32 , 32 , 32 } ,
		{ 32 , 32 , 32 , 32 , 64 , 32 , 32 , 32 , 32 , 32 } ,
		{ 32 , 32 , 32 , 201 , 254 , 187 , 32 , 32 , 32 , 32 } ,
		{ 32 , 32 , 32 , 254 , 254 , 254 , 32 , 32 , 32 , 32 } ,
		{ 32 , 32 , 32 , 254 , 254 , 254 , 32 , 32 , 32 , 32 } ,
		{ 32 , 32 , 254 , 254 , 254 , 254 , 254 , 32 , 32 , 32 } ,
		{ 32 , 32 , 32 , 32 , 32 , 32 , 32 , 32 , 32 , 32 } ,

	};*/

	char arr[FieldSizeY][FieldSizeX] =
	{
		{ 32 , 32 , 32 , 32 , 32 , 32 , 32 , 32 , 32 , 32 } ,
		{ 32 , 32 , 32 , '_' , 'o' , '_' , 32 , 32 , 32 , 32 } ,
		{ 32 , 32 , '/' , '_' , 177 , '_' , '\\' , 32 , 32 , 32 } ,
		{ 32 , 32 , 32 , '|' , 177 , '|' , 32 , 32 , 32 , 32 } ,
		{ 32 , 32 , '/' , 177 , 177 , 177 , '\\' , 32 , 32 , 32 } ,
		{ 32 , 32 , 178 , 178 , 178 , 178 , 178 , 32 , 32 , 32 } ,
		{ 32 , 32 , 32 , 32 , 32 , 32 , 32 , 32 , 32 , 32 } ,

	};
	for ( int i = 0; i < FieldSizeY; i++ )
	{
		SetPos (x , y + i);
		for ( int j = 0; j < FieldSizeX; j++ )
		{
			cout << arr[i][j];
		}
	}
}
void ChessFiguresG::DrawKnight (int x , int y)
{
	char arr[FieldSizeY][FieldSizeX] =
	{
		{ 32 , 32 , 32 , 32 , 32 , 32 , 32 , 32 , 32 , 32 } ,
		{ 32 , 32 , 32 , 32 , 32 , 32 , 32 , 32 , 32 , 32 } ,
		{ 32 , 32 , 32 , 178 , 178 , 32 , 32 , 32 , 32 , 32 } ,
		{ 32 , 32 , 178 , 111 , 178 , 178 , 32 , 32 , 32 , 32 } ,
		{ 32 , 32 , 32 , 178 , 178 , 178 , 32 , 32 , 32 , 32 } ,
		{ 32 , 32 , 178 , 178 , 178 , 178 , 178 , 32 , 32 , 32 } ,
		{ 32 , 32 , 32 , 32 , 32 , 32 , 32 , 32 , 32 , 32 } ,

	};
	for ( int i = 0; i < FieldSizeY; i++ )
	{
		SetPos (x , y + i);
		for ( int j = 0; j < FieldSizeX; j++ )
		{
			cout << arr[i][j];
		}
	}
}
void ChessFiguresG::DrawPawn (int x , int y)
{

	/*char arr[FieldSizeY][FieldSizeX] =
	{
		{ 32 , 32 , 32 , 32 , 32 , 32 , 32 , 32 , 32 , 32 } ,
		{ 32 , 32 , 32 , 32 , 32 , 32 , 32 , 32 , 32 , 32 } ,
		{ 32 , 32 , 32 , 32 , 32 , 32 , 32 , 32 , 32 , 32 } ,
		{ 32 , 32 , 32 , 254 , 254 , 254 , 32 , 32 , 32 , 32 } ,
		{ 32 , 32 , 32 , 254 , 254 , 254 , 32 , 32 , 32 , 32 } ,
		{ 32 , 32 , 254 , 254 , 254 , 254 , 254 , 32 , 32 , 32 } ,
		{ 32 , 32 , 32 , 32 , 32 , 32 , 32 , 32 , 32 , 32 } ,


	};*/
	char arr[FieldSizeY][FieldSizeX] =
	{
		{ 32 , 32 , 32 , 32 , 32 , 32 , 32 , 32 , 32 , 32 },
		{ 32 , 32 , 32 , 32 , 32 , 32 , 32 , 32 , 32 , 32 } ,
		{ 32 , 32 , '_' , '_' , '_' , '_' , '_' , 32 , 32 , 32 } ,
		{ 32 , 32 , '|' , '_' , 176, '_' , '|' , 32 , 32 , 32 } ,
		{ 32 , 32 , 32 , '/' , 177 , '\\' , 32 , 32 , 32 , 32 } ,
		{ 32 , 32 , 178 , 178 , 178 , 178 , 178 , 32 , 32 , 32 } ,
		{ 32 , 32 , 32 , 32 , 32 , 32 , 32 , 32 , 32 , 32 } ,


	};
	for ( int i = 0; i < FieldSizeY; i++ )
	{
		SetPos (x , y + i);
		for ( int j = 0; j < FieldSizeX; j++ )
		{
			cout << arr[i][j];
		}
	}
}
void ChessFiguresG::ClearField (int x , int y)
{
	for ( int i = 0; i < FieldSizeY; i++ )
	{
		SetPos (x , y + i);
		for ( int j = 0; j < FieldSizeX; j++ )
		{
			cout <<" ";
		}
	}
}
void ChessFiguresG::DrawField (string str,int i,int j)
{

	//Check which piece in current field and then drow 
	if ( str == "Rook" )
		DrawRook (GameField[i][j].StartX , GameField[i][j].StartY);
	if ( str == "Knight" )
		DrawKnight (GameField[i][j].StartX , GameField[i][j].StartY);
	if ( str == "Bishop" )
		DrawBishop (GameField[i][j].StartX , GameField[i][j].StartY);
	if ( str == "Queen" )
		DrawQueen (GameField[i][j].StartX , GameField[i][j].StartY);
	if ( str == "King" )
		DrawKing (GameField[i][j].StartX , GameField[i][j].StartY);
	if ( str == "Pawn" )
		DrawPawn (GameField[i][j].StartX , GameField[i][j].StartY);
	if ( str == " " )
		ClearField (GameField[i][j].StartX , GameField[i][j].StartY);
}
ChessFiguresG::~ChessFiguresG ( )
{
}
