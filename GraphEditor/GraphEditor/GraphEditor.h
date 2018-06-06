#pragma once
#include <iostream>
#include <conio.h>
#include <Windows.h>
using namespace std;

class GraphEditor
{
	int size=1;
	COORD* GraphArr;
	int** arr;
public:
	GraphEditor ( );
	GraphEditor (int _size , COORD* _GraphArr) :size (_size) , GraphArr (_GraphArr){};
	void SetSize (int _size){ size = _size; }
	void DrawGraphs ( );
	void SetColor (int color1 , int color2);
	void SetPos (COORD obj );
	void SetPos (int x,int y);
	void InitializeArray ( );
	void ShowArrayTable ( );
	void InitializeArray (int** arr);
	int** GetArr ( ){ return arr; }
	void SetLink ( );
	void ShowLinks ( );
	void ShowLink (int i,int j );
	void dijkstra ( );
	GraphEditor AddGraph ();
	GraphEditor operator=( GraphEditor& obj );
	~GraphEditor ( );
};

