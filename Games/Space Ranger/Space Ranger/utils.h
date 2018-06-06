#pragma once

#include <windows.h>
#include <conio.h>
#include <iostream>
static void GoToXY (int x , int y)
{
	COORD pos = { x , y };
	HANDLE output = GetStdHandle (STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition (output , pos);
}

static void HideCursor (void)
{
	void* handle = GetStdHandle (STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO structCursorInfo;
	GetConsoleCursorInfo (handle , &structCursorInfo);
	structCursorInfo.bVisible = FALSE;
	SetConsoleCursorInfo (handle , &structCursorInfo);
}

static bool RandomDecision (int prob)
{
	int aux = rand () % 100;
	return ( aux <= prob );
}

static int RandomInt (int min , int max)
{
	int aux = ( rand () % ( max - min ) ) + min;
	return aux;
}

static void Color (int text , int background)
{
	HANDLE hStdOut = GetStdHandle (STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute (hStdOut , (WORD)( ( background << 4 ) | text ));
}
static void Color (int text)
{
	SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE) , text);
}