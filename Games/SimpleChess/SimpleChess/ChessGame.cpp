#include "ChessGame.h"
#include "ChessFiguresG.h"

//White color - 15
//Black color - 4

ChessGame::ChessGame ( )
{
	bool temp;
	for ( int i = 0; i < 8; i++ )
	{
		for ( int j = 0; j < 8; j++ )
		{
			//Set StartPos for each field
			GameField[i][j].StartX = 1 + ( j*FieldSizeX ) % ( FieldSizeX * 8 );
			GameField[i][j].StartY = 1 + ( i*FieldSizeY );

		
			//Set if field Black or White
			temp = ( i + j + 1 )%2;
			if ( temp )
				GameField[i][j].color2 = 3;
		}
	}
	for ( int j = 0; j < 8; j++ )
	{
		//Set Black is not White
		GameField[0][j].White = 0;
		GameField[1][j].White = 0;

		//Set Color for Black
		GameField[0][j].color1 = 4;
		GameField[1][j].color1 = 4;

		//Set White is White
		GameField[6][j].White = 1;
		GameField[7][j].White = 1;

		//Set Color for White
		GameField[6][j].color1 = 15;
		GameField[7][j].color1 = 15;

		//Set Pawns
		GameField[1][j].piece = "Pawn";
		GameField[6][j].piece = "Pawn";
	}
	GameField[2][4].piece = "Pawn";
	GameField[2][4].White = 1;
	GameField[2][4].color1 = 15;

	//Set Rooks
	GameField[7][7].piece = "Rook";
	GameField[7][0].piece = "Rook";
	GameField[0][0].piece = "Rook";
	GameField[0][7].piece = "Rook";

	//Set Knights
	GameField[7][1].piece = "Knight";
	GameField[7][6].piece = "Knight";
	GameField[0][1].piece = "Knight";
	GameField[0][6].piece = "Knight";

	//Set Bishops
	GameField[7][2].piece = "Bishop";
	GameField[7][5].piece = "Bishop";
	GameField[0][2].piece = "Bishop";
	GameField[0][5].piece = "Bishop";

	//Set Queens
	GameField[7][3].piece = "Queen";
	GameField[0][3].piece = "Queen";

	//Set Kings
	GameField[7][4].piece = "King";
	GameField[0][4].piece = "King";
	
}

void ChessGame::DrawAllPieces ( )
{
	for ( int i = 0; i < 8; i++ )
	{
		for ( int j = 0; j < 8; j++ )
		{
			//Set Color Current Field
			SetColor (GameField[i][j].color1 , GameField[i][j].color2);

			if ( i == CurFieldY && j == CurFieldX )
				SetColor (14 , GameField[i][j].color2);
			//Draw Current Field
			DrawField (GameField[i][j].piece,i,j);
		}
	}
	SetPos (180 , 50);
	SetColor (15 , 0);
}
void ChessGame::Walk ()
{
	char action = ' ';
	while ( action != 13)
	{
		action = _getch ( );
		switch ( action )
		{
			case 'w':
				if ( CurFieldY > 0 ){
					SetColor (GameField[CurFieldY][CurFieldX].color1 , GameField[CurFieldY][CurFieldX].color2);
					DrawField (GameField[CurFieldY][CurFieldX].piece , CurFieldY , CurFieldX);
					CurFieldY--;
				} break;
			case 's':
				if ( CurFieldY < 7 ){
					SetColor (GameField[CurFieldY][CurFieldX].color1 , GameField[CurFieldY][CurFieldX].color2);
					DrawField (GameField[CurFieldY][CurFieldX].piece , CurFieldY , CurFieldX);
					CurFieldY++;
				} break;
			case 'a':
				if ( CurFieldX>0 ){
					SetColor (GameField[CurFieldY][CurFieldX].color1 , GameField[CurFieldY][CurFieldX].color2);
					DrawField (GameField[CurFieldY][CurFieldX].piece , CurFieldY , CurFieldX);
					CurFieldX--;
				}break;
			case 'd':
				if ( CurFieldX < 7 ){
					SetColor (GameField[CurFieldY][CurFieldX].color1 , GameField[CurFieldY][CurFieldX].color2);
					DrawField (GameField[CurFieldY][CurFieldX].piece , CurFieldY , CurFieldX);
					CurFieldX++;
				}break;
			default:
				break;
		}
		SetColor (14 , GameField[CurFieldY][CurFieldX].color2);
		DrawField (GameField[CurFieldY][CurFieldX].piece , CurFieldY , CurFieldX);	
	}
}
void ChessGame::Move ( )
{
	ChessGame Temp;
		for ( int i = 0; i < 8; i++ )
		for ( int j = 0; j < 8; j++ )
			Temp.GameField[i][j] = GameField[i][j];

	ScanMap ();
	bool MoveSuccessful = 0;
	if(!Check)
	if (GameField[CurFieldY][CurFieldX].White == WhiteStep)
	{
		if (GameField[CurFieldY][CurFieldX].piece == "Pawn")
			MoveSuccessful = PawnMove();

		if (GameField[CurFieldY][CurFieldX].piece == "Bishop")
			MoveSuccessful = BishopMove();

		if (GameField[CurFieldY][CurFieldX].piece == "Knight")
			MoveSuccessful = KnightMove();

		if (GameField[CurFieldY][CurFieldX].piece == "Rook")
			MoveSuccessful = RookMove();

		if (GameField[CurFieldY][CurFieldX].piece == "Queen")
			MoveSuccessful = QueenMove();

		if (GameField[CurFieldY][CurFieldX].piece == "King")
			MoveSuccessful = KingMove();

		if (MoveSuccessful) {
			ScanMap();
			WhiteStep = !WhiteStep;
			Reverse();

		}
	}

		if ( Check )
		{
			DrawAllPieces();
			SetPos(100, 30);
			cout << "CHECK-rEVERSE";
			system("pause");
			for ( int i = 0; i < 8; i++ )
			for ( int j = 0; j < 8; j++ )
			{
				if ( WhiteStep == 1 && GameField[i][j].White == 1 )
					FakeWalk (GameField[i][j].piece , i , j);
				if (WhiteStep == 0 && GameField[i][j].White == 0)
					FakeWalk(GameField[i][j].piece, i, j);
			}
			SetPos(101, 31);
			cout << "CHECK-rEVERSE";
			SetPos(101, 32);
			cout << "CHECK: " << Check;
			SetPos(101, 33);
			cout << "Can Avoid: " << CanAvoid;
		}
		if ( CanAvoid && Check )
		{
			SetPos (85 , 52);
			cout << "Can Avoid";
			while ( Check ){
				for ( int i = 0; i < 8; i++ )
				for ( int j = 0; j < 8; j++ )
					Temp.GameField[i][j] = GameField[i][j];

				Walk ( );	
				if ( GameField[CurFieldY][CurFieldX].White == WhiteStep )
				{
					if ( GameField[CurFieldY][CurFieldX].piece == "Pawn" )
						PawnMove ( );

					if ( GameField[CurFieldY][CurFieldX].piece == "Bishop" )
						BishopMove ( );

					if ( GameField[CurFieldY][CurFieldX].piece == "Knight" )
						KnightMove ( );

					if ( GameField[CurFieldY][CurFieldX].piece == "Rook" )
						RookMove ( );

					if ( GameField[CurFieldY][CurFieldX].piece == "Queen" )
						QueenMove ( );

					if ( GameField[CurFieldY][CurFieldX].piece == "King" )
						KingMove ( );
				}
				ScanMap ( );
				if ( Check )
				{
					for ( int i = 0; i < 8; i++ )
					for ( int j = 0; j < 8; j++ )
						GameField[i][j] = Temp.GameField[i][j];
				
					
				}	
				if ( !Check )
				{
					Reverse ();
					WhiteStep = !WhiteStep;
				}
				DrawAllPieces ();
			}
		}
		else if (Check )
		{
			SetPos (80 , 50);
			cout << "CHECKMATE";
			system ("pause");
		}
}
bool ChessGame::PawnMove ()
{
	ChessGame Temp;
	Temp.GameField[CurFieldY][CurFieldX].color2 = 2;
	Temp.CurFieldX = CurFieldX;
	Temp.CurFieldY = CurFieldY;
	int tempX = CurFieldX , tempY = CurFieldY;

	for ( int i = 0; i < 8;i++ )
	for ( int j = 0; j < 8; j++ )
		Temp.GameField[i][j] = GameField[i][j];

	//Check for free moves
	if ( GameField[CurFieldY - 1][CurFieldX].piece == " " )
	{
		if ( CurFieldY == 6 && GameField[CurFieldY - 2][CurFieldX].piece == " " )
		{
			Temp.GameField[CurFieldY - 2][CurFieldX].color2 = 2;
		}
		Temp.GameField[CurFieldY - 1][CurFieldX].color2 = 2;
	}
	//Check for attack in left
	if ( GameField[CurFieldY - 1][CurFieldX - 1].piece != " " && GameField[CurFieldY - 1][CurFieldX - 1].White != GameField[CurFieldY][CurFieldX].White )
		Temp.GameField[CurFieldY - 1][CurFieldX-1].color2 = 2;
	//Check for attack in right
	if ( GameField[CurFieldY - 1][CurFieldX + 1].piece != " " && GameField[CurFieldY - 1][CurFieldX + 1].White != GameField[CurFieldY][CurFieldX].White )
		Temp.GameField[CurFieldY - 1][CurFieldX + 1].color2 = 2;

	//Check for available move
	bool CheckMove = 0;
	for ( int i = 0; i < 8; i++ )
	for ( int j = 0; j < 8; j++ )
	if ( Temp.GameField[i][j].color2 == 2 )
		CheckMove = 1;
	if ( CheckMove == 0 )
		return 0;

	//Redraw New Temp Map
	Temp.DrawAllPieces ( );
	Temp.Walk ( );



	//Check move of walk
	if ( Temp.GameField[Temp.CurFieldY][Temp.CurFieldX].color2 == 2 )
	{
		GameField[Temp.CurFieldY][Temp.CurFieldX].piece = GameField[tempY][tempX].piece;
		GameField[Temp.CurFieldY][Temp.CurFieldX].White = GameField[tempY][tempX].White;
		GameField[Temp.CurFieldY][Temp.CurFieldX].color1 = GameField[tempY][tempX].color1;
		GameField[tempY][tempX].piece = " ";
		GameField[tempY][tempX].White = 2;
		GameField[Temp.CurFieldY][Temp.CurFieldX].White = WhiteStep;
		CurFieldX = Temp.CurFieldX;
		CurFieldY = Temp.CurFieldY;

		return 1;
	}
	return 0;
}
bool ChessGame::BishopMove ( )
{
	int i , j;
	ChessGame Temp;
	Temp.CurFieldX = CurFieldX;
	Temp.CurFieldY = CurFieldY;
	int tempX = CurFieldX , tempY = CurFieldY;

	for ( int i = 0; i < 8; i++ )
	for ( int j = 0; j < 8; j++ )
		Temp.GameField[i][j] = GameField[i][j];

	//Left-Down check move
	i = CurFieldY;
	j = CurFieldX;
	while ( i <= 6 && j > 0 )
	{
		
		Temp.GameField[++i][--j].color2 = 2;
		if ( Temp.GameField[i][j].piece != " " )
		{
			if ( Temp.GameField[i][j].White != Temp.GameField[CurFieldY][CurFieldX].White )
				break;
			else
				Temp.GameField[i][j].color2 = GameField[i][j].color2;
			break;
		}
			
	}
	
	//Right-Down check move
	i = CurFieldY;
	j = CurFieldX;
	while ( i <= 6 && j <=6 )
	{
		Temp.GameField[++i][++j].color2 = 2;
		if ( Temp.GameField[i][j].piece != " " )
		{
			if ( Temp.GameField[i][j].White != Temp.GameField[CurFieldY][CurFieldX].White )
				break;
			else
				Temp.GameField[i][j].color2 = GameField[i][j].color2;
			break;
		}
	}

	//Left-Up check move
	i = CurFieldY;
	j = CurFieldX;
	while ( i > 0 && j > 0 )
	{
		Temp.GameField[--i][--j].color2 = 2;
		if ( Temp.GameField[i][j].piece != " " )
		{
			if ( Temp.GameField[i][j].White != Temp.GameField[CurFieldY][CurFieldX].White )
				break;
			else
				Temp.GameField[i][j].color2 = GameField[i][j].color2;
			break;
		}
	}

	//Right-Up check move
	i = CurFieldY;
	j = CurFieldX;
	while ( i > 0 && j <= 6 )
	{
		Temp.GameField[--i][++j].color2 = 2;
		if ( Temp.GameField[i][j].piece != " " )
		{
			if ( Temp.GameField[i][j].White != Temp.GameField[CurFieldY][CurFieldX].White )
				break;
			else
				Temp.GameField[i][j].color2 = GameField[i][j].color2;
			break;
		}
	}



	//Check for available move
	bool CheckMove = 0;
	for ( int i = 0; i < 8; i++ )
	for ( int j = 0; j < 8; j++ )
	if ( Temp.GameField[i][j].color2 == 2 )
		CheckMove = 1;
	if ( CheckMove == 0 )
		return 0;

	//Redraw New Temp Map
	Temp.DrawAllPieces ();
	Temp.Walk ();

	//Check move of walk
	if ( Temp.GameField[Temp.CurFieldY][Temp.CurFieldX].color2 == 2 )
	{
		GameField[Temp.CurFieldY][Temp.CurFieldX].piece = Temp.GameField[tempY][tempX].piece;
		GameField[Temp.CurFieldY][Temp.CurFieldX].White = Temp.GameField[tempY][tempX].White;
		GameField[Temp.CurFieldY][Temp.CurFieldX].color1 = Temp.GameField[tempY][tempX].color1;
		GameField[tempY][tempX].White = 2;
		GameField[Temp.CurFieldY][Temp.CurFieldX].White = WhiteStep;
		GameField[tempY][tempX].piece = " ";
		CurFieldX = Temp.CurFieldX;
		CurFieldY = Temp.CurFieldY;
		return 1;
	}
	return 0;
}
bool ChessGame::KnightMove ()
{
	ChessGame Temp;
	Temp.CurFieldX = CurFieldX;
	Temp.CurFieldY = CurFieldY;
	int tempX = CurFieldX , tempY = CurFieldY;

	for ( int i = 0; i < 8; i++ )
	for ( int j = 0; j < 8; j++ )
		Temp.GameField[i][j] = GameField[i][j];

	// up-up-left
	if ( CurFieldY - 2 >= 0 && CurFieldX - 1 >= 0 )
	if ( Temp.GameField[CurFieldY - 2][CurFieldX - 1].White != GameField[CurFieldY][CurFieldX].White )
		Temp.GameField[CurFieldY-2][CurFieldX-1].color2 = 2;

	// up-up-right
	if ( CurFieldY - 2 >= 0 && CurFieldX + 1 < 8 )
	if ( Temp.GameField[CurFieldY - 2][CurFieldX + 1].White != GameField[CurFieldY][CurFieldX].White )
		Temp.GameField[CurFieldY - 2][CurFieldX + 1].color2 = 2;

	// up-left-left
	if ( CurFieldY - 1 >= 0 && CurFieldX - 2 >=0 )
	if ( Temp.GameField[CurFieldY - 1][CurFieldX - 2].White != GameField[CurFieldY][CurFieldX].White )
		Temp.GameField[CurFieldY - 1][CurFieldX - 2].color2 = 2;

	// down-left-left
	if ( CurFieldY + 1 < 8 && CurFieldX - 2 >= 0 )
	if ( Temp.GameField[CurFieldY + 1][CurFieldX - 2].White != GameField[CurFieldY][CurFieldX].White )
		Temp.GameField[CurFieldY + 1][CurFieldX - 2].color2 = 2;

	// up-right-right
	if ( CurFieldY - 1 >= 0 && CurFieldX + 2 < 8 )
	if ( Temp.GameField[CurFieldY - 1][CurFieldX + 2].White != GameField[CurFieldY][CurFieldX].White )
		Temp.GameField[CurFieldY - 1][CurFieldX + 2].color2 = 2;

	// down-right-right
	if ( CurFieldY + 1 < 8 && CurFieldX + 2 < 8 )
	if ( Temp.GameField[CurFieldY + 1][CurFieldX + 2].White != GameField[CurFieldY][CurFieldX].White )
		Temp.GameField[CurFieldY + 1][CurFieldX + 2].color2 = 2;

	// down-down-right
	if ( CurFieldY + 2 < 8 && CurFieldX + 1 < 8 )
	if ( Temp.GameField[CurFieldY + 2][CurFieldX + 1].White != GameField[CurFieldY][CurFieldX].White )
		Temp.GameField[CurFieldY + 2][CurFieldX + 1].color2 = 2;

	// down-down-left
	if ( CurFieldY + 2 < 8 && CurFieldX - 1 >= 0 )
	if ( Temp.GameField[CurFieldY + 2][CurFieldX - 1].White != GameField[CurFieldY][CurFieldX].White )
		Temp.GameField[CurFieldY + 2][CurFieldX - 1].color2 = 2;


	//Check for available move
	bool CheckMove = 0;
	for ( int i = 0; i < 8; i++ )
	for ( int j = 0; j < 8; j++ )
	if ( Temp.GameField[i][j].color2 == 2 )
		CheckMove = 1;
	if ( CheckMove == 0 )
		return 0;

	//Redraw New Temp Map
	Temp.DrawAllPieces ();
	Temp.Walk ();

	//Check move of walk
	if ( Temp.GameField[Temp.CurFieldY][Temp.CurFieldX].color2 == 2 )
	{
		GameField[Temp.CurFieldY][Temp.CurFieldX].piece = Temp.GameField[tempY][tempX].piece;
		GameField[Temp.CurFieldY][Temp.CurFieldX].White = Temp.GameField[tempY][tempX].White;
		GameField[Temp.CurFieldY][Temp.CurFieldX].color1 = Temp.GameField[tempY][tempX].color1;
		GameField[tempY][tempX].White = 2;
		GameField[Temp.CurFieldY][Temp.CurFieldX].White = WhiteStep;
		GameField[tempY][tempX].piece = " ";
		CurFieldX = Temp.CurFieldX;
		CurFieldY = Temp.CurFieldY;
		return 1;
	}
	return 0;

}
bool ChessGame::RookMove ( )
{
	ChessGame Temp;
	Temp.CurFieldX = CurFieldX;
	Temp.CurFieldY = CurFieldY;
	int tempX = CurFieldX , tempY = CurFieldY;

	for ( int i = 0; i < 8; i++ )
	for ( int j = 0; j < 8; j++ )
		Temp.GameField[i][j] = GameField[i][j];

	    //Right
	for (int i = CurFieldX+1; i < 8; i++ )
	{
		Temp.GameField[CurFieldY][i].color2 = 2;
		if ( Temp.GameField[CurFieldY][i].piece != " " )
		{
			if ( Temp.GameField[CurFieldY][i].White != Temp.GameField[CurFieldY][CurFieldX].White )
				break;
			else
				Temp.GameField[CurFieldY][i].color2 = GameField[CurFieldY][i].color2;
			break;
		}
	}

		//Left
	for ( int i = CurFieldX - 1; i >= 0; i-- )
	{
		Temp.GameField[CurFieldY][i].color2 = 2;
		if ( Temp.GameField[CurFieldY][i].piece != " " )
		{
			if ( Temp.GameField[CurFieldY][i].White != Temp.GameField[CurFieldY][CurFieldX].White )
				break;
			else
				Temp.GameField[CurFieldY][i].color2 = GameField[CurFieldY][i].color2;
			break;
		}
	}

	//Up
	for ( int i = CurFieldY - 1; i >= 0; i-- )
	{
		Temp.GameField[i][CurFieldX].color2 = 2;
		if ( Temp.GameField[i][CurFieldX].piece != " " )
		{
			if ( Temp.GameField[i][CurFieldX].White != Temp.GameField[CurFieldY][CurFieldX].White )
				break;
			else
				Temp.GameField[i][CurFieldX].color2 = GameField[i][CurFieldX].color2;
			break;
		}
	}
	//Down
	for ( int i = CurFieldY + 1; i < 8; i++ )
	{
		Temp.GameField[i][CurFieldX].color2 = 2;
		if ( Temp.GameField[i][CurFieldX].piece != " " )
		{
			if ( Temp.GameField[i][CurFieldX].White != Temp.GameField[CurFieldY][CurFieldX].White )
				break;
			else
				Temp.GameField[i][CurFieldX].color2 = GameField[i][CurFieldX].color2;
			break;
		}
	}

	//Check for available move
	bool CheckMove = 0;
	for ( int i = 0; i < 8; i++ )
	for ( int j = 0; j < 8; j++ )
	if ( Temp.GameField[i][j].color2 == 2 )
		CheckMove = 1;
	if ( CheckMove == 0 )
		return 0;

	//Redraw New Temp Map
	Temp.DrawAllPieces ();
	Temp.Walk ();

	//Check move of walk
	if ( Temp.GameField[Temp.CurFieldY][Temp.CurFieldX].color2 == 2 )
	{
		GameField[Temp.CurFieldY][Temp.CurFieldX].piece = Temp.GameField[tempY][tempX].piece;
		GameField[Temp.CurFieldY][Temp.CurFieldX].White = Temp.GameField[tempY][tempX].White;
		GameField[Temp.CurFieldY][Temp.CurFieldX].color1 = Temp.GameField[tempY][tempX].color1;
		GameField[tempY][tempX].White = 2;
		GameField[Temp.CurFieldY][Temp.CurFieldX].White = WhiteStep;
		GameField[tempY][tempX].piece = " ";
		CurFieldX = Temp.CurFieldX;
		CurFieldY = Temp.CurFieldY;
		return 1;
	}
	return 0;
}
bool ChessGame::QueenMove ( )
{

	ChessGame Temp;
	Temp.CurFieldX = CurFieldX;
	Temp.CurFieldY = CurFieldY;
	int tempX = CurFieldX , tempY = CurFieldY;

	for ( int i = 0; i < 8; i++ )
	for ( int j = 0; j < 8; j++ )
		Temp.GameField[i][j] = GameField[i][j];

	//Right
	for ( int i = CurFieldX + 1; i < 8; i++ )
	{
		if ( Temp.GameField[CurFieldY][i].color2!=0 )
			Temp.GameField[CurFieldY][i].color2 = 7;
		else
			Temp.GameField[CurFieldY][i].color2 = 8;

		//Temp.GameField[CurFieldY][i].color2 = 2;

		if ( Temp.GameField[CurFieldY][i].piece != " " )
		{
			if ( Temp.GameField[CurFieldY][i].White != Temp.GameField[CurFieldY][CurFieldX].White )
				break;
			else
				Temp.GameField[CurFieldY][i].color2 = GameField[CurFieldY][i].color2;
			break;
		}
	}

	//Left
	for ( int i = CurFieldX - 1; i >= 0; i-- )
	{
		Temp.GameField[CurFieldY][i].color2 = 2;
		if ( Temp.GameField[CurFieldY][i].piece != " " )
		{
			if ( Temp.GameField[CurFieldY][i].White != Temp.GameField[CurFieldY][CurFieldX].White )
				break;
			else
				Temp.GameField[CurFieldY][i].color2 = GameField[CurFieldY][i].color2;
			break;
		}
	}

	//Up
	for ( int i = CurFieldY - 1; i >= 0; i-- )
	{
		Temp.GameField[i][CurFieldX].color2 = 2;
		if ( Temp.GameField[i][CurFieldX].piece != " " )
		{
			if ( Temp.GameField[i][CurFieldX].White != Temp.GameField[CurFieldY][CurFieldX].White )
				break;
			else
				Temp.GameField[i][CurFieldX].color2 = GameField[i][CurFieldX].color2;
			break;
		}
	}
	//Down
	for ( int i = CurFieldY + 1; i < 8; i++ )
	{
		Temp.GameField[i][CurFieldX].color2 = 2;
		if ( Temp.GameField[i][CurFieldX].piece != " " )
		{
			if ( Temp.GameField[i][CurFieldX].White != Temp.GameField[CurFieldY][CurFieldX].White )
				break;
			else
				Temp.GameField[i][CurFieldX].color2 = GameField[i][CurFieldX].color2;
			break;
		}
	}

	int i , j;
	//Left-Down check move
	i = CurFieldY;
	j = CurFieldX;
	while ( i <= 6 && j > 0 )
	{

		Temp.GameField[++i][--j].color2 = 2;
		if ( Temp.GameField[i][j].piece != " " )
		{
			if ( Temp.GameField[i][j].White != Temp.GameField[CurFieldY][CurFieldX].White )
				break;
			else
				Temp.GameField[i][j].color2 = GameField[i][j].color2;
			break;
		}

	}

	//Right-Down check move
	i = CurFieldY;
	j = CurFieldX;
	while ( i <= 6 && j <= 6 )
	{
		Temp.GameField[++i][++j].color2 = 2;
		if ( Temp.GameField[i][j].piece != " " )
		{
			if ( Temp.GameField[i][j].White != Temp.GameField[CurFieldY][CurFieldX].White )
				break;
			else
				Temp.GameField[i][j].color2 = GameField[i][j].color2;
			break;
		}
	}

	//Left-Up check move
	i = CurFieldY;
	j = CurFieldX;
	while ( i > 0 && j > 0 )
	{
		Temp.GameField[--i][--j].color2 = 2;
		if ( Temp.GameField[i][j].piece != " " )
		{
			if ( Temp.GameField[i][j].White != Temp.GameField[CurFieldY][CurFieldX].White )
				break;
			else
				Temp.GameField[i][j].color2 = GameField[i][j].color2;
			break;
		}
	}

	//Right-Up check move
	i = CurFieldY;
	j = CurFieldX;
	while ( i > 0 && j <= 6 )
	{
		Temp.GameField[--i][++j].color2 = 2;
		if ( Temp.GameField[i][j].piece != " " )
		{
			if ( Temp.GameField[i][j].White != Temp.GameField[CurFieldY][CurFieldX].White )
				break;
			else
				Temp.GameField[i][j].color2 = GameField[i][j].color2;
			break;
		}
	}


	//Check for available move
	bool CheckMove = 0;
	for ( int i = 0; i < 8; i++ )
	for ( int j = 0; j < 8; j++ )
	if ( Temp.GameField[i][j].color2 == 2 )
		CheckMove = 1;
	if ( CheckMove == 0 )
		return 0;



	//Redraw New Temp Map
	Temp.DrawAllPieces ();
	Temp.Walk ();

	//Check move of walk
	if ( Temp.GameField[Temp.CurFieldY][Temp.CurFieldX].color2 == 2 )
	{
		GameField[Temp.CurFieldY][Temp.CurFieldX].piece = Temp.GameField[tempY][tempX].piece;
		GameField[Temp.CurFieldY][Temp.CurFieldX].White = Temp.GameField[tempY][tempX].White;
		GameField[Temp.CurFieldY][Temp.CurFieldX].color1 = Temp.GameField[tempY][tempX].color1;
		GameField[tempY][tempX].White = 2;
		GameField[Temp.CurFieldY][Temp.CurFieldX].White = WhiteStep;
		GameField[tempY][tempX].piece = " ";
		CurFieldX = Temp.CurFieldX;
		CurFieldY = Temp.CurFieldY;
		return 1;
	}
	return 0;
}
bool ChessGame::KingMove ( )
{
	ChessGame Temp;
	Temp.GameField[CurFieldY][CurFieldX].color2 = 2;
	Temp.CurFieldX = CurFieldX;
	Temp.CurFieldY = CurFieldY;
	int tempX = CurFieldX , tempY = CurFieldY;

	for ( int i = 0; i < 8; i++ )
	for ( int j = 0; j < 8; j++ )
		Temp.GameField[i][j] = GameField[i][j];


	//Check for attack in Top-left
	if ( CurFieldY - 1 >= 0 && CurFieldX - 1 >=0)
	if (GameField[CurFieldY - 1][CurFieldX - 1].White != GameField[CurFieldY][CurFieldX].White )
		Temp.GameField[CurFieldY - 1][CurFieldX - 1].color2 = 2;

	//Check for attack in Top-right
	if ( CurFieldY - 1 >= 0 && CurFieldX + 1 < 8 )
	if (GameField[CurFieldY - 1][CurFieldX + 1].White != GameField[CurFieldY][CurFieldX].White )
		Temp.GameField[CurFieldY - 1][CurFieldX + 1].color2 = 2;

    //Check for attack in Top-left
	if (CurFieldX - 1 >= 0 )
	if (GameField[CurFieldY][CurFieldX - 1].White != GameField[CurFieldY][CurFieldX].White )
		Temp.GameField[CurFieldY][CurFieldX - 1].color2 = 2;


	//Check for attack in Top-left
	if (CurFieldX + 1 < 8 )
	if (GameField[CurFieldY][CurFieldX + 1].White != GameField[CurFieldY][CurFieldX].White )
		Temp.GameField[CurFieldY][CurFieldX + 1].color2 = 2;

	//Check for attack in Top-left
	if ( CurFieldY + 1 < 8 && CurFieldX - 1 >=0 )
	if (GameField[CurFieldY +1][CurFieldX - 1].White != GameField[CurFieldY][CurFieldX].White )
		Temp.GameField[CurFieldY +1][CurFieldX - 1].color2 = 2;

	//Check for attack in Top-left
	if ( CurFieldY + 1 < 8 && CurFieldX + 1 < 8 )
	if (GameField[CurFieldY +1][CurFieldX + 1].White != GameField[CurFieldY][CurFieldX].White )
		Temp.GameField[CurFieldY +1][CurFieldX + 1].color2 = 2;

	//Check for attack in Top-left
	if ( CurFieldY - 1 >= 0)
	if ( GameField[CurFieldY -1][CurFieldX].White != GameField[CurFieldY][CurFieldX].White )
		Temp.GameField[CurFieldY -1][CurFieldX].color2 = 2;

	//Check for attack in Top-left
	if ( CurFieldY + 1 < 8 )
	if (	GameField[CurFieldY +1][CurFieldX].White != GameField[CurFieldY][CurFieldX].White )
		Temp.GameField[CurFieldY +1][CurFieldX].color2 = 2;
	


	//Check for available move
	bool CheckMove = 0;
	for ( int i = 0; i < 8; i++ )
	for ( int j = 0; j < 8; j++ )
	if ( Temp.GameField[i][j].color2 == 2 )
		CheckMove = 1;
	if ( CheckMove == 0 )
		return 0;

	//Redraw New Temp Map
	Temp.DrawAllPieces ();
	Temp.Walk ();

	//Check move of walk
	if ( Temp.GameField[Temp.CurFieldY][Temp.CurFieldX].color2 == 2 )
	{
		GameField[Temp.CurFieldY][Temp.CurFieldX].piece = Temp.GameField[tempY][tempX].piece;
		GameField[Temp.CurFieldY][Temp.CurFieldX].White = Temp.GameField[tempY][tempX].White;
		GameField[Temp.CurFieldY][Temp.CurFieldX].color1 = Temp.GameField[tempY][tempX].color1;
		GameField[tempY][tempX].piece = " ";
		GameField[tempY][tempX].White = 2;
		GameField[Temp.CurFieldY][Temp.CurFieldX].White = WhiteStep;
		CurFieldX = Temp.CurFieldX;
		CurFieldY = Temp.CurFieldY;
		return 1;
	}
	return 0;
}

//void ChessGame::PawnMoveScan (ChessGame& map,int curY, int curX)
//{
//	ChessGame Temp;
//	Temp.CurFieldX = curX;
//	Temp.CurFieldY = curY;
//	int tempX = curX , tempY = curY;
//
//	for ( int i = 0; i < 8; i++ )
//	for ( int j = 0; j < 8; j++ )
//		Temp.GameField[i][j] = map.GameField[i][j];
//
//	//Check for attack in left
//	if (GameField[curY - 1][curX - 1].White != GameField[curY][curX].White )
//		Temp.GameField[curY - 1][curX - 1].color2 = 2;
//	//Check for attack in right
//	if (GameField[curY - 1][curX + 1].White != GameField[curY][curX].White )
//		Temp.GameField[curY - 1][curX + 1].color2 = 2;
//
//
//	Temp.DrawAllPieces ( );
//	system ("pause");
//	//Check move of walk
//	for ( int i = 0; i < 8;i++ )
//	for ( int j = 0; j < 8; j++ )
//	{
//		if ( Temp.GameField[i][j].color2 == 2 )
//		{
//			if (WhiteStep == 1 )
//				AttackMap[i][j] = 1;
//			if ( WhiteStep == 0 )
//				AttackMap[i][j] = 2;
//			if ( AttackMap[i][j] == 1 && WhiteStep == 0 || AttackMap[i][j] == 2 && WhiteStep == 1 )
//				AttackMap[i][j] = 3;
//		}
//	}
//}


// White = 10 GREEN
// Black = 9 BLUE
// Black+White = 12 RED
void ChessGame::PawnMoveScan (ChessGame& map , int curY , int curX)
{
	map.CurFieldX = curX;
	map.CurFieldY = curY;
	int tempX = curX , tempY = curY;

	if ( map.GameField[curY][curX].White == 1 ){
		//Check for attack in left White
		if ( curY - 1 >= 0 && curX - 1 >= 0 )
		if ( map.GameField[curY - 1][curX - 1].White != map.GameField[curY][curX].White )
		if ( map.GameField[curY - 1][curX - 1].color2 == 12 );
		else if ( map.GameField[curY][curX].White == 0 )
		{
			if ( map.GameField[curY - 1][curX - 1].color2 == 10 )
				map.GameField[curY - 1][curX - 1].color2 = 12;
			else
				map.GameField[curY - 1][curX - 1].color2 = 9;
		}
		else if ( map.GameField[curY][curX].White == 1 )
		{
			if ( map.GameField[curY - 1][curX - 1].color2 == 9 )
				map.GameField[curY - 1][curX - 1].color2 = 12;
			else
				map.GameField[curY - 1][curX - 1].color2 = 10;
		}

		//Check for attack in right White
		if ( curY - 1 >= 0 && curX + 1 >= 0 )
		if ( map.GameField[curY - 1][curX + 1].White != map.GameField[curY][curX].White )
		if ( map.GameField[curY - 1][curX + 1].color2 == 12 );
		else if ( map.GameField[curY][curX].White == 0 )
		{
			if ( map.GameField[curY - 1][curX + 1].color2 == 10 )
				map.GameField[curY - 1][curX + 1].color2 = 12;
			else
				map.GameField[curY - 1][curX + 1].color2 = 9;
		}
		else if ( map.GameField[curY][curX].White == 1 )
		{
			if ( map.GameField[curY - 1][curX + 1].color2 == 9 )
				map.GameField[curY - 1][curX + 1].color2 = 12;
			else
				map.GameField[curY - 1][curX + 1].color2 = 10;
		}
	}

	if ( map.GameField[curY][curX].White == 0 ){
		//Check for attack in left Black

		if ( curY + 1 < 8 && curX - 1 < 8 )
		if ( map.GameField[curY + 1][curX - 1].White != map.GameField[curY][curX].White )
		if ( map.GameField[curY + 1][curX - 1].color2 == 12 );
		else if ( map.GameField[curY][curX].White == 0 )
		{
			if ( map.GameField[curY + 1][curX - 1].color2 == 10 )
				map.GameField[curY + 1][curX - 1].color2 = 12;
			else
				map.GameField[curY + 1][curX - 1].color2 = 9;
		}
		else if ( map.GameField[curY][curX].White == 1 )
		{
			if ( map.GameField[curY + 1][curX - 1].color2 == 9 )
				map.GameField[curY + 1][curX - 1].color2 = 12;
			else
				map.GameField[curY + 1][curX - 1].color2 = 10;
		}
		//Check for attack in right Black

		{
			if ( curY + 1 < 8 && curX + 1 < 8 )
			if ( map.GameField[curY + 1][curX + 1].White != map.GameField[curY][curX].White )
			if ( map.GameField[curY - 1][curX - 1].color2 == 12 );
			else if ( map.GameField[curY][curX].White == 0 )
			{
				if ( map.GameField[curY + 1][curX + 1].color2 == 10 )
					map.GameField[curY + 1][curX + 1].color2 = 12;
				else
					map.GameField[curY + 1][curX + 1].color2 = 9;
			}
			else if ( map.GameField[curY][curX].White == 1 )
			{
				if ( map.GameField[curY + 1][curX + 1].color2 == 9 )
					map.GameField[curY + 1][curX + 1].color2 = 12;
				else
					map.GameField[curY + 1][curX + 1].color2 = 10;
			}
		}
	}

	//map.DrawAllPieces ();
	//SetPos (110 , 40);
	//SetPos (110 , 41);
	//cout << tempY << " " << tempX << endl;
	//system ("pause");

}
void ChessGame::BishopMoveScan (ChessGame& map,int curY , int curX)
{
	int i , j;
	map.CurFieldX = curX;
	map.CurFieldY = curY;
	int tempX = curX , tempY = curY;


	//Left-Down check move
	i = map.CurFieldY;
	j = map.CurFieldX;
	while ( i <= 6 && j <= 6 )
	{
		++i; ++j;
		if ( map.GameField[i][j].color2 == 12 );
		else if ( map.GameField[curY][curX].White == 0 )
		{
			if ( map.GameField[i][j].color2 == 10 )
				map.GameField[i][j].color2 = 12;
			else
				map.GameField[i][j].color2 = 9;
		}
		else if ( map.GameField[curY][curX].White == 1 )
		{
			if ( map.GameField[i][j].color2 == 9 )
				map.GameField[i][j].color2 = 12;
			else
				map.GameField[i][j].color2 = 10;
		}
		if ( map.GameField[i][j].piece != " " )
		{
			break;
		}

	}

	//Right-Down check move
	i = map.CurFieldY;
	j = map.CurFieldX;
	while ( i <= 6 && j >= 1 )
	{
		++i; --j;
		if ( map.GameField[i][j].color2 == 12 );
		else if ( map.GameField[curY][curX].White == 0 )
		{
			if ( map.GameField[i][j].color2 == 10 )
				map.GameField[i][j].color2 = 12;
			else
				map.GameField[i][j].color2 = 9;
		}
		else if ( map.GameField[curY][curX].White == 1 )
		{
			if ( map.GameField[i][j].color2 == 9 )
				map.GameField[i][j].color2 = 12;
			else
				map.GameField[i][j].color2 = 10;
		}
		if ( map.GameField[i][j].piece != " " )
		{
			break;
		}
	}

	//Left-Up check move
	i = map.CurFieldY;
	j = map.CurFieldX;
	while ( i >= 1 && j >= 1 )
	{
		--i; --j;
		if ( map.GameField[i][j].color2 == 12 );
		else if ( map.GameField[curY][curX].White == 0 )
		{
			if ( map.GameField[i][j].color2 == 10 )
				map.GameField[i][j].color2 = 12;
			else
				map.GameField[i][j].color2 = 9;
		}
		else if ( map.GameField[curY][curX].White == 1 )
		{
			if ( map.GameField[i][j].color2 == 9 )
				map.GameField[i][j].color2 = 12;
			else
				map.GameField[i][j].color2 = 10;
		}
		if ( map.GameField[i][j].piece != " " )
		{
			break;
		}
	}

	//Right-Up check move
	i = map.CurFieldY;
	j = map.CurFieldX;
	while ( i >= 1 && j <= 6 )
	{
		--i; ++j;
		if ( map.GameField[i][j].color2 == 12 );
		else if ( map.GameField[curY][curX].White == 0 )
		{
			if ( map.GameField[i][j].color2 == 10 )
				map.GameField[i][j].color2 = 12;
			else
				map.GameField[i][j].color2 = 9;
		}
		else if ( map.GameField[curY][curX].White == 1 )
		{
			if ( map.GameField[i][j].color2 == 9 )
				map.GameField[i][j].color2 = 12;
			else
				map.GameField[i][j].color2 = 10;
		}
		if ( map.GameField[i][j].piece != " " )
		{
			break;
		}
	}

	/*map.DrawAllPieces ();
	SetPos (110 , 40);
	SetPos (110 , 41);
	cout << tempY << " " << tempX << endl;
	system ("pause");*/


}
void ChessGame::KnightMoveScan (ChessGame& map,int curY , int curX)
{
	map.CurFieldX = curX;
	map.CurFieldY = curY;
	int tempX = curX , tempY = curY;

	// up-up-left
	if ( curY - 2 >= 0 && curX - 1 >= 0 )
	{
		if ( map.GameField[curY - 2][curX - 1].color2 == 12 );
		else if ( map.GameField[curY][curX].White == 0 )
		{
			if ( map.GameField[curY - 2][curX - 1].color2 == 10 )
				map.GameField[curY - 2][curX - 1].color2 = 12;
			else
				map.GameField[curY - 2][curX - 1].color2 = 9;
		}
		else if ( map.GameField[curY][curX].White == 1)
		{
			if ( map.GameField[curY - 2][curX - 1].color2 == 9 )
				map.GameField[curY - 2][curX - 1].color2 = 12;
			else
				map.GameField[curY - 2][curX - 1].color2 = 10;
		}
	}

	// up-up-right
	if ( curY - 2 >= 0 && curX + 1 < 8 )
	{
		if ( map.GameField[curY - 2][curX + 1].color2 == 12 );
		else if ( map.GameField[curY][curX].White == 0 )
		{
			if ( map.GameField[curY - 2][curX + 1].color2 == 10 )
				map.GameField[curY - 2][curX + 1].color2 = 12;
			else
				map.GameField[curY - 2][curX + 1].color2 = 9;
		}
		else if ( map.GameField[curY][curX].White == 1 )
		{
			if ( map.GameField[curY - 2][curX + 1].color2 == 9 )
				map.GameField[curY - 2][curX + 1].color2 = 12;
			else
				map.GameField[curY - 2][curX + 1].color2 = 10;
		}
	}

	// up-left-left
	if ( curY - 1 >= 0 && curX - 2 >= 0 )
	{
		if ( map.GameField[curY - 1][curX - 2].color2 == 12 );
		else if ( map.GameField[curY][curX].White == 0 )
		{
			if ( map.GameField[curY - 1][curX - 2].color2 == 10 )
				map.GameField[curY - 1][curX - 2].color2 = 12;
			else
				map.GameField[curY - 1][curX - 2].color2 = 9;
		}
		else if ( map.GameField[curY][curX].White == 1 )
		{
			if ( map.GameField[curY - 1][curX - 2].color2 == 9 )
				map.GameField[curY - 1][curX - 2].color2 = 12;
			else
				map.GameField[curY - 1][curX - 2].color2 = 10;
		}
	}

	// down-left-left
	if ( curY + 1 < 8 && curX - 2 >= 0 )
	{
		if ( map.GameField[curY + 1][curX - 2].color2 == 12 );
		else if ( map.GameField[curY][curX].White == 0 )
		{
			if ( map.GameField[curY + 1][curX - 2].color2 == 10 )
				map.GameField[curY + 1][curX - 2].color2 = 12;
			else
				map.GameField[curY + 1][curX - 2].color2 = 9;
		}
		else if ( map.GameField[curY][curX].White == 1 )
		{
			if ( map.GameField[curY + 1][curX - 2].color2 == 9 )
				map.GameField[curY + 1][curX - 2].color2 = 12;
			else
				map.GameField[curY + 1][curX - 2].color2 = 10;
		}
	}

	// up-right-right
	if ( curY - 1 >= 0 && curX + 2 < 8 )
	{
		if ( map.GameField[curY - 1][curX + 2].color2 == 12 );
		else if ( map.GameField[curY][curX].White == 0 )
		{
			if ( map.GameField[curY - 1][curX + 2].color2 == 10 )
				map.GameField[curY - 1][curX + 2].color2 = 12;
			else
				map.GameField[curY - 1][curX + 2].color2 = 9;
		}
		else if ( map.GameField[curY][curX].White == 1 )
		{
			if ( map.GameField[curY - 1][curX + 2].color2 == 9 )
				map.GameField[curY - 1][curX + 2].color2 = 12;
			else
				map.GameField[curY - 1][curX + 2].color2 = 10;
		}
	}

	// down-right-right
	if ( curY + 1 < 8 && curX + 2 < 8 )
	{
		if ( map.GameField[curY + 1][curX + 2].color2 == 12 );
		else if ( map.GameField[curY][curX].White == 0 )
		{
			if ( map.GameField[curY + 1][curX + 2].color2 == 10 )
				map.GameField[curY + 1][curX + 2].color2 = 12;
			else
				map.GameField[curY + 1][curX + 2].color2 = 9;
		}
		else if ( map.GameField[curY][curX].White == 1 )
		{
			if ( map.GameField[curY + 1][curX + 2].color2 == 9 )
				map.GameField[curY + 1][curX + 2].color2 = 12;
			else
				map.GameField[curY + 1][curX + 2].color2 = 10;
		}
	}

	// down-down-right
	if ( curY + 2 < 8 && curX + 1 < 8 )
	{
		if ( map.GameField[curY + 2][curX + 1].color2 == 12 );
		else if ( map.GameField[curY][curX].White == 0 )
		{
			if ( map.GameField[curY + 2][curX + 1].color2 == 10 )
				map.GameField[curY + 2][curX + 1].color2 = 12;
			else
				map.GameField[curY + 2][curX + 1].color2 = 9;
		}
		else if ( map.GameField[curY][curX].White == 1 )
		{
			if ( map.GameField[curY + 2][curX + 1].color2 == 9 )
				map.GameField[curY + 2][curX + 1].color2 = 12;
			else
				map.GameField[curY + 2][curX + 1].color2 = 10;
		}
	}

	// down-down-left
	if ( curY + 2 < 8 && curX - 1 >= 0 )
	{
		if ( map.GameField[curY + 2][curX - 1].color2 == 12 );
		else if ( map.GameField[curY][curX].White == 0 )
		{
			if ( map.GameField[curY + 2][curX - 1].color2 == 10 )
				map.GameField[curY + 2][curX - 1].color2 = 12;
			else
				map.GameField[curY + 2][curX - 1].color2 = 9;
		}
		else if ( map.GameField[curY][curX].White == 1)
		{
			if ( map.GameField[curY + 2][curX - 1].color2 == 9 )
				map.GameField[curY + 2][curX - 1].color2 = 12;
			else
				map.GameField[curY + 2][curX - 1].color2 = 10;
		}
	}

	/*map.DrawAllPieces ();
	SetPos (110 , 40);
	SetPos (110 , 41);
	cout << tempY << " " << tempX << endl;
	system ("pause");*/
}
void ChessGame::RookMoveScan (ChessGame& map, int curY , int curX)
{
	map.CurFieldX = curX;
	map.CurFieldY = curY;
	int tempX = curX , tempY = curY;

	//Right
	for ( int i = curX + 1; i < 8; i++ )
	{
		if (  map.GameField[curY][i].color2 == 12 );
		else if ( map.GameField[curY][curX].White == 0 )
		{
			if (  map.GameField[curY][i].color2 == 10 )
				 map.GameField[curY][i].color2 = 12;
			else
				 map.GameField[curY][i].color2 = 9;
		}
		else if ( map.GameField[curY][curX].White == 1 )
		{
			if (  map.GameField[curY][i].color2 == 9 )
				 map.GameField[curY][i].color2 = 12;
			else
				 map.GameField[curY][i].color2 = 10;
		}
		if ( map.GameField[curY][i].piece != " " )
		{
			break;
		}
	}

	//Left
	for ( int i = curX - 1; i >= 0; i-- )
	{
		if ( map.GameField[curY][i].color2 == 12 );
		else if ( map.GameField[curY][curX].White == 0 )
		{
			if ( map.GameField[curY][i].color2 == 10 )
				map.GameField[curY][i].color2 = 12;
			else
				map.GameField[curY][i].color2 = 9;
		}
		else if ( map.GameField[curY][curX].White == 1 )
		{
			if ( map.GameField[curY][i].color2 == 9 )
				map.GameField[curY][i].color2 = 12;
			else
				map.GameField[curY][i].color2 = 10;
		}
		if ( map.GameField[curY][i].piece != " " )
		{
			break;
		}
	}

	//Up
	for ( int i = curY - 1; i >= 0; i-- )
	{
		if ( map.GameField[i][curX].color2 == 12 );
		else if ( map.GameField[curY][curX].White == 0 )
		{
			if ( map.GameField[i][curX].color2 == 10 )
				map.GameField[i][curX].color2 = 12;
			else
				map.GameField[i][curX].color2 = 9;
		}
		else if ( map.GameField[curY][curX].White == 1 )
		{
			if ( map.GameField[i][curX].color2 == 9 )
				map.GameField[i][curX].color2 = 12;
			else
				map.GameField[i][curX].color2 = 10;
		}
		if ( map.GameField[i][curX].piece != " " )
		{
			break;
		}
	}
	//Down
	for ( int i = curY + 1; i < 8; i++ )
	{
		if ( map.GameField[i][curX].color2 == 12 );
		else if ( map.GameField[curY][curX].White == 0 )
		{
			if ( map.GameField[i][curX].color2 == 10 )
				map.GameField[i][curX].color2 = 12;
			else
				map.GameField[i][curX].color2 = 9;
		}
		else if ( map.GameField[curY][curX].White == 1 )
		{
			if ( map.GameField[i][curX].color2 == 9 )
				map.GameField[i][curX].color2 = 12;
			else
				map.GameField[i][curX].color2 = 10;
		}
		if ( map.GameField[i][curX].piece != " " )
		{
			break;
		}
	}

	/*map.DrawAllPieces ();
	SetPos (110 , 40);
	SetPos (110 , 41);
	cout << tempY << " " << tempX << endl;
	system ("pause");*/
	
}
void ChessGame::QueenMoveScan (ChessGame& map , int curY , int curX)
{
	int i , j;
	map.CurFieldX = curX;
	map.CurFieldY = curY;
	int tempX = curX , tempY = curY;

	//Right
	for ( int i = curX + 1; i < 8; i++ )
	{
		if ( map.GameField[curY][i].color2 == 12 );
		else if ( map.GameField[curY][curX].White == 0 )
		{
			if ( map.GameField[curY][i].color2 == 10 )
				map.GameField[curY][i].color2 = 12;
			else
				map.GameField[curY][i].color2 = 9;
		}
		else if ( map.GameField[curY][curX].White == 1 )
		{
			if ( map.GameField[curY][i].color2 == 9 )
				map.GameField[curY][i].color2 = 12;
			else
				map.GameField[curY][i].color2 = 10;
		}
		if ( map.GameField[curY][i].piece != " " )
		{
			break;
		}
	}

	//Left
	for ( int i = curX - 1; i >= 0; i-- )
	{
		if ( map.GameField[curY][i].color2 == 12 );
		else if ( map.GameField[curY][curX].White == 0 )
		{
			if ( map.GameField[curY][i].color2 == 10 )
				map.GameField[curY][i].color2 = 12;
			else
				map.GameField[curY][i].color2 = 9;
		}
		else if ( map.GameField[curY][curX].White == 1 )
		{
			if ( map.GameField[curY][i].color2 == 9 )
				map.GameField[curY][i].color2 = 12;
			else
				map.GameField[curY][i].color2 = 10;
		}
		if ( map.GameField[curY][i].piece != " " )
		{
			break;
		}
	}

	//Up
	for ( int i = curY - 1; i >= 0; i-- )
	{
		if ( map.GameField[i][curX].color2 == 12 );
		else if ( map.GameField[curY][curX].White == 0 )
		{
			if ( map.GameField[i][curX].color2 == 10 )
				map.GameField[i][curX].color2 = 12;
			else
				map.GameField[i][curX].color2 = 9;
		}
		else if ( map.GameField[curY][curX].White == 1 )
		{
			if ( map.GameField[i][curX].color2 == 9 )
				map.GameField[i][curX].color2 = 12;
			else
				map.GameField[i][curX].color2 = 10;
		}
		if ( map.GameField[i][curX].piece != " " )
		{
			break;
		}
	}
	//Down
	for ( int i = curY + 1; i < 8; i++ )
	{
		if ( map.GameField[i][curX].color2 == 12 );
		else if ( map.GameField[curY][curX].White == 0 )
		{
			if ( map.GameField[i][curX].color2 == 10 )
				map.GameField[i][curX].color2 = 12;
			else
				map.GameField[i][curX].color2 = 9;
		}
		else if ( map.GameField[curY][curX].White == 1 )
		{
			if ( map.GameField[i][curX].color2 == 9 )
				map.GameField[i][curX].color2 = 12;
			else
				map.GameField[i][curX].color2 = 10;
		}
		if ( map.GameField[i][curX].piece != " " )
		{
			break;
		}
	}
	//Left-Down check move
	i = map.CurFieldY;
	j = map.CurFieldX;
	while ( i <= 6 && j <= 6 )
	{
		++i; ++j;
		if ( map.GameField[i][j].color2 == 12 );
		else if ( map.GameField[curY][curX].White == 0 )
		{
			if ( map.GameField[i][j].color2 == 10 )
				map.GameField[i][j].color2 = 12;
			else
				map.GameField[i][j].color2 = 9;
		}
		else if ( map.GameField[curY][curX].White == 1 )
		{
			if ( map.GameField[i][j].color2 == 9 )
				map.GameField[i][j].color2 = 12;
			else
				map.GameField[i][j].color2 = 10;
		}
		if ( map.GameField[i][j].piece != " " )
		{
			break;
		}

	}

	//Right-Down check move
	i = map.CurFieldY;
	j = map.CurFieldX;
	while ( i <= 6 && j >= 1 )
	{
		++i; --j;
		if ( map.GameField[i][j].color2 == 12 );
		else if ( map.GameField[curY][curX].White == 0 )
		{
			if ( map.GameField[i][j].color2 == 10 )
				map.GameField[i][j].color2 = 12;
			else
				map.GameField[i][j].color2 = 9;
		}
		else if ( map.GameField[curY][curX].White == 1 )
		{
			if ( map.GameField[i][j].color2 == 9 )
				map.GameField[i][j].color2 = 12;
			else
				map.GameField[i][j].color2 = 10;
		}
		if ( map.GameField[i][j].piece != " " )
		{
			break;
		}
	}

	//Left-Up check move
	i = map.CurFieldY;
	j = map.CurFieldX;
	while ( i >= 1 && j >= 1 )
	{
		--i; --j;
		if ( map.GameField[i][j].color2 == 12 );
		else if ( map.GameField[curY][curX].White == 0 )
		{
			if ( map.GameField[i][j].color2 == 10 )
				map.GameField[i][j].color2 = 12;
			else
				map.GameField[i][j].color2 = 9;
		}
		else if ( map.GameField[curY][curX].White == 1 )
		{
			if ( map.GameField[i][j].color2 == 9 )
				map.GameField[i][j].color2 = 12;
			else
				map.GameField[i][j].color2 = 10;
		}
		if ( map.GameField[i][j].piece != " " )
		{
			break;
		}
	}

	//Right-Up check move
	i = map.CurFieldY;
	j = map.CurFieldX;
	while ( i >= 1 && j <= 6 )
	{
		--i; ++j;
		if ( map.GameField[i][j].color2 == 12 );
		else if ( map.GameField[curY][curX].White == 0 )
		{
			if ( map.GameField[i][j].color2 == 10 )
				map.GameField[i][j].color2 = 12;
			else
				map.GameField[i][j].color2 = 9;
		}
		else if ( map.GameField[curY][curX].White == 1 )
		{
			if ( map.GameField[i][j].color2 == 9 )
				map.GameField[i][j].color2 = 12;
			else
				map.GameField[i][j].color2 = 10;
		}
		if ( map.GameField[i][j].piece != " " )
		{
			break;
		}
	}

	//map.DrawAllPieces ();
	//SetPos (110 , 40);
	//SetPos (110 , 41);
	//cout << tempY << " " << tempX << endl;
	//system ("pause");

}
void ChessGame::KingMoveScan (ChessGame& map , int curY , int curX)
{
	int i , j;
	map.CurFieldX = curX;
	map.CurFieldY = curY;
	int tempX = curX , tempY = curY;


	//Check for attack in Top-left
	if ( curY - 1 >= 0 && curX - 1 >= 0 )
	if ( map.GameField[curY - 1][curX - 1].color2 == 12 );
	else if ( map.GameField[curY][curX].White == 0 )
	{
		if ( map.GameField[curY - 1][curX - 1].color2 == 10 )
			map.GameField[curY - 1][curX - 1].color2 = 12;
		else
			map.GameField[curY - 1][curX - 1].color2 = 9;
	}
	else if ( map.GameField[curY][curX].White == 1 )
	{
		if ( map.GameField[curY - 1][curX - 1].color2 == 9 )
			map.GameField[curY - 1][curX - 1].color2 = 12;
		else
			map.GameField[curY - 1][curX - 1].color2 = 10;
	}


	//Check for attack in Top-right
	if ( curY - 1 >= 0 && curX + 1 < 8 )
	if ( map.GameField[curY - 1][curX + 1].color2 == 12 );
	else if ( map.GameField[curY][curX].White == 0 )
	{
		if ( map.GameField[curY - 1][curX + 1].color2 == 10 )
			map.GameField[curY - 1][curX + 1].color2 = 12;
		else
			map.GameField[curY - 1][curX + 1].color2 = 9;
	}
	else if ( map.GameField[curY][curX].White == 1 )
	{
		if ( map.GameField[curY - 1][curX + 1].color2 == 9 )
			map.GameField[curY - 1][curX + 1].color2 = 12;
		else
			map.GameField[curY - 1][curX + 1].color2 = 10;
	}

	//Check for attack in Top-left
	if ( curX - 1 >= 0 )
	if ( map.GameField[curY][curX - 1].color2 == 12 );
	else if ( map.GameField[curY][curX].White == 0 )
	{
		if ( map.GameField[curY][curX - 1].color2 == 10 )
			map.GameField[curY][curX - 1].color2 = 12;
		else
			map.GameField[curY][curX - 1].color2 = 9;
	}
	else if ( map.GameField[curY][curX].White == 1 )
	{
		if ( map.GameField[curY][curX - 1].color2 == 9 )
			map.GameField[curY][curX - 1].color2 = 12;
		else
			map.GameField[curY][curX - 1].color2 = 10;
	}


	//Check for attack in Top-left
	if ( curX + 1 < 8 )
	if ( map.GameField[curY][curX + 1].color2 == 12 );
	else if ( map.GameField[curY][curX].White == 0 )
	{
		if ( map.GameField[curY][curX + 1].color2 == 10 )
			map.GameField[curY][curX + 1].color2 = 12;
		else
			map.GameField[curY][curX + 1].color2 = 9;
	}
	else if ( map.GameField[curY][curX].White == 1 )
	{
		if ( map.GameField[curY][curX + 1].color2 == 9 )
			map.GameField[curY][curX + 1].color2 = 12;
		else
			map.GameField[curY][curX + 1].color2 = 10;
	}

	//Check for attack in Top-left
	if ( curY + 1 < 8 && curX - 1 >= 0 )
	if ( map.GameField[curY + 1][curX - 1].color2 == 12 );
	else if ( map.GameField[curY][curX].White == 0 )
	{
		if ( map.GameField[curY + 1][curX - 1].color2 == 10 )
			map.GameField[curY + 1][curX - 1].color2 = 12;
		else
			map.GameField[curY + 1][curX - 1].color2 = 9;
	}
	else if ( map.GameField[curY][curX].White == 1 )
	{
		if ( map.GameField[curY + 1][curX - 1].color2 == 9 )
			map.GameField[curY + 1][curX - 1].color2 = 12;
		else
			map.GameField[curY + 1][curX - 1].color2 = 10;
	}

	//Check for attack in Top-left
	if ( curY + 1 < 8 && curX + 1 < 8 )
	if ( map.GameField[curY + 1][curX + 1].color2 == 12 );
	else if ( map.GameField[curY][curX].White == 0 )
	{
		if ( map.GameField[curY + 1][curX + 1].color2 == 10 )
			map.GameField[curY + 1][curX + 1].color2 = 12;
		else
			map.GameField[curY + 1][curX + 1].color2 = 9;
	}
	else if ( map.GameField[curY][curX].White == 1 )
	{
		if ( map.GameField[curY + 1][curX + 1].color2 == 9 )
			map.GameField[curY + 1][curX + 1].color2 = 12;
		else
			map.GameField[curY + 1][curX + 1].color2 = 10;
	}

	//Check for attack in Top-left
	if ( curY - 1 >= 0 )
	if ( map.GameField[curY - 1][curX].color2 == 12 );
	else if ( map.GameField[curY][curX].White == 0 )
	{
		if ( map.GameField[curY - 1][curX].color2 == 10 )
			map.GameField[curY - 1][curX].color2 = 12;
		else
			map.GameField[curY - 1][curX].color2 = 9;
	}
	else if ( map.GameField[curY][curX].White == 1 )
	{
		if ( map.GameField[curY - 1][curX].color2 == 9 )
			map.GameField[curY - 1][curX].color2 = 12;
		else
			map.GameField[curY - 1][curX].color2 = 10;
	}

	//Check for attack in Top-left
	if ( curY + 1 < 8 )
	if ( map.GameField[curY + 1][curX].color2 == 12 );
	else if ( map.GameField[curY][curX].White == 0 )
	{
		if ( map.GameField[curY + 1][curX].color2 == 10 )
			map.GameField[curY + 1][curX].color2 = 12;
		else
			map.GameField[curY + 1][curX].color2 = 9;
	}
	else if ( map.GameField[curY][curX].White == 1 )
	{
		if ( map.GameField[curY + 1][curX].color2 == 9 )
			map.GameField[curY + 1][curX].color2 = 12;
		else
			map.GameField[curY + 1][curX].color2 = 10;
	}

	/*map.DrawAllPieces ();
	SetPos (110 , 40);
	SetPos (110 , 41);
	cout << tempY << " " << tempX << endl;
	system ("pause");*/
}

// White = 10 GREEN
// Black = 9 BLUE
// Black+White = 12 RED
void ChessGame::Reverse ( )
{
	for ( int i = 0; i < 4;i++ )
	for ( int j = 0; j < 8; j++ )
	{
		swap (GameField[i][j].color1 , GameField[7 - i][7 - j].color1);
		swap (GameField[i][j].color2 , GameField[7 - i][7 - j].color2);
		swap (GameField[i][j].White , GameField[7 - i][7 - j].White);
		swap (GameField[i][j].piece , GameField[7 - i][7 - j].piece);
	}
	for ( int i = 0; i < 8;i++ )
	for ( int j = 0; j < 8; j++ )
	{
		if ( GameField[i][j].White )
			GameField[i][j].color1 = 15;
		else
			GameField[i][j].color1 = 4;

	}
}
void ChessGame::ScanMap ( )
{
	ChessGame Temp;
	for ( int i = 0; i < 8; i++ )
	for ( int j = 0; j < 8; j++ ){
		Temp.GameField[i][j] = GameField[i][j];
		AttackMap[i][j] = 0;
	}
	int Send_I;
	int Send_J;

	if ( WhiteStep == 0 )
		Temp.Reverse ( );


	bool tempWhiteStep = WhiteStep;
	for ( int i = 0; i < 8; i++ )
	{
		for ( int j = 0; j < 8; j++ )
		{
			Send_I = i;
			Send_J = j;

			//if ( Temp.GameField[i][j].White == 0 )
			//{
			//	//Reverse For Black/White
			//	Temp.Reverse ();
			//	WhiteStep = !WhiteStep;
			//	for ( int k = 0; k < 4; k++ )
			//	for ( int f = 0; f < 8; f++ )
			//	{
			//		swap (AttackMap[k][f] , AttackMap[7 - k][7 - f]);
			//	}
			//	Send_I = 7 - i;
			//	Send_J = 7 - j;
			//}

			if ( Temp.GameField[i][j].piece == "Pawn" )
				PawnMoveScan (Temp , Send_I , Send_J);
			if ( Temp.GameField[i][j].piece == "Bishop" )
				BishopMoveScan (Temp , Send_I , Send_J);
			if ( Temp.GameField[i][j].piece == "Knight" )
				KnightMoveScan (Temp , Send_I , Send_J);
			if ( Temp.GameField[i][j].piece == "Rook" )
				RookMoveScan (Temp , Send_I , Send_J);
			if ( Temp.GameField[i][j].piece == "Queen" )
				QueenMoveScan (Temp , Send_I , Send_J);
			if ( Temp.GameField[i][j].piece == "King" )
				KingMoveScan (Temp , Send_I , Send_J);

		/*	if ( Send_I != i ){
				Temp.Reverse ( );
			}*/
		}
	}

	WhiteStep = tempWhiteStep;

	// White = 10 GREEN
	// Black = 9 BLUE
	// Black+White = 12 RED
	for ( int i = 0; i < 8; i++ )
	for ( int j = 0; j < 8; j++ )
	{
		if ( Temp.GameField[i][j].color2 == 9 )
			AttackMap[i][j] = 2;
		if ( Temp.GameField[i][j].color2 == 10 )
			AttackMap[i][j] = 1;
		if ( Temp.GameField[i][j].color2 == 12 )
			AttackMap[i][j] = 3;
	}
	bool FindCheck = 0;
	for ( int i = 0; i < 8; i++ )
	{
		for ( int j = 0; j < 8; j++ )
		{
			if ( Temp.GameField[i][j].piece == "King" )
			{
				if ( AttackMap[i][j] == 1 && Temp.GameField[i][j].White == 0 || AttackMap[i][j] == 2 && Temp.GameField[i][j].White == 1 || AttackMap[i][j] == 3)
				{
					SetPos (150+i , 40);
					cout << "CHECK!" << endl;
					FindCheck = true;
				}
			}
		}
	}


	if ( FindCheck )
		Check = true;
	else
		Check = false;

	if (WhiteStep )
	for ( int k = 0; k < 4; k++ )
	for ( int f = 0; f < 8; f++ )
	{
		swap (AttackMap[k][f] , AttackMap[7 - k][7 - f]);
	}

	for ( int i = 0; i < 8; i++ )
	{
		for ( int j = 0; j < 8; j++ )
		{
			SetPos (100+j , 20+i);
			cout << AttackMap[i][j] << " ";
		}
		cout << endl;
	}

}


void ChessGame::FakeSwap (ChessGame& map , int curY1 , int curX1 , int curY2 , int curX2)
{
		map.GameField[curY1][curX1].piece = map.GameField[curY2][curX2].piece;
		map.GameField[curY1][curX1].White = map.GameField[curY2][curX2].White;
		map.GameField[curY1][curX1].color1 = map.GameField[curY2][curX2].color1;
		map.GameField[curY2][curX2].piece = " ";
		map.GameField[curY2][curX2].White = 2;
		map.GameField[curY1][curX1].White = WhiteStep;
}
void ChessGame::FakeWalk (string _piece , int curY , int curX)
{
	if ( _piece == "Pawn" )
		FakePawnMove (curY , curX);
}
void ChessGame::FakePawnMove (int curY , int curX)
{
	ChessGame Temp;
	Temp.WhiteStep = WhiteStep;
	Temp.CurFieldX = curX;
	Temp.CurFieldY = curY;
	int tempX = curX , tempY = curY;

	for ( int i = 0; i < 8; i++ )
	for ( int j = 0; j < 8; j++ )
		Temp.GameField[i][j] = GameField[i][j];
	Temp.ScanMap();
	SetPos(85, 13);
	cout << "TEMPSCANMAP: " << Temp.Check;
	system("pause");
	//Check for free moves
	if ( GameField[curY - 1][curX].piece == " " )
	{
		if ( curY == 6 && GameField[curY - 2][curX].piece == " " )
		{
			Temp.FakeSwap (Temp , curY - 2 , curX , curY , curX);
			Temp.ScanMap ( );
			if (!Temp.Check) CanAvoid = 1;
			Temp.DrawAllPieces();
			SetPos(85, 10);
			cout << "Check: " << Check;
			SetPos(85, 11);
			cout << "Avoid: " << CanAvoid;
			system("pause");
			for ( int i = 0; i < 8; i++ )
			for ( int j = 0; j < 8; j++ )
				Temp.GameField[i][j] = GameField[i][j];
		}
		Temp.GameField[curY - 1][curX].color2 = 2;
		Temp.FakeSwap (Temp , curY - 1 , curX , curY , curX);
		Temp.ScanMap ();
		if (!Temp.Check) CanAvoid = 1;
		SetPos(85, 10);
		cout << "Check: " << Check;
		SetPos(85, 11);
		cout << "Avoid: " << CanAvoid;

		Temp.DrawAllPieces();
		system("pause");
		for ( int i = 0; i < 8; i++ )
		for ( int j = 0; j < 8; j++ )
			Temp.GameField[i][j] = GameField[i][j];

	}
	//Check for attack in left
	if(curY-1>=0 && curX - 1 >=0)

		if (Temp.GameField[curY - 1][curX - 1].piece != " " && Temp.GameField[curY - 1][curX - 1].White != Temp.GameField[curY][curX].White) {
			Temp.FakeSwap(Temp, curY - 1, curX - 1, curY, curX);
			Temp.ScanMap();
			if (!Temp.Check) CanAvoid = 1;
			Temp.DrawAllPieces();
			system("pause");
			for (int i = 0; i < 8; i++)
				for (int j = 0; j < 8; j++)
					Temp.GameField[i][j] = GameField[i][j];
		}
	//Check for attack in right
	if (curY - 1 >= 0 && curX + 1 < 8)
	if (Temp.GameField[curY - 1][curX + 1].piece != " " && Temp.GameField[curY - 1][curX + 1].White != Temp.GameField[curY][curX].White ){
		Temp.FakeSwap (Temp , curY - 1 , curX + 1 , curY , curX);
		Temp.ScanMap ();
		if (!Temp.Check) CanAvoid = 1;
		Temp.DrawAllPieces();
		system("pause");
		for ( int i = 0; i < 8; i++ )
		for ( int j = 0; j < 8; j++ )
			Temp.GameField[i][j] = GameField[i][j];
	}
}


ChessGame::~ChessGame ( )
{
}
