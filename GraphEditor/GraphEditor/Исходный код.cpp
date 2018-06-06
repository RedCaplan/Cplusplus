#include "GraphEditor.h"
#include "Menu\Menu.h"
void SetPos (int x , int y)
{
	COORD position = { x , y }; //позиция x и y
	HANDLE hConsole = GetStdHandle (STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition (hConsole , position);
}
int main ( )
{
	Menu Menu_Obj;
	GraphEditor obj;
	int Selection=1;
	while ( Selection!=4 )
	{ 
		Selection = Menu_Obj.Show ();
		if ( Selection == 0 ){ obj = obj.AddGraph ( ); obj.InitializeArray ( ); }
		if ( Selection == 1 ) obj.SetLink ();
		if ( Selection == 2 ){
			obj.dijkstra ( ); SetPos (180 , 50); system ("pause");
			SetPos (180 , 50); cout << "\t\t\t";
		}
		if ( Selection == 3 ){ obj.SetSize(1); }
	
		obj.ShowArrayTable ();
		obj.ShowLinks ();
	}
	SetPos (20 , 40);
	system ("pause");
}