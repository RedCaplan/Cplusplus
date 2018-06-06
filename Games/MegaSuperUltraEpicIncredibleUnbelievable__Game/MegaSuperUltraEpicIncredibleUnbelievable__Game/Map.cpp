#include "Map.h"
#include "Player.h"
#include "Field.h"


Map::Map (int l,int w )
{
	name = new char[20];
	name = "Standart";
	Username = new char[20];
	Username[0] = '\0';
	MapSize.l = l;
	MapSize.w = w;
	arr = new Field*[MapSize.l];
	for ( int i = 0; i < MapSize.l; i++ )
	{
		arr[i] = new Field[MapSize.w];
	}
	InitializeMap ();
	InitializeBorders ();
}

void Map::DrawMap ( )
{
	system ("cls");
	for ( int i = 0; i < MapSize.l; i++ )
	{
		for ( int j = 0; j < MapSize.w; j++ )
		{
			arr[i][j].DrawField ( );
		}
	}
}

void Map::InitializeBorders ( )
{
	
	for ( int i = 0; i < MapSize.l; i++ )
	{
		arr[i][0].SetPos (i , 0);
		arr[i][0].SetSign ('#');
		arr[i][1].SetPos (i , 1);
		arr[i][1].SetSign ('#');
		arr[i][MapSize.w - 1].SetPos (i , MapSize.w - 1);
		arr[i][MapSize.w - 1].SetSign ('#');
		arr[i][MapSize.w - 2].SetPos (i , MapSize.w - 2);
		arr[i][MapSize.w - 2].SetSign ('#');
	}
	for ( int i = 0; i < MapSize.w; i++ )
	{
		arr[0][i].SetPos (0 , i);
		arr[0][i].SetSign ('#');
		arr[MapSize.l - 1][i].SetPos (MapSize.l - 1 , i);
		arr[MapSize.l - 1][i].SetSign ('#');
		arr[1][i].SetPos (1 , i);
		arr[1][i].SetSign ('#');
		arr[MapSize.l - 2][i].SetPos (MapSize.l - 2 , i);
		arr[MapSize.l - 2][i].SetSign ('#');
	}
}
void Map::InitializeMap ( )
{
	for ( int i = 0; i < MapSize.l;i++ )
	for ( int j = 0; j < MapSize.w; j++ )
		arr[i][j].InitializeFields ( );
}
void Map::SetColor (int text , int background)
{
	HANDLE hStdOut = GetStdHandle (STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute (hStdOut , (WORD)( ( background << 4 ) | text ));
}
void Map::DrawMenuLogo ( ) //Unknown hero
{
	SetColor (0 , 15);
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	cout << "                                           ####         ####    ####         ####    ####    /###   ####         ####          ##########         #####  ######  ####   ####         ####              " << endl;
	cout << "                                           #  #         #  #    |  #|\\       |  #    #  |   /  /    |  #|\\       |  #        ###/      \\###       |   #  |    #  |  #   |  #|\\       |  #              " << endl;
	cout << "                                           #  #         #  #    |  # \\\\      |  #    #  |  /  /     |  # \\\\      |  #       ###/        \\###      |   #  |    #  |  #   |  # \\\\      |  #              " << endl;
	cout << "                                           #  #         #  #    |  # \\\\\\     |  #    #  | /  /      |  # \\\\\\     |  #      ###/          \\###     |   #  |    #  |  #   |  # \\\\\\     |  #              " << endl;
	cout << "                                           #  #         #  #    |  #  \\\\\\    |  #    #  |/  /       |  #  \\\\\\    |  #     ###/            \\###    |   #  |    #  |  #   |  #  \\\\\\    |  #              " << endl;
	cout << "                                           #  #         #  #    |  #   \\\\\\   |  #    #     /        |  #   \\\\\\   |  #    ###/              \\###   |   #  |    #  |  #   |  #   \\\\\\   |  #              " << endl;
	cout << "                                           #  #         #  #    |  #    \\\\\\  |  #    #  |\\  \\       |  #    \\\\\\  |  #   ###\\               /###   |   #  |    #  |  #   |  #    \\\\\\  |  #              " << endl;
	cout << "                                           #  #         #  #    |  #     \\\\\\ |  #    #  | \\  \\      |  #     \\\\\\ |  #    ###\\             /###    |   #  |    #  |  #   |  #     \\\\\\ |  #              " << endl;
	cout << "                                           #   #       #   #    |  #      \\\\\\|  #    #  |  \\  \\     |  #      \\\\\\|  #     ###\\           /###     |   #  |    #  |  #   |  #      \\\\\\|  #              " << endl;
	cout << "                                            ##  #######  ##     |  #       \\\\|  #    #  |   \\  \\    |  #       \\\\|  #      ###\\         /###      |    @@@    @@@   #   |  #       \\\\|  #              " << endl;
	cout << "                                              ## Kirill ##      |  #        \\|  #    #  |    \\  \\   |  #        \\|  #       ###\\       /###        ##              ##   |  #        \\|  #              " << endl;
	cout << "                                                #######         ####         ####    ####     ###   ####         ####         ###########            #############      ####         ####              " << endl;

	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	cout << "                                                                               ##         ##      /###########\\\\      |##########\\\\       #############       " << endl;
	cout << "                                                                              # #         # #     # ##########//      |#         /#      ###          ###        " << endl;
	cout << "                                                                             #  #         #  #    #                   |#       /#       ###            ###       " << endl;
	cout << "                                                                             #  #         #  #    #                   |#     /#        ###              ###   " << endl;
	cout << "                                  # # #                                      #  #/#######/#  #    #                   |#   /#         ###               ###    " << endl;
	cout << "                                 # o o #                                     #  ############ #    #\\##########/       |# /#           ###               ###    " << endl;
	cout << "                                 #  |  #                                     #  #         #  #    #/##########\\       |#/#            ###               ###    " << endl;
	cout << "                                 # ~~~ #                                     #  #         #  #    #                   |#  #\\          ###              ###      " << endl;
	cout << "                                  # # #                                      #  #         #  #    #                   |#   #\\         ###             ###        " << endl;
	cout << "                                                                             #  #         #  #    #                   |#    #\\         ###            ###       " << endl;
	cout << "                                                                             # #          # #     # ##########\\\\      |#     #\\         ###         ###      " << endl;
	cout << "                                                                             ##           ##      \\###########//      |#      #\\         #############         " << endl;
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
}
void Map::DrawMenuButtons ( )
{
	HANDLE hCon;
	hCon = GetStdHandle (STD_OUTPUT_HANDLE);
	COORD cPos = { 110 , 40 };
	SetConsoleCursorPosition (hCon , cPos);
	cout << "1   -   PLAY" << endl;
	cPos = { 110 , 45 };
	SetConsoleCursorPosition (hCon , cPos);
	cout << "2   -   CREATE MAP" << endl;
	cPos = { 110 , 50 };
	SetConsoleCursorPosition (hCon , cPos);
	cout << "3   -   LOAD MAP" << endl;
	cPos = { 114 , 52 };
	SetConsoleCursorPosition (hCon , cPos);
	cout << "(Current: "<< name <<")" << endl;
	//cPos = { 110 , 55 };
	//SetConsoleCursorPosition (hCon , cPos);
	//cout << "4   -   PROFILE" << endl;
	cPos = { 110 , 60 };
	SetConsoleCursorPosition (hCon , cPos);
	cout << "5   -   EXIT" << endl;
}
void Map::FillMapColor ( )
{
	HANDLE hCon;
	COORD cPos = { 0 , 0 };
	hCon = GetStdHandle (STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition (hCon , cPos);
	SetColor (0 , 15);
	for ( int i = 0; i < 67; i++ )
	{
		for ( int j = 0; j < 236; j++ )
			cout << " ";
		cout << endl;
	}
	SetConsoleCursorPosition (hCon , cPos);
}
void Map::ShowCreatorHelp (bool hero,int wall,int coin,int exit)
{
	HANDLE hCon;
	hCon = GetStdHandle (STD_OUTPUT_HANDLE);
	COORD cPos = { 10 , 63 };
	SetColor (3 , 15);
	SetConsoleCursorPosition (hCon , cPos);
	cout << "1  -  HERO";
	cPos = { 13 , 65 };
	SetConsoleCursorPosition (hCon , cPos);
	cout << "x " << hero;

	cPos = { 25 , 63 };
	SetConsoleCursorPosition (hCon , cPos);
	SetColor (0 , 15);
	cout << "2  -  WALL";
	cPos = { 26 , 65 };
	SetConsoleCursorPosition (hCon , cPos);
	cout << "# x " << wall ;

	cPos = { 40 , 63 };
	SetConsoleCursorPosition (hCon , cPos);
	SetColor (1 , 15);
	cout << "3  -  COIN";
	cPos = { 41 , 65 };
	SetConsoleCursorPosition (hCon , cPos);
	cout << "@ x"<<coin;

	cPos = { 55 , 63 };
	SetConsoleCursorPosition (hCon , cPos);
	SetColor (12 , 15);
	cout << "4  -  EXIT";
	cPos = { 58 , 65 };
	SetConsoleCursorPosition (hCon , cPos);
	cout << "X" << exit;

	cPos = { 180 , 63 };
	SetConsoleCursorPosition (hCon , cPos);
	SetColor (10 , 15);
	cout << "8  -  SAVE";

	cPos = { 215 , 63 };
	SetColor (12 , 15);
	SetConsoleCursorPosition (hCon , cPos);
	cout << "9  -  UNSAVE";
}
void Map::DrawPlay (int _scores,int steps)
{

	HANDLE hCon;
	hCon = GetStdHandle (STD_OUTPUT_HANDLE);
	COORD cPos = { 10 , 63 };
	SetColor (3 , 15);
	SetConsoleCursorPosition (hCon , cPos);
	cout <<"NAME: " << name;
	cPos = { 13 , 65 };
	SetConsoleCursorPosition (hCon , cPos);
	cout <<"SCORES: "<<_scores<<"|"<< scores;
	cPos = { 13 , 64 };
	SetConsoleCursorPosition (hCon , cPos);
	cout << "STEPS: " << steps;
	cPos = { 110 , 64 };
	SetColor (12 , 15);
	SetConsoleCursorPosition (hCon , cPos);
	cout << "0 - EXIT: ";
}
void Map::DrawPlayEnd (int _scores , int steps)
{
	HANDLE hCon;
	hCon = GetStdHandle (STD_OUTPUT_HANDLE);
	COORD cPos = { 110 , 20 };
	SetColor (3 , 15);
	SetConsoleCursorPosition (hCon , cPos);
	cout << "MapName: " << name;
	cPos = { 110 , 30 };
	SetConsoleCursorPosition (hCon , cPos);
	cout << "Scores: " << _scores << "|" << scores;
	cPos = { 110 , 40 };
	SetConsoleCursorPosition (hCon , cPos);
	cout << "Steps: " << steps;
	cPos = { 110 , 10 };
	SetConsoleCursorPosition (hCon , cPos);
	cout << "Player: " <<Username ;
	cPos = { 110 , 50};
	SetConsoleCursorPosition (hCon , cPos);
	cout << "Time:  " << time << " sec";

	cPos = { 118 , 10 };
	SetConsoleCursorPosition (hCon , cPos);
	cin >> Username;


	FILE* file;
	char* filename = new char[30];
	char* buff = new char[240];
	int size=0;
	strcpy (filename , "Maps\\");
	strcat (filename , name);
	strcat (filename , ".txt");
	file = fopen (filename , "a+t");

	while ( fgets (buff , 240 , file) )size++;
	rewind (file);
	if ( size - MapSize.w > 8 )
	{
		FILE* file2;
		file2 = fopen ("Maps\\temp.txt" , "a+t");
		for ( int i = 0; i < MapSize.w; i++ )
		{
			fgets (buff , 240 , file);
			fputs (buff , file2);
		}
		fclose (file2);
		fclose (file);
		if ( remove (filename) == 0 )cout << "success"; else cout << "Bad";
		if ( rename ("Maps\\temp.txt" , filename) == 0 )cout << "success"; else cout << "Bad";

		file = fopen (filename , "a+t"); 
	}

	fseek (file ,0, SEEK_END);
	fprintf (file , "\n%s %d/%d %d %f" , Username , _scores , scores , steps , time);
	fclose (file);
}
void Map::DrawLastPlayersMap()
{
	HANDLE hCon;
	hCon = GetStdHandle (STD_OUTPUT_HANDLE);
	COORD cPos;
	
	
	int counter = 0;
	FILE* file;
	char* new_name = new char[40];
	strcpy (new_name , "Maps\\");
	strcat (new_name , name);
	if ( name[strlen (name) - 4] != '.' )
	strcat (new_name , ".txt");
	file = fopen (new_name , "r");
	SetColor (9 , 15);
	cPos = { 160 , 33 };
	SetConsoleCursorPosition (hCon , cPos);
	cout << "LAST 10 PASSED MAP";
	cPos = { 160 , 34 };
	SetConsoleCursorPosition (hCon , cPos);
	
	cout << "  NAME COINS STEPS  TIME";
	char* buff = new char[236];
	SetColor (12 , 15);
	for ( int i = 0; i < MapSize.w; i++ ){fgets (buff , 236 , file);}

	while ( fgets (buff , 236 , file) && counter < 9 )
	{
		cPos = { 160 , 36 + counter * 3 };
		SetConsoleCursorPosition (hCon , cPos);
		cout <<counter<<". "<< buff;
		counter++;
	}

	fclose (file);
}
Map::~Map ( )
{
	/*for ( int i = 0; i < MapSize.l;i++ )
		delete[]arr[i];
	delete[]arr;*/
}
