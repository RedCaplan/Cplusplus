#pragma once
#include "ChessFiguresG.h"

class ChessGame :
	public ChessFiguresG
{
private:

	bool Check;
	bool CanAvoid=0;

	bool WhiteStep = 1;

	int CurFieldX = 0;
	int CurFieldY = 0;

	short AttackMap[8][8];
public:
	ChessGame ( );
	void DrawAllPieces ( );

	void Walk ( );
	void Move ( );
	bool PawnMove ();
	bool BishopMove ();
	bool KnightMove ();
	bool RookMove ( );
	bool QueenMove ( );
	bool KingMove ( );

	void PawnMoveScan (ChessGame& map,int curY, int curX);
	void BishopMoveScan (ChessGame& map,int curY , int curX);
	void KnightMoveScan (ChessGame& map,int curY , int curX);
	void RookMoveScan (ChessGame& map , int curY , int curX);
	void QueenMoveScan (ChessGame& map , int curY , int curX);
	void KingMoveScan (ChessGame& map , int curY , int curX);

	void FakeWalk (string _piece,int curY,int curX );
	void FakePawnMove (int curY , int curX);
	void FakeSwap (ChessGame& map , int curY1 , int curX1 , int curY2 , int curX2);
	void ScanMap ( );
	void Reverse ( );
	~ChessGame ( );
};

