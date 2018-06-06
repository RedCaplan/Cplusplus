#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "Field.h"
#include "Player.h"
#include <ctime>
class Map
{
	struct MapOption{ short l , w; }MapSize;
	Field** arr;
	Player Hero{ 2 , 2 };
	int scores;
	char* name;
	char* Username;
	double time;
public:
	Map ( ) :Map (50 , 60){};
	Map (int l , int w);
	void DrawMap ( );
	void SetColor (int text , int background);
	void InitializeMap ( );
	void InitializeBorders ();
	void DrawMenuButtons ( );
	void DrawMenuLogo ( );
	void DrawLastPlayersMap ();
	void FillMapColor ( );
	void ShowCreatorHelp (bool hero , int wall , int coin , int exit);
	void DrawHero ( ){
		COORD HeroCord = Hero.GetCord ( );
		int i = HeroCord.X;
		int j = HeroCord.Y;
		Hero.DrawPlayer ();
	};
	void SetHeroColor1 (int color){ Hero.SetColor1 (color); }
	void SetHeroPos (int x , int y){Hero.SetCord (x , y);}
	void SetHeroSign (char _sign){ Hero.SetSign (_sign); }
	int GetHeroPosX ( ){ COORD x = Hero.GetCord ( ); return x.X; }
	int GetHeroPosY (){ COORD x = Hero.GetCord (); return x.Y; }
	bool CanChange (int i , int j){return arr[i][j].CanChange ( ); }
	void setCanChange (int i , int j , bool arg){ arr[i][j].setCanChange (arg); }
	int GetHeroColor1 ( ){ return Hero.GetColor1 ( ); }
	void SetFieldSign (int i , int j , char sign){ arr[i][j].SetSign (sign); }
	char GetHeroSign ( ){ return Hero.GetHeroSign ( ); }
	void SetFieldPos (int i , int j){ arr[i][j].SetPos (i , j); }
	void DrawField (int i , int j){ arr[i][j].DrawField ( ); }
	void SetFieldColor (int i , int j , int color1 , int color2){ arr[i][j].SetColorsField (color1 , color2); }
	void SetHeroColor2 (int color){ Hero.SetColor2 (color); }
	int GetFieldColor1 (int i,int j ){ return arr[i][j].GetColor1(); }
	int GetMapL ( ){ return MapSize.l; }
	int GetMapW (){ return MapSize.w; }
	char GetFieldSign (int i , int j){ return arr[i][j].GetSign ( ); }
	int GetFieldPosX (int i , int j){ return arr[i][j].GetPosX ( ); }
	int GetFieldPosY (int i , int j){ return arr[i][j].GetPosY (); }
	int GetScores ( ){ return scores; }
	void SetScores (int i){ scores = i; }
	void DrawPlay (int _score,int steps );
	void DrawPlayEnd (int _score , int steps);
	void SetName (char* _name){ name = _name;}
	char* GetName ( ){ return name; }
	void SetTime (double _time){ time = _time; }
	double GetTime ( ){ return time; }
	void SetUserName (char* _name){ Username = _name; }
	~Map ( );
};

