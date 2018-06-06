#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <Windows.h>
#include <time.h>
#include <string.h>
#include <clocale>
/* */
void gotoxy(int xpos, int ypos); //�������� ������� ��������� ������� � ����� xpos, ypos
								 /* */

unsigned const char KEY_UP = 'w'; //����������� ������� "�����"
unsigned const char KEY_DOWN = 's'; //����������� ������� "����"
unsigned const char KEY_LEFT = 'a'; //����������� ������� "�����"
unsigned const char KEY_RIGHT = 'd'; //����������� ������� "������"
unsigned const char KEY_SPACE = 32; //����������� ������� "������"
unsigned const char KEY_ESC = 27; //����������� ������� "escape"
unsigned const char KEY_ENTER = 13; //����������� ������� "enter"

unsigned const int SIZEX = 20;//-������ ����
unsigned const int SIZEY = 20;//-����� ����
unsigned const int FMAP_COUNTS = 7; //���������� ����� �������

#define TRUE 1 
#define FALSE 0  //���������� ���������� ��� �������� ����� 

unsigned const char SCR_SP = 249; //������������ ����
unsigned const char SCR_OB = 178; //������������ ������
								 //char main_color[] = "color ##";
int screen[SIZEX][SIZEY] = { 0 }; //������ ������
int map[4][4]; //������
int px, py, nextmap;

int fmap[FMAP_COUNTS][4][4] = //������������� ����� �������
{
	{
		{ 1 , 1 , 0 , 0 } ,
		{ 1 , 1 , 0 , 0 } ,
		{ 0 , 0 , 0 , 0 } ,
		{ 0 , 0 , 0 , 0 }
	} ,
	{
		{ 1 , 0 , 0 , 0 } ,
		{ 1 , 0 , 0 , 0 } ,
		{ 1 , 0 , 0 , 0 } ,
		{ 1 , 0 , 0 , 0 }
	} ,
	{
		{ 0 , 0 , 1 , 0 } ,
		{ 1 , 1 , 1 , 0 } ,
		{ 0 , 0 , 0 , 0 } ,
		{ 0 , 0 , 0 , 0 }
	} ,
	{
		{ 1 , 1 , 1 , 0 } ,
		{ 0 , 0 , 1 , 0 } ,
		{ 0 , 0 , 0 , 0 } ,
		{ 0 , 0 , 0 , 0 }
	} ,
	{
		{ 0 , 1 , 1 , 0 } ,
		{ 1 , 1 , 0 , 0 } ,
		{ 0 , 0 , 0 , 0 } ,
		{ 0 , 0 , 0 , 0 }
	} ,
	{
		{ 1 , 1 , 0 , 0 } ,
		{ 0 , 1 , 1 , 0 } ,
		{ 0 , 0 , 0 , 0 } ,
		{ 0 , 0 , 0 , 0 }
	} ,
	{
		{ 1 , 1 , 1 , 0 } ,
		{ 0 , 1 , 0 , 0 } ,
		{ 0 , 0 , 0 , 0 } ,
		{ 0 , 0 , 0 , 0 }
	}
};

void print(void) //������
{
	int i, j;
	int buff[SIZEX][SIZEY];

	for (i = 0; i < SIZEY; i++) for (j = 0; j < SIZEX; j++) buff[j][i] = screen[j][i]; //����� �� ������ �� �����
	for (i = 0; i < 4; i++) for (j = 0; j < 4; j++) if (map[j][i]) buff[j + px][i + py] = 1; //���� ����� ������, �� � ������ ���������� 1

	gotoxy(0, 0); //������� � ����� � ������������ 0, 0
	for (i = 0; i < SIZEY; i++)
	{
		for (j = 0; j < SIZEX; j++)
		{
			putchar(buff[j][i] == 0 ? SCR_SP : SCR_OB); //���� ������� � ������ �� ����� ������, �� ��������� �����
		}
		putchar('\n');
	}

	gotoxy(SIZEX + 1, 0); //���� ����
}
////////////////////////////////////////////////////////////////////////////////////////////////
void printnextmap(void) //���������� ��������� ������ ������ � ����
{
	int i, j;

	gotoxy(SIZEX + 1, 2);
	printf("NEXT: ");

	for (i = 0; i < 4; i++)
	{
		gotoxy(SIZEX + 2, i + 3);
		for (j = 0; j < 4; j++)
		{
			putchar(fmap[nextmap][j][i] == 0 ? ' ' : SCR_OB); //���� �� ����� ������, �� ��������� ���������, ����� ��������� �������
		}
	}
}
////////////////////////////////////////////////////////////////////////////////////// 
int getkey(void)//-����� �� ����� ����
{
	int c;
	if (_kbhit()) //���� ������ �������
	{
		if ((c = _getch()) == 224)
			c = _getch();
		//���� ������ ������� p (�����), �� ������ ����� ������� ��� ����������� ����
		return c;
	}
	return FALSE;
}
////////////////////////////////////////////////////////////////////////////////////// 
void gotoxy(int xpos, int ypos) //����������� ������� �������� �������� � ����� � ������������ xpos, ypos
{
	COORD scrn;
	HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
	scrn.X = xpos; scrn.Y = ypos;
	SetConsoleCursorPosition(hOuput, scrn);
}
///////////////////////////////////////////////////////////////////////////////////////// 
int valnewpos(int x, int y) //������������� �������� ������ ����
{
	int i, j;
	if (x < 0) return FALSE;
	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			if (map[j][i])
			{
				if ((j + x >= SIZEX) || (i + y >= SIZEY)) return FALSE;//-�������� �� ����� �� ������ �� ������� ������ ������.
				if (screen[j + x][i + y])
				{
					return FALSE;//-���� �� �� ������ "����"
				}
			}
		}
	}
	return TRUE;//-���� ��� ���������� "���" - ������ �������� ����.
}

#define inv(x) ((x * (-1)) + 3)
///////////////////////////////////////////////////////////////////////////////////////////////////// 
void rotatemap(void) //������� ������
{
	/* Optimize! */
	int _map[4][4];
	int i, j, sx = 4, sy = 4;

	for (i = 0; i < 4; i++)
		for (j = 0; j < 4; j++)
		{
			_map[j][i] = map[j][i];//-������ ����� ������,��� ���� ��� �� ������� �������������� ���.
			if (map[j][i])//���� � �������� ���� - ������ ����� ���� ,�� 
			{
				if (i < sx) sx = i;//�������� �� ������� ���������� ����� ���������� �
				if (inv(j) < sy) sy = inv(j);//����� ���������� �
			}
			map[j][i] = 0;//-�������� ������� � �������
		}

	for (i = 0; i < 4; i++)
		for (j = 0; j < 4; j++)
			if (_map[inv(i)][j]) map[j - sx][i - sy] = 1;//������ ����������
	if (!valnewpos(px, py)) for (i = 0; i < 4; i++)
		for (j = 0; j < 4; j++)
			map[j][i] = _map[j][i];//���������� ������� �� ����������� �������
}
////////////////////////////////////////////////////////////////////////////////////////////////////// 
int rnd(int max) //������������
{
	max++;
	return (int)(rand() * max / RAND_MAX);
}
/////////////////////////////////////////////////////////////////////////////////// 
void sleep(int milsec) //��������
{
	clock_t t = clock();
	while (clock() - t < milsec);
}
/////////////////////////////////////////////////////////////////////////////////// 
void deleteline(void) //����� ��������� �����
{
	int i, j, k, cl;

	for (i = SIZEY - 1; i >= 0; i--)
	{
		cl = 1;
		for (j = 0, cl = 1; j < SIZEX; j++)
		{
			if (!screen[j][i]) cl = 0;
		}
		if (cl)
		{
			/* Animation */
			gotoxy(0, i);
			for (k = 0; k < SIZEX; k++) putchar('_'), sleep(20);
			/* --------- */

			for (k = i; k > 0; k--)
			{
				for (j = 0; j < SIZEX; j++)
				{
					screen[j][k] = screen[j][k - 1];
				}
			}
			i++;
			print();
		}
	}
}
////////////////////////////////////////////////////////////////////////////////////
void createmap(void) //�������� ������
{
	int i, j;

	for (i = 0; i < 4; i++)
		for (j = 0; j < 4; j++)
			map[j][i] = fmap[nextmap][j][i];
	py = 0;
	px = SIZEX / 2;

	nextmap = rnd(FMAP_COUNTS - 1);
	printnextmap();
}
///////////////////////////////////////////////////////////////////////////////////////
void clearscreen(void) //������� ������
{
	int i, j;
	for (i = 0; i < SIZEY; i++)
		for (j = 0; j < SIZEX; j++)
			screen[j][i] = 0;
}
/////////////////////////////////////////////////////////////////////////////////////
void createrndscreen(void) //������� ��������� �����
{
	int i, j, rn;
	clearscreen();
	rn = rnd(10);
	for (i = SIZEY - 1; i >= (SIZEY - 1) - rn; i--)
		for (j = 0; j < SIZEX; j++)
		{
			screen[j][i] = rnd(1);
		}
}
//////////////////////////////////////////////////////////////////////////////////// 
void startgame(void) //����
{
	int i, j, c;
	time_t tm;

	system("cls");
	px = SIZEX / 2;//�������� ��� ������� ������ �� �,����� �� ������
	py = 0;

	tm = clock();

	nextmap = rnd(FMAP_COUNTS - 1);//��������� ������ ���������� �� 6 
	createmap();//�������� �������

	while (TRUE)
	{
		c = getkey();

		switch (c)
		{
		case KEY_UP:
			rotatemap();//�������
			break;
		case KEY_SPACE:
			rotatemap();//�������
			break;
		case KEY_DOWN://�������� ����
			for (; valnewpos(px, py + 1); py++);
			for (i = 0; i < 4; i++)
				for (j = 0; j < 4; j++)
					if (map[j][i]) screen[px + j][py + i] = 1;

			print();
			deleteline();//������ �� ������� �������� ����������� �� ����� � � ��������
			createmap();//����� ������
			break;
		case KEY_LEFT:
			if (valnewpos(px - 1, py)) px--;//�������� ����� ,��������� �������� ���� �� �
			break;
		case KEY_RIGHT:
			if (valnewpos(px + 1, py)) px++;//�������� ������ ,����������� �������� ���� �� �
			break;
		case 'p'://�����
			_getch();
			break;
		case KEY_ESC://�����
			return;
		}

		if ((clock() - tm) > 720)//-����� ������� ������ 
		{
			tm = clock();

			if (!(valnewpos(px, py + 1)))
			{
				for (i = 0; i < 4; i++)
					for (j = 0; j < 4; j++)
						if (map[j][i]) screen[px + j][py + i] = 1;

				createmap();
				deleteline();
			}
			else py++;//������� ����
		}

		print();

		for (i = 0; i < SIZEX; i++)
		{
			if (screen[i][0])//���� ������� � � � ������ ������� � ����� 0,�� ����� ���� ,���� ����������� �� �����
			{
				system("cls");
				gotoxy(2, 8);
				printf("GAME END! :(");
				return;
			}
		}
	}
}
/////////////////////////////////////////////////////////////////////////////////// 
void gamemenu(void) //������� ����
{
	int p = 1, c = 0;
	const char* GAME_MENU = "                     =================================\n"
		"                     |  1. START                     |\n"
		"                     =================================\n"
		"                     |  2. START(LVLUP)              |\n"
		"                     =================================\n"
		"                     |  3. CONTROLS                  |\n"
		"                     =================================\n"
		"                     |  4. EXIT                      |\n "
		"                    =================================";
	system("cls"); printf("%s", GAME_MENU);
	while (TRUE) //��������� �� ����
	{
		c = _getch();
		switch (c)
		{
		case '1':
		case '2':
		case '3':
		case '4':
			p = c - '0';
		case KEY_ENTER:
			switch (p)
			{
			case 1:
				clearscreen();
				startgame();
				gotoxy(0, SIZEY); printf("Press esc to exit in main menu...\n"); while (_getch() != KEY_ESC);
				break;
			case 2:
				clearscreen();
				createrndscreen();
				startgame();
				gotoxy(0, SIZEY); printf("Press esc to exit in main menu...\n");  while (_getch() != KEY_ESC);
				break;
			case 3:
				system("cls");
				printf("%s",
					"=================\n"
					"| 'A'      |LEFT  |\n"
					"| 'D'      |RIGHT |\n"
					"| 'S'      |DOWN  |\n"
					"| 'W'/Space|ROTATE|\n"
					"| 'P'      |PAUSE |\n"
					"| 'ESC'    |EXIT  |\n"
					"=================\n\n"
					"Press anything...\n");
				_getch();
		
				if (_kbhit())
					_getch();
				break;
			case 4: return;
			}
			system("cls"); printf("%s", GAME_MENU);
			p = 1;
			break;
		case KEY_UP:
			if (p > 1) p--;
			break;
		case KEY_DOWN:
			if (p < 4) p++;
			break;
		case KEY_ESC:
			return;
		}

	}
}
///////////////////////////////////////////////////////////////////////////////////
int main()
{
	system("color 5F");
	gamemenu();
}
