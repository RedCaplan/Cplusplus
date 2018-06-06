#include "Player.h"


Player::Player ( )
{
}
void Player::DrawPlayer ()
{
	HANDLE hStdOut = GetStdHandle (STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute (hStdOut , (WORD)( ( color2 << 4 ) | color1 ));
	HANDLE hCon;
	COORD cPos = { PosX , PosY };
	hCon = GetStdHandle (STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition (hCon , cPos);
	cout << sign;

}

Player::~Player ( )
{
}
