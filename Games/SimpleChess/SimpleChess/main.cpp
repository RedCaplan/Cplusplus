#include "ChessFiguresG.h"
#include "ChessGame.h"
int main ( )
{
	ChessGame obj;
	COORD coord;
	SetConsoleDisplayMode (GetStdHandle (STD_OUTPUT_HANDLE) , CONSOLE_FULLSCREEN_MODE , &coord);

	//obj.DrawRook ();
	//obj.DrawBishop ();
	//obj.DrawKing ( );
	//obj.DrawQueen ( );
	//obj.DrawKnight ( );
	//obj.DrawPawn ();

	
	obj.DrawMap ( );
	obj.DrawAllPieces ();
	while ( 1 )
	{
		obj.Walk ( );
		obj.Move ( );
		obj.DrawAllPieces ( );
	}
	system ("pause");
}