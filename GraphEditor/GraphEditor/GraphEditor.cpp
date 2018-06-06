#include "GraphEditor.h"
using namespace std;

GraphEditor::GraphEditor ( )
{
	GraphArr = new COORD[size];
	GraphArr[0] = { 5 ,5  };
}

GraphEditor GraphEditor::operator=( GraphEditor& obj )
{
	size = obj.size;
	for ( int i = 0; i < size; i++ )
		GraphArr[i] = obj.GraphArr[i];
	return GraphEditor (size , GraphArr);

}

void GraphEditor::SetPos (COORD obj)
{
	HANDLE hConsole = GetStdHandle (STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition (hConsole , obj);
}
void GraphEditor::SetPos (int x , int y)
{
	COORD position = { x , y }; //позиция x и y
	HANDLE hConsole = GetStdHandle (STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition (hConsole , position);
}
void GraphEditor::SetColor (int color1 , int color2)
{
	HANDLE hStdOut = GetStdHandle (STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute (hStdOut , (WORD)( ( color2 << 4 ) | color1 ));
}

/*    #####
     #     #
     #  O  #
	 #     #
      #####*/
void GraphEditor::DrawGraphs ( )
{
	HANDLE hStdOut = GetStdHandle (STD_OUTPUT_HANDLE);	
	for ( int i = 0; i < size; i++ )
	{
		SetPos (GraphArr[i]);
		cout << i;
		for ( int j = 0; j < 5; j++ )
		{
			SetPos (GraphArr[i].X - 2+j , GraphArr[i].Y - 2);
			cout << "#";
			SetPos (GraphArr[i].X - 2+j , GraphArr[i].Y + 2);
			cout << "#";
		}
		for ( int j = 0; j < 3; j++ )
		{
			SetPos (GraphArr[i].X - 3 , GraphArr[i].Y - 1 +j);
			cout << "#";
			SetPos (GraphArr[i].X + 3 , GraphArr[i].Y -1 +j);
			cout << "#";
		}
	}
}

void GraphEditor::SetLink ( )
{
	int i , j;
	SetPos (100 , 44);
	cout << "From: ";
	cin >> i;
	SetPos (102 , 45);
	cout << "To: ";
	cin >> j;
	arr[i][j] = sqrt (( GraphArr[j].X - GraphArr[i].X )*( GraphArr[j].X - GraphArr[i].X )/7*2 + ( GraphArr[j].Y - GraphArr[i].Y )*( GraphArr[j].Y - GraphArr[i].Y ));
	arr[j][i] = sqrt (( GraphArr[j].X - GraphArr[i].X )*( GraphArr[j].X - GraphArr[i].X )/7*2 + ( GraphArr[j].Y - GraphArr[i].Y )*( GraphArr[j].Y - GraphArr[i].Y ));
	SetPos (100 , 44);
	cout << "          ";
	SetPos (102 , 45);
	cout << "          ";
	
}
void GraphEditor::ShowLinks ( )

{
	double X_index;
	double Y_index;
	double Y_koef;

	bool** showed = new bool*[size];
	for ( int i = 0; i < size; i++ )
		showed[i] = new bool[size];
	for ( int i = 0; i < size;i++ )
	for ( int j = 0; j < size; j++ )
		showed[i][j] = false;

	for ( int i = 0; i < size; i++ )
	{
		for ( int j = 0; j < size; j++ )
		{
			if ( arr[i][j] != 0 && !showed[i][j] && !showed[j][i] )
			{
				X_index = GraphArr[i].X;
				Y_index = GraphArr[i].Y;
				Y_koef = sqrt (pow (GraphArr[i].X - GraphArr[j].X , 2) + pow (GraphArr[i].Y - GraphArr[j].Y , 2)) / abs (GraphArr[i].X - GraphArr[j].X);
				for ( int k = abs (GraphArr[i].X - GraphArr[j].X); k > 4; k-- )
				{
					if ( X_index > GraphArr[j].X && Y_index > GraphArr[j].Y ){
						X_index -= 1;
						Y_index -= Y_koef;
					}
					else if ( X_index > GraphArr[j].X && Y_index < GraphArr[j].Y ){
						X_index -= 1;
						Y_index += Y_koef;
					}
					else if ( X_index < GraphArr[j].X && Y_index > GraphArr[j].Y ){
						X_index += 1;
						Y_index -= Y_koef;
					}
					else if ( X_index < GraphArr[j].X && Y_index < GraphArr[j].Y ){
						X_index += 1;
						Y_index += Y_koef;
					}
					else if ( Y_index == GraphArr[j].Y && X_index > GraphArr[j].X ) X_index--;
					else if ( Y_index == GraphArr[j].Y && X_index < GraphArr[j].X ) X_index++;
					COORD temp = { static_cast<int>(X_index) , static_cast<int>(Y_index) };
					SetPos (temp);
					cout << "*";
				}
				for (int k = abs(GraphArr[i].Y - GraphArr[j].Y);k > 1;k--)
				{
					if ( X_index == GraphArr[j].X && Y_index > GraphArr[j].Y ) Y_index--;
					else if ( X_index == GraphArr[j].X && Y_index < GraphArr[j].Y ) Y_index++;
					COORD temp = { static_cast<int>(X_index) , static_cast<int>(Y_index) };
					SetPos(temp);
					cout << "*";
				}
				showed[i][j] = true;
				showed[j][i] = true;
			}
		}
	}

}
//void GraphEditor::ShowLinks()
//{
//	double X_index;
//	double Y_index;
//	double Y_koef;
//
//	bool** showed = new bool*[size];
//	for (int i = 0; i < size; i++)
//		showed[i] = new bool[size];
//	for (int i = 0; i < size;i++)
//		for (int j = 0; j < size; j++)
//			showed[i][j] = false;
//
//	for (int i = 0; i < size; i++)
//	{
//		for (int j = 0; j < size; j++)
//		{
//			if (arr[i][j] != 0 && !showed[i][j] && !showed[j][i])
//			{
//				X_index = GraphArr[i].X;
//				Y_index = GraphArr[i].Y;
//				Y_koef = sqrt(pow(GraphArr[i].X - GraphArr[j].X, 2) + pow(GraphArr[i].Y - GraphArr[j].Y, 2)) / abs(GraphArr[i].X - GraphArr[j].X);
//				if (X_index > GraphArr[j].X && Y_index > GraphArr[j].Y) {
//					for (int k = abs(GraphArr[i].X - GraphArr[j].X); k > 3; k--)
//					{
//						X_index -= 1;
//						Y_index -= Y_koef;
//						COORD temp = {static_cast<int>( X_index) , static_cast<int>(Y_index)};
//						SetPos(temp);
//						cout << "*";
//					}
//				}
//				if (X_index > GraphArr[j].X && Y_index < GraphArr[j].Y) {
//					for (int k = abs(GraphArr[i].X - GraphArr[j].X); k > 6; k--)
//					{
//						X_index -= 1;
//						Y_index += Y_koef;
//						COORD temp = { static_cast<int>(X_index) , static_cast<int>(Y_index)};
//						SetPos(temp);
//						cout << "*";
//					}
//				}
//				if (X_index < GraphArr[j].X && Y_index > GraphArr[j].Y) {
//					for (int k = abs(GraphArr[i].X - GraphArr[j].X); k > 3; k--)
//					{
//						X_index += 1;
//						Y_index -= Y_koef;
//						COORD temp = {static_cast<int>( X_index) , static_cast<int>(Y_index)};
//						SetPos(temp);
//						cout << "*";
//					}
//				}
//				if (X_index < GraphArr[j].X && Y_index < GraphArr[j].Y) {
//					for (int k = abs(GraphArr[i].X - GraphArr[j].X); k > 3; k--)
//					{
//						X_index += 1;
//						Y_index += Y_koef;
//						COORD temp = {static_cast<int>( X_index) , static_cast<int>(Y_index)};
//						SetPos(temp);
//						cout << "*";
//					}
//				}
//				else if (X_index == GraphArr[j].X && Y_index > GraphArr[j].Y) {
//					for (int k = abs(GraphArr[i].Y - GraphArr[j].Y); k > 1; k--)
//					{
//						Y_index--;
//						COORD temp = {static_cast<int>( X_index) , static_cast<int>(Y_index)};
//						SetPos(temp);
//						cout << "*";
//					}
//				}
//				else if (X_index == GraphArr[j].X && Y_index < GraphArr[j].Y) {
//					for (int k = abs(GraphArr[i].Y - GraphArr[j].Y); k > 1; k--)
//					{
//						Y_index++;
//						COORD temp = {static_cast<int>( X_index) , static_cast<int>(Y_index)};
//						SetPos(temp);
//						cout << "*";
//					}
//				}
//				else if (Y_index == GraphArr[j].Y && X_index > GraphArr[j].X) {
//					for (int k = abs(GraphArr[i].X - GraphArr[j].X); k > 1; k--)
//					{
//						X_index-=1;
//						COORD temp = {static_cast<int>( X_index) , static_cast<int>(Y_index)};
//						SetPos(temp);
//						cout << "*";
//					}
//				}
//				else if (Y_index == GraphArr[j].Y && X_index < GraphArr[j].X) {
//					for (int k = abs(GraphArr[i].X - GraphArr[j].X); k > 1; k--)
//					{
//						X_index += 1;
//						COORD temp = {static_cast<int>( X_index) , static_cast<int>(Y_index)};
//						SetPos(temp);
//						cout << "*";
//					}
//				}
//				}
//				showed[i][j] = true;
//				showed[j][i] = true;
//			}
//		}
//	}
void GraphEditor::ShowLink (int j,int i )
{
	double X_index;
	double Y_index;
	double Y_koef;
	if ( arr[i][j] != 0 )
	{
		X_index = GraphArr[i].X;
		Y_index = GraphArr[i].Y;
		Y_koef = sqrt (pow (GraphArr[i].X - GraphArr[j].X , 2) + pow (GraphArr[i].Y - GraphArr[j].Y , 2)) / abs (GraphArr[i].X - GraphArr[j].X);
		for ( int k = abs (GraphArr[i].X - GraphArr[j].X); k > 1; k-- )
		{
			X_index = GraphArr[i].X;
			Y_index = GraphArr[i].Y;
			Y_koef = sqrt(pow(GraphArr[i].X - GraphArr[j].X, 2) + pow(GraphArr[i].Y - GraphArr[j].Y, 2)) / abs(GraphArr[i].X - GraphArr[j].X);
			for (int k = abs(GraphArr[i].X - GraphArr[j].X); k > 4; k--)
			{
				if (X_index > GraphArr[j].X && Y_index > GraphArr[j].Y) {
					X_index -= 1;
					Y_index -= Y_koef;
				}
				else if (X_index > GraphArr[j].X && Y_index < GraphArr[j].Y) {
					X_index -= 1;
					Y_index += Y_koef;
				}
				else if (X_index < GraphArr[j].X && Y_index > GraphArr[j].Y) {
					X_index += 1;
					Y_index -= Y_koef;
				}
				else if (X_index < GraphArr[j].X && Y_index < GraphArr[j].Y) {
					X_index += 1;
					Y_index += Y_koef;
				}
				else if (Y_index == GraphArr[j].Y && X_index > GraphArr[j].X) X_index--;
				else if (Y_index == GraphArr[j].Y && X_index < GraphArr[j].X) X_index++;
				COORD temp = { static_cast<int>(X_index) , static_cast<int>(Y_index) };
				SetPos(temp);
				cout << "*";
			}
			for (int k = abs(GraphArr[i].Y - GraphArr[j].Y);k > 1;k--)
			{
				if (X_index == GraphArr[j].X && Y_index > GraphArr[j].Y) Y_index--;
				else if (X_index == GraphArr[j].X && Y_index < GraphArr[j].Y) Y_index++;
				COORD temp = { static_cast<int>(X_index) , static_cast<int>(Y_index) };
				SetPos(temp);
				cout << "*";
			}
		}
	}
}

void GraphEditor::InitializeArray ( )
{
	delete[]arr;
	arr = new int*[size];
	for ( int i = 0; i < size; i++ )
		arr[i] = new int[size];
	for ( int i = 0; i < size;i++ )
	for ( int j = 0; j < size; j++ )
		arr[i][j] = 0;
}
void GraphEditor::InitializeArray (int **_arr)
{
	delete[]arr;
	arr = new int*[size];
	for ( int i = 0; i < size; i++ )
		arr[i] = new int[size];
	for ( int i = 0; i < size; i++ )
	{
		arr[size - 1][i] = 0;
		for ( int j = 0; j < size-1; j++ )
			arr[i][j] = _arr[i][j];
	}
	
}
void GraphEditor::ShowArrayTable ( )
{
	SetPos (179 , 5);
	cout << "|";
	for ( int i = 0; i < size; i++ )
	{
		SetPos (180 + i*4 , 5);
		cout << i << " | ";
		SetPos (178, 6 + i*2);
		for ( int j = 0; j < size*4; j++ )
			cout << "-";
		SetPos (178 , 7 + i*2);
		cout << i << "| ";
	}
	for ( int i = 0; i < size; i++ )
	{
		for ( int j = 0; j < size; j++ )
		{
			SetPos (180 + j * 4 , 7 + i * 2);
			cout << arr[i][j] << " | ";
		}

	}
}

GraphEditor GraphEditor::AddGraph ()
{
	GraphEditor NewGraphArr;
	NewGraphArr.size = size + 1;
	NewGraphArr.GraphArr = new COORD[size + 1];
	for ( int i = 0; i < size; i++ )
		NewGraphArr.GraphArr[i] = GraphArr[i];


	NewGraphArr.GraphArr[size].X = GraphArr[size-1].X;
	NewGraphArr.GraphArr[size].Y = GraphArr[size-1].Y;
	char action='0';
	while ( action != 32 )
	{
		system ("cls");
		NewGraphArr.DrawGraphs ();
		action = _getch ( );
		switch ( action )
		{
			case 'w':
				if ( NewGraphArr.GraphArr[size].Y - 3 >= 0 )
					NewGraphArr.GraphArr[size].Y-=3;
				break;
			case 's':
					NewGraphArr.GraphArr[size].Y+=3;
					break;
			case 'a':
				if ( NewGraphArr.GraphArr[size].X - 3 >= 0 )
					NewGraphArr.GraphArr[size].X-=3;
				break;
			case 'd':
				if ( NewGraphArr.GraphArr[size].X + 3 <=264 )
					NewGraphArr.GraphArr[size].X+=3;
				break;

			default:
				break;
		}
	}
	NewGraphArr.DrawGraphs ();
	return NewGraphArr;
}

void GraphEditor::dijkstra ( )
{
	int start , end;
	SetPos (100 , 47);
	cout << "Start: ";
	cin >> start;
	SetPos (102 , 48);
	cout << "End: ";
	cin >> end;
	end++;
	SetPos (100 , 47);
	cout << "            ";
	SetPos (102 , 48);
	cout << "          ";
	int* dist = new int[end]; // расстояния от заданной(№0) вершины

	int* parent = new int[end]; // из какой вершины пришли, служит для восстановления маршрута

	// in_tree[i] == true, если для вершины i
	// уже посчитано минимальное расстояние
	bool* in_tree = new bool[end];
	for ( int i = 0; i < end; i++ )
		in_tree[i] = false;


	for ( int i = 0; i < end; i++ )
		dist[i] = INT_MAX; // машинная бесконечность, т. е. любое расстояние будет меньше данного

	dist[start] = 0;

	int cur = 0; //Вершина с которой работаем
	while ( !in_tree[cur] )
	{
		in_tree[cur] = true;

		for ( int i = 0; i < end; i++ )
		{
			// если между cur и i есть ребро
			if ( arr[cur][i] != 0 )
			{
				// считаем расстояние до вершины i:
				// расстояние до cur + вес ребра
				int d = dist[cur] + arr[cur][i];
				// если оно меньше, чем уже записанное
				if ( d < dist[i] )
				{
					SetColor (12 , 0);
					Sleep (1000);
					ShowLink (i ,cur);
					dist[i] = d;   // обновляем его
					parent[i] = cur; // и "родителя"
				}
			}
		}

		// ищем нерассмотренную вершину
		// с минимальным расстоянием
		int min_dist = INT_MAX;
		for ( int i = 0; i < end; i++ )
		{
			if ( !in_tree[i] && dist[i] < min_dist )
			{
				
				cur = i;
				min_dist = dist[i];
			}
		}
	}
	SetColor (11 , 2);
		for ( int i = end-1; i > start; ) {
			Sleep (1400);
			ShowLink (i , parent[i]);
			i = parent[i];	
		}

	SetColor (15 , 0);
}
GraphEditor::~GraphEditor ( )
{
	
}