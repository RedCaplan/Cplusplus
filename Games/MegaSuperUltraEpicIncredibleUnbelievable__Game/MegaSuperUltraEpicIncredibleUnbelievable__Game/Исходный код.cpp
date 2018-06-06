#pragma comment(lib,"Winmm.lib")
#define _CRT_SECURE_NO_WARNINGS
#include "Map.h"

// Состояние меню
bool isActive = 1;
bool MainMenu = 1;
bool PlayMenu = 0;
bool Create_Menu = 0;
bool Load_Menu = 0;
//bool Profile_Menu = 0;

//Консоль на весь экран
void render_window (){
	COORD dummy;
	bool ret = SetConsoleDisplayMode (GetStdHandle (STD_OUTPUT_HANDLE) , 1 , &dummy);
}  //Консоль на весь экран 

//Установить Цвет текста/Положение Курсора
void SetColor (int text , int background)
{
	HANDLE hStdOut = GetStdHandle (STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute (hStdOut , (WORD)( ( background << 4 ) | text ));
}
void SetCursor (int x , int y)
{
	HANDLE hCon;
	COORD cPos = { x , y };
	hCon = GetStdHandle (STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition (hCon , cPos);
}
//Движение в меню создания
void MoveCreator (char action , int length , int width , Map& Game)
{
	
	int CurPosY = Game.GetHeroPosY ();
	int CurPosX = Game.GetHeroPosX ();

	SetCursor (CurPosX , CurPosY);
    cout << " ";
	
	switch ( action )
	{
		case 'w': if ( CurPosY > 2 )
			SetCursor (CurPosX , --CurPosY); break;
		case 's':if ( CurPosY < width-3 )
			SetCursor (CurPosX , ++CurPosY); break;
		case 'a':if ( CurPosX > 2 )
			SetCursor (--CurPosX , CurPosY); break;
		case 'd':if ( CurPosX < length-3 )
			SetCursor (++CurPosX , CurPosY); break;
		default:
			break;
	}
	if ( Game.CanChange (CurPosX , CurPosY) == 0 )	Game.SetHeroColor2 (Game.GetFieldColor1 (CurPosX , CurPosY));
	else Game.SetHeroColor2 (15);
	
	Game.SetHeroPos (CurPosX , CurPosY);
	Game.DrawHero ();
	SetCursorPos (200 , 60);
}
//Движение в игре
void MovePlay (char action , int length , int width , Map& Game,int& steps,int& score)
{
	int CurPosY = Game.GetHeroPosY ();
	int CurPosX = Game.GetHeroPosX ();
	SetCursor (CurPosX , CurPosY);
	cout << " ";
	switch ( action )
	{
		case 'w': if ( CurPosY > 2 && Game.GetFieldSign (CurPosX , CurPosY - 1) != '#' ){
					  if ( Game.GetFieldSign (CurPosX , CurPosY - 1) == 'o' ){
						  Beep (3000 , 50);
						  Game.SetFieldSign (CurPosX , CurPosY - 1 , ' ');
						  score++;
					  }
					  if ( Game.GetFieldSign (CurPosX , CurPosY - 1) == '*' ) PlayMenu = 0;
					  steps++;
					  SetCursor (CurPosX , --CurPosY); break;
		}
		case 's':if ( CurPosY < width - 3 && Game.GetFieldSign (CurPosX , CurPosY + 1) != '#' ){
					 if ( Game.GetFieldSign (CurPosX , CurPosY + 1) == 'o' ) {
						 Beep (3000 , 50);
						 Game.SetFieldSign (CurPosX , CurPosY + 1 , ' ');
						 score++;
					 }
					 if ( Game.GetFieldSign (CurPosX , CurPosY + 1) == '*' )PlayMenu=0;
					 steps++;
					 SetCursor (CurPosX , ++CurPosY); break;
		}
		case 'a':if ( CurPosX > 2 && Game.GetFieldSign (CurPosX - 1 , CurPosY) != '#' ){
					 if ( Game.GetFieldSign (CurPosX - 1 , CurPosY) == 'o' ){
						 Beep (3000,50);
						 Game.SetFieldSign (CurPosX - 1 , CurPosY , ' ');
						 score++;
					 }
					 if ( Game.GetFieldSign (CurPosX - 1 , CurPosY) == '*' ) PlayMenu = 0;
					 steps++;
					 SetCursor (--CurPosX , CurPosY); break;
		}
		case 'd':if ( CurPosX < length - 3 && Game.GetFieldSign (CurPosX + 1 , CurPosY) != '#' ){
					 if ( Game.GetFieldSign (CurPosX + 1 , CurPosY) == 'o' ) {
						 Beep (3000 , 50);
						 Game.SetFieldSign (CurPosX + 1 , CurPosY , ' ');
							 score++;
					 }
					 if ( Game.GetFieldSign (CurPosX + 1 , CurPosY) == '*' ) PlayMenu = 0;
					 steps++;
					 SetCursor (++CurPosX , CurPosY); break;
		}
		default:
			break;
	}
	Game.SetHeroPos (CurPosX , CurPosY);
	Game.DrawHero ();
	SetCursorPos (200 , 60);
}
//Сохранение карты
void SaveMap (Map Game)
{
	char* path = new char[30];
	path[0] = '\0';
	strcat (path , "Maps\\");
	strcat (path , Game.GetName ( ));
	FILE* file;

	file = fopen (path , "w");
	for ( int i = 0; i < Game.GetMapW (); i++ )
	{
		for ( int j = 0; j < Game.GetMapL (); j++ )
		{
			fputc (Game.GetFieldSign (j , i) , file);
		}
		if(i==0)fputs ("n\n" , file);
		else if ( i == Game.GetMapW ( ) - 1 );
		else fputc ('\n' , file);
	}
	fclose (file);
}

/////////////////////////////////////////////////////////////////// МЕНЮ ///////////////////////////////////////////////////

//Показ Директории
void DirectoryShow (int &i)
{

	WIN32_FIND_DATAW wfd;
	HANDLE const hFind = FindFirstFileW (L"Maps\\*.txt" , &wfd);
	if ( INVALID_HANDLE_VALUE != hFind )
	{
		do
		{
			SetColor (0 , 15);
			SetCursor (5 , 30 + i * 3);
			std::wcout << i << ". " << &wfd.cFileName[0] << std::endl;
			i++;
		} while ( NULL != FindNextFileW (hFind , &wfd) );
		FindClose (hFind);
	}
}

//Меню_Загрузки
Map LoadMap (char* name)
{

	FILE* file;
	file = fopen (name , "r");


	char* buff = new char[236];
	int length = 0;
	int width = 1;
	fgets (buff , 236 , file);
	while ( buff[length] != 'n' )length++;
	while ( fgets (buff , 236 , file) && buff[0] == '#' )width++;


	rewind (file);
	Map NewGame (length , width);
	name[strlen (name) - 4] = '\0';
	char* NewName = new char[strlen (name)];
	for ( int i = 0; i < strlen (name) - 4; i++ )
		NewName[i] = name[5 + i];
	NewGame.SetName (NewName);

	int scores = 0;
	for ( int i = 0; i < width; i++ )
	{
		fgets (buff , 236 , file);
		for ( int j = 0; j < length; j++ )
		{
			NewGame.SetFieldSign (j , i , buff[j]);
			if ( buff[j] == 'o' ){
				NewGame.SetFieldColor (j , i , 9 , 15);	scores++;
			}
			if ( buff[j] == '*' )
				NewGame.SetFieldColor (j , i , 12 , 15);
			NewGame.SetFieldPos (j , i);
		}

	}
	NewGame.SetScores (scores);
	fclose (file);
	return NewGame;
}
Map DrawLoadMenu (Map Game)
{
	Game.FillMapColor ();
	int k = 0;
	Game.DrawMenuLogo ();
	DirectoryShow (k);
	bool LoadActive = 1;
	SetColor (0 , 15);
	SetCursor (14 , 30 + k * 3);
	cout << "Input MapName: ";
	char* name = new char[15];
	SetCursor (28 , 30 + k * 3);
	cin >> name;
	char* _NewName = new char[25];
	_NewName[0] = '\0';
	strcat (_NewName , "Maps\\");
	strcat (_NewName , name);

	Load_Menu = 0;
	MainMenu = 1;

	return LoadMap (_NewName);
}




//Главное Меню
void DrawMainMenu (Map Game )
{
	PlaySound (TEXT ("Sounds\\TitleMenu.wav") , NULL , SND_FILENAME | SND_ASYNC | SND_LOOP);
	render_window ();
	Game.FillMapColor ();
	Game.DrawMenuLogo ();
	Game.DrawMenuButtons ( );
	Game.DrawLastPlayersMap ( );
	char action;
	while ( MainMenu ){
		action = _getch ( );
		switch ( action )
		{
			case '1': 	MainMenu = 0; PlayMenu = 1; break;
			case '2': 	MainMenu = 0; Create_Menu = 1; break;
			case '3': 	MainMenu = 0; Load_Menu = 1; break;
			/*case '4': 	MainMenu = 0; Profile_Menu = 1; break;*/
			case '5': 	MainMenu = 0; isActive = 0; break;
			default:
				break;
		}
	}
}

//Меню_Игра
void DrawPlayMenu (char* name)
{
	char* path = new char[40];
	strcpy (path , "Maps\\");
	strcat (path , name);
	strcat (path , ".txt");
	Map Game;
	Game= LoadMap (path);

	double t = clock ();
	PlaySound (TEXT ("Sounds\\PlayMenu.wav") , NULL , SND_FILENAME | SND_ASYNC | SND_LOOP);
	Game.DrawMap ( );
	for ( int i = 0; i < Game.GetMapL();i++ )
	for ( int j = 0; j < Game.GetMapW ( );j++ )
	if ( Game.GetFieldSign (i , j) == '@' )
		Game.SetHeroPos (Game.GetFieldPosX (i , j) , Game.GetFieldPosY (i , j));
	Game.SetHeroSign ('@');
	Game.SetHeroColor1 (3);
	
	int score = 0;
	int steps = 0;
	while ( PlayMenu )
	{
		Game.DrawPlay (score,steps);
		char action = _getch ( );
		
		MovePlay (action , Game.GetMapL ( ) , Game.GetMapW() , Game,steps,score);
		if ( PlayMenu == 0 )
		{
			double _t = clock ( );
			_t = ( _t - t ) / 1000;
			Game.SetTime (_t);
			Game.FillMapColor ();
			PlaySound (TEXT ("Sounds\\WinMenu.wav") , NULL , SND_FILENAME | SND_ASYNC | SND_LOOP);
			Game.DrawPlayEnd (score , steps );
		}
		if ( action == '0' )
			PlayMenu = 0;
	}
	MainMenu = 1;
}

//Меню_Создания_Карты
Map DrawCreateMenu (Map& Game)
{
	int coin = 30 ,wall = 999 ,exit = 4;
	bool hero = 1;
	Game.FillMapColor ( );
	PlaySound (TEXT ("Sounds\\CreateMenu.wav") , NULL , SND_FILENAME | SND_ASYNC | SND_LOOP);
	SetCursor (100 , 45);
	cout << "(Max:236) Length:  ";
	SetCursor (99 , 50);
	cout << " (Max:60) Width: ";
	int New_l , New_w;
	SetCursor (118 , 45);
	cin >> New_l;
	SetCursor (118 , 50);
	cin >> New_w;
	Map NewGame (New_l , New_w);

	NewGame.DrawMap ( );

	char action;
	while ( Create_Menu )
	{
		NewGame.ShowCreatorHelp (hero,wall,coin,exit);
		NewGame.DrawHero ();
		action = _getch ( );
		if ( action == 'w' || action == 's' || action == 'a' || action == 'd' )
			MoveCreator (action,New_l,New_w,NewGame);
		switch ( action )
		{
			case '1': NewGame.SetHeroSign ('@'); NewGame.SetHeroColor1 (3); break;
			case '2': NewGame.SetHeroSign ('#'); NewGame.SetHeroColor1 (0); break;
			case '3': NewGame.SetHeroSign ('o'); NewGame.SetHeroColor1 (9); break;
			case '4': NewGame.SetHeroSign ('*'); NewGame.SetHeroColor1 (12); break;
			case '8':
			{
						SetCursor (110 , 63);
						cout << "Name: ";
						char* name = new char[15];
						SetCursor (116 , 63);
						cin >> name;
						NewGame.SetName (name);
						SaveMap (NewGame); 
						Create_Menu = 0; 
						MainMenu = 1; 
						return Game; break; }
			case '9': Create_Menu = 0; MainMenu = 1; return Game; break;
			case 13:
			{
					   if ( NewGame.CanChange (NewGame.GetHeroPosX ( ) , NewGame.GetHeroPosY ( )) )
					   {
						   if ( NewGame.GetHeroSign ( ) == '@' && hero == true || NewGame.GetHeroSign ( ) == '#' && wall > 0
							   || NewGame.GetHeroSign ( ) == 'o' && coin > 0 || NewGame.GetHeroSign ( ) == '*' && exit > 0 ){
							   NewGame.SetFieldColor (NewGame.GetHeroPosX ( ) , NewGame.GetHeroPosY ( ) , NewGame.GetHeroColor1 ( ) , 15);
							   NewGame.setCanChange (NewGame.GetHeroPosX ( ) , NewGame.GetHeroPosY ( ) , false);
							   NewGame.SetFieldSign (NewGame.GetHeroPosX ( ) , NewGame.GetHeroPosY ( ) , NewGame.GetHeroSign ( ));
							   NewGame.SetFieldPos (NewGame.GetHeroPosX ( ) , NewGame.GetHeroPosY ( ));
							   NewGame.DrawField (NewGame.GetHeroPosX ( ) , NewGame.GetHeroPosY ( ));
							   if ( NewGame.GetHeroSign ( ) == 'o' ){
								   NewGame.SetScores (NewGame.GetScores ( ) + 1); coin--;
							   }
							   if ( NewGame.GetHeroSign ( ) == '@' )hero = false;
							   if ( NewGame.GetHeroSign ( ) == '*' )--exit;
							   if ( NewGame.GetHeroSign ( ) == '#' )wall--;
						   }
					   }
					   break; 
			}
			default:
				break;
		}
		for ( int i = 0; i < 3; i++ )
		{
			NewGame.DrawField (NewGame.GetHeroPosX ()-i , NewGame.GetHeroPosY ());
			NewGame.DrawField (NewGame.GetHeroPosX ()+i , NewGame.GetHeroPosY ());
			NewGame.DrawField (NewGame.GetHeroPosX () , NewGame.GetHeroPosY ()+i);
			NewGame.DrawField (NewGame.GetHeroPosX () , NewGame.GetHeroPosY ()-i);
		}

	}
}

////Меню_Профиль
//void DrawProfileMenu (Map Game)
//{
//	Game.DrawMap ();
//	char action = _getch ();
//}

///////////////////////////////////////////////////////////////// Игра ///////////////////////////////////////////////////

//Игра
void MyGame ( ){
	Map Game;
	
	char* Standart = new char[25];
	strcpy (Standart , "Maps\\");
	strcat (Standart , "Standart.txt");
	Game=LoadMap (Standart);
	
	while ( isActive )
	{
		if ( MainMenu ) DrawMainMenu (Game );
		if ( PlayMenu ) DrawPlayMenu (Game.GetName());
		if ( Create_Menu ) Game=DrawCreateMenu (Game);
		if ( Load_Menu ) Game=DrawLoadMenu (Game);
		/*if ( Profile_Menu ) DrawProfileMenu (Game);*/
	}
}


int main ( )
{
	MyGame ( );
}
