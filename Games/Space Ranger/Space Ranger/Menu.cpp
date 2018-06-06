#include "Menu.h"
#define _CRT_SECURE_NO_WARNINGS
Menu::Menu()
{
	arr = new Pointer[size];
}
Pointer* Menu::AddPoint()
{
	size++;
	Pointer* new_arr = new Pointer[size];

	for (int i = 0;i < size-1;i++)
	{
		new_arr[i].str = arr[i].str;
		new_arr[i].x = arr[i].x;
		new_arr[i].y = arr[i].y;
		new_arr[i].color1 = arr[i].color1;
		new_arr[i].color2 = arr[i].color2;
		new_arr[i].point = arr[i].point;
	}
	cout << "Name: ";
	cin >> new_arr[size - 1].str;
	return new_arr;
}
Pointer * Menu::AddPoint(const char * str)
{
	size++;
	Pointer* new_arr = new Pointer[size];

	for (int i = 0;i < size - 1;i++)
	{
		new_arr[i].str = arr[i].str;
		new_arr[i].x = arr[i].x;
		new_arr[i].y = arr[i].y;
		new_arr[i].color1 = arr[i].color1;
		new_arr[i].color2 = arr[i].color2;
		new_arr[i].point = arr[i].point;
	}
	new_arr[size - 1].str.reserve(strlen(str)+1);
	new_arr[size - 1].str += str;
	return new_arr;
}
Pointer* Menu::RemovePoint(int _i)
{
	--size;
	Pointer* new_arr = new Pointer[size];

	for (int i = 0;i < size;i++)
	{
		if (i < _i) {
			new_arr[i].str = arr[i].str;
			new_arr[i].x = arr[i].x;
			new_arr[i].y = arr[i].y;
			new_arr[i].color1 = arr[i].color1;
			new_arr[i].color2 = arr[i].color2;
			new_arr[i].point = arr[i].point;
		}
		else
		{
			new_arr[i].str = arr[i+1].str;
			new_arr[i].x = arr[i + 1].x;
			new_arr[i].y = arr[i + 1].y;
			new_arr[i].color1 = arr[i+1].color1;
			new_arr[i].color2 = arr[i+1].color2;
			new_arr[i].point = arr[i+1].point;
		}
	}
	return new_arr;
}
Pointer* Menu::EditPoint(int i)
{
	cout << "Name: ";
	cin >> arr[i].str;
	cout << "Color1: ";
	cin >> arr[i].color1;
	cout << "Color2: ";
	cin >> arr[i].color2;
	return arr;
}
void Menu::SetColor(int text, int background)
{
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdOut, (WORD)((background << 4) | text));
}


void Menu::SetPos(int x, int y)
{
	COORD coord = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void Menu::SetCompletePos(int x, int y)
{
    startX = x;
    startY = y;
	for (int i = 0;i < size;i++)
	{
		arr[i].x = startX;
		arr[i].y = startY + i*Interval;
		arr[i].point = i;
	}
}

int Menu::Show()
{
	if (size == 0) {
		if (LoadFile() == 0)
			cout << "ADD POINTS IN MENU ( SETTINGs.TXT)" << endl;
	}
	SetCompletePos(startX, startY);

	SetBorder();
	for (int i = 0;i < size;i++)
	{
		SetPos(arr[i].x, arr[i].y);
		SetColor(arr[i].color1, arr[i].color2);
		for (int j = 0;j < arr[i].str.length();j++)
		{
			cout << arr[i].str[j];
			for (int k = 0;k < LetInterval;k++)
				cout << " ";
		}
	}
	SetColor(3, 2);
	for (int i = 0;i < widthBord;i++)
	{
		SetPos(startX - 2, startY - 2 + i);
		cout << "#";
		SetPos(startX + lengthBord - 2, startY - 2 + i);
		cout << "#";
	}
	for (int i = 0;i < lengthBord+1;i++)
	{
		SetPos(startX - 2 + i, startY - 2);
		cout << "#";
		SetPos(startX - 2 + i, startY + Interval*(size - 1) + 2);
		cout << "#";
	}


	int index = 0;
	char action=' ';

	SetColor(11, 0);
	SetPos(arr[index].x, arr[index].y);
	for (int j = 0;j < arr[index].str.length();j++)
	{
		cout << arr[index].str[j];
		if (j< arr[index].str.length() - 1)
			for (int k = 0;k < LetInterval;k++)
				cout << " ";
	};
	SetColor(12, 0);

	while (action != 13)
	{
		action = _getch();
		Beep (300 , 20);
		switch (action)
		{
		case 'w':
			if (index-1 >= 0)
			{
				index--;
				SetColor(11, 0);
				SetPos(arr[index].x, arr[index].y);
				for (int j = 0;j < arr[index].str.length();j++)
				{
					cout << arr[index].str[j];
					if (j< arr[index].str.length() - 1)
					for (int k = 0;k < LetInterval;k++)
						cout << " ";
				};
				SetColor(12, 0);
				SetPos(arr[index+1].x, arr[index+1].y);
				for (int j = 0;j < arr[index+1].str.length();j++)
				{
					cout << arr[index+1].str[j];
					if (j< arr[index-1].str.length() - 1)
					for (int k = 0;k < LetInterval;k++)
						cout << " ";
				};
				break;
			}
		case 's':
			if (index+1 < size)
			{
				index++;
				SetColor(11, 0);
				SetPos(arr[index].x, arr[index].y);
				for (int j = 0;j < arr[index].str.length();j++)
				{
					cout << arr[index].str[j];
					if (j< arr[index].str.length() - 1)
					for (int k = 0;k < LetInterval;k++)
						cout << " ";
				};
				SetColor(12, 0);
				SetPos(arr[index-1].x, arr[index-1].y);
				for (int j = 0;j < arr[index - 1].str.length();j++)
				{
					cout << arr[index - 1].str[j];
					if (j< arr[index-1].str.length() - 1)
					for (int k = 0;k < LetInterval;k++)
						cout << " ";
				};
				break;
			}

		default:
			break;
		}
	}

	SaveFile();
	SetColor(15, 0);
	return index;
}

void Menu::SetBorder()
{
	int max_size = 0;
	for (int i = 0;i < size;i++)
	{
		if (max_size < arr[i].str.length()) max_size = arr[i].str.length();
	}
	widthBord =Interval*(size-1)+4;
	lengthBord = max_size*(LetInterval+1)+2;
}
void Menu::SaveFile()
{
	FILE* file;
	file = fopen("Settings.txt","w");
	fprintf(file, "%d %d ", Interval, LetInterval);
	fprintf(file, "%d %d\n", startX, startY);
	for (int i = 0;i < size;i++)
		fprintf(file, "%s", arr[i].str.c_str());
	fclose(file);
}

int Menu::LoadFile()
{
	FILE* file;
	int _size = 0;
	char* buff = new char[120];
	file = fopen("Settings.txt", "r");
	if (file==NULL)
		return 0;
	while (fgets(buff, 120, file))_size++;
	rewind(file);
	fscanf(file, "%d %d %d %d\n", &Interval, &LetInterval, &startX, &startY);
	for (int i = 0;i < _size-1;i++) {
		fgets(buff, 120, file);
		arr=AddPoint(buff);
	}
	fclose(file);
	return 1;
}


Menu::~Menu()
{
}
