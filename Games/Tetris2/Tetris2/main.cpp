#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <Windows.h>
#include <time.h>
#include <string.h>
#include <clocale>
/* */
void gotoxy(int xpos, int ypos); //прототип функции помещения курсора в точку xpos, ypos
								 /* */

unsigned const char KEY_UP = 'w'; //определение клавиши "вверх"
unsigned const char KEY_DOWN = 's'; //определение клавиши "вниз"
unsigned const char KEY_LEFT = 'a'; //определение клавиши "влево"
unsigned const char KEY_RIGHT = 'd'; //определение клавиши "вправо"
unsigned const char KEY_SPACE = 32; //определение клавиши "пробел"
unsigned const char KEY_ESC = 27; //определение клавиши "escape"
unsigned const char KEY_ENTER = 13; //определение клавиши "enter"

unsigned const int SIZEX = 20;//-ширина поля
unsigned const int SIZEY = 20;//-длина поля
unsigned const int FMAP_COUNTS = 7; //количество фигур тетриса

#define TRUE 1 
#define FALSE 0  //логические переменные для создания фигур 

unsigned const char SCR_SP = 249; //закрашивание поля
unsigned const char SCR_OB = 178; //закрашивание фигуры
								 //char main_color[] = "color ##";
int screen[SIZEX][SIZEY] = { 0 }; //размер экрана
int map[4][4]; //фигура
int px, py, nextmap;

int fmap[FMAP_COUNTS][4][4] = //инициализация фигур тетриса
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

void print(void) //печать
{
	int i, j;
	int buff[SIZEX][SIZEY];

	for (i = 0; i < SIZEY; i++) for (j = 0; j < SIZEX; j++) buff[j][i] = screen[j][i]; //вывод из буфера на экран
	for (i = 0; i < 4; i++) for (j = 0; j < 4; j++) if (map[j][i]) buff[j + px][i + py] = 1; //если часть фигуры, то в буфере обозначить 1

	gotoxy(0, 0); //перейти в точку с координатами 0, 0
	for (i = 0; i < SIZEY; i++)
	{
		for (j = 0; j < SIZEX; j++)
		{
			putchar(buff[j][i] == 0 ? SCR_SP : SCR_OB); //если элемент в буфере не часть фигуры, то закрасить полем
		}
		putchar('\n');
	}

	gotoxy(SIZEX + 1, 0); //уйти вбок
}
////////////////////////////////////////////////////////////////////////////////////////////////
void printnextmap(void) //напечатать следующую идущую фигуру в поле
{
	int i, j;

	gotoxy(SIZEX + 1, 2);
	printf("NEXT: ");

	for (i = 0; i < 4; i++)
	{
		gotoxy(SIZEX + 2, i + 3);
		for (j = 0; j < 4; j++)
		{
			putchar(fmap[nextmap][j][i] == 0 ? ' ' : SCR_OB); //если не часть фигуры, то закрасить пробелами, иначе закрасить фигурой
		}
	}
}
////////////////////////////////////////////////////////////////////////////////////// 
int getkey(void)//-пауза во время игры
{
	int c;
	if (_kbhit()) //если нажата клавиша
	{
		if ((c = _getch()) == 224)
			c = _getch();
		//если нажата клавиша p (пауза), то нажать любую клавишу для продолжения игры
		return c;
	}
	return FALSE;
}
////////////////////////////////////////////////////////////////////////////////////// 
void gotoxy(int xpos, int ypos) //стандартная функция перехода курсором в точку с координатами xpos, ypos
{
	COORD scrn;
	HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
	scrn.X = xpos; scrn.Y = ypos;
	SetConsoleCursorPosition(hOuput, scrn);
}
///////////////////////////////////////////////////////////////////////////////////////// 
int valnewpos(int x, int y) //необходимость движения фигуры вниз
{
	int i, j;
	if (x < 0) return FALSE;
	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			if (map[j][i])
			{
				if ((j + x >= SIZEX) || (i + y >= SIZEY)) return FALSE;//-проверка не зашла ли фигура за границы нашего экрана.
				if (screen[j + x][i + y])
				{
					return FALSE;//-если да то вернем "фолс"
				}
			}
		}
	}
	return TRUE;//-если нет возвращаем "тру" - фигура движется вниз.
}

#define inv(x) ((x * (-1)) + 3)
///////////////////////////////////////////////////////////////////////////////////////////////////// 
void rotatemap(void) //поворот фигуры
{
	/* Optimize! */
	int _map[4][4];
	int i, j, sx = 4, sy = 4;

	for (i = 0; i < 4; i++)
		for (j = 0; j < 4; j++)
		{
			_map[j][i] = map[j][i];//-создае копию фигуры,для того что бы вернуть первоначальный вид.
			if (map[j][i])//цикл с услевием ЕСЛИ - фигура равна нулю ,то 
			{
				if (i < sx) sx = i;//проходим по фигурке запоминаем новую координату х
				if (inv(j) < sy) sy = inv(j);//новую координату у
			}
			map[j][i] = 0;//-обнуляем матрицу с фигурой
		}

	for (i = 0; i < 4; i++)
		for (j = 0; j < 4; j++)
			if (_map[inv(i)][j]) map[j - sx][i - sy] = 1;//рисуем перевертыш
	if (!valnewpos(px, py)) for (i = 0; i < 4; i++)
		for (j = 0; j < 4; j++)
			map[j][i] = _map[j][i];//возвращаем обратно на изначальную фигурку
}
////////////////////////////////////////////////////////////////////////////////////////////////////// 
int rnd(int max) //рандомизация
{
	max++;
	return (int)(rand() * max / RAND_MAX);
}
/////////////////////////////////////////////////////////////////////////////////// 
void sleep(int milsec) //задержка
{
	clock_t t = clock();
	while (clock() - t < milsec);
}
/////////////////////////////////////////////////////////////////////////////////// 
void deleteline(void) //убить собранную линию
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
void createmap(void) //создание фигуры
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
void clearscreen(void) //очистка экрана
{
	int i, j;
	for (i = 0; i < SIZEY; i++)
		for (j = 0; j < SIZEX; j++)
			screen[j][i] = 0;
}
/////////////////////////////////////////////////////////////////////////////////////
void createrndscreen(void) //создать случайный экран
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
void startgame(void) //игра
{
	int i, j, c;
	time_t tm;

	system("cls");
	px = SIZEX / 2;//значение для падения фигуры по х,выход из центра
	py = 0;

	tm = clock();

	nextmap = rnd(FMAP_COUNTS - 1);//следующая фигура выбирается из 6 
	createmap();//создание фигурки

	while (TRUE)
	{
		c = getkey();

		switch (c)
		{
		case KEY_UP:
			rotatemap();//поворот
			break;
		case KEY_SPACE:
			rotatemap();//поворот
			break;
		case KEY_DOWN://движение вниз
			for (; valnewpos(px, py + 1); py++);
			for (i = 0; i < 4; i++)
				for (j = 0; j < 4; j++)
					if (map[j][i]) screen[px + j][py + i] = 1;

			print();
			deleteline();//проход по функции проверки заполнилась ли линия и её удаление
			createmap();//новая фигура
			break;
		case KEY_LEFT:
			if (valnewpos(px - 1, py)) px--;//движение влево ,уменьшаем значение пера по х
			break;
		case KEY_RIGHT:
			if (valnewpos(px + 1, py)) px++;//движение вправо ,увеличиваем значение пера по х
			break;
		case 'p'://пауза
			_getch();
			break;
		case KEY_ESC://выход
			return;
		}

		if ((clock() - tm) > 720)//-время падения фигуры 
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
			else py++;//падение вниз
		}

		print();

		for (i = 0; i < SIZEX; i++)
		{
			if (screen[i][0])//если экраный у и у фигуры совпали и равны 0,то конец игры ,поле заполнилось до верха
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
void gamemenu(void) //игровое меню
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
	while (TRUE) //навигация по меню
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
