#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <Windows.h>
#include <conio.h>
using namespace std;
struct Pointer
{
	string str;
	int point, x, y, color1 = 12, color2 = 0;
};

class Menu
{
	int size = 0;	
	Pointer* arr;
	int Interval=3;
	int LetInterval=2;
	int startX;
	int startY;
	COORD* border;
	int widthBord;
	int lengthBord;
public:
	Menu();
	Pointer* AddPoint();
	Pointer* AddPoint(const char* str);
	Pointer* RemovePoint(int i);
	Pointer* EditPoint(int i);
	void SetPointerArr(Pointer* _arr) { arr = _arr; }
	void SetColor(int color1, int color2);
	void SetPos(int x, int y);
	void SetCompletePos(int x, int y);
	int Show();
	void SetBorder();
	void SaveFile();
	int LoadFile();
	int GetSize() { return size; }
	~Menu();
};

