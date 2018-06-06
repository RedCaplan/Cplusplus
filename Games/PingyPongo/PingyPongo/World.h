#pragma once
#include "Hero.h"
#include "Enemy.h"
#include "Ball.h"	
#include <vector>
#include <string>

class World
{
public:
	/***************************** Public functions */
	World ();
	~World ();
	void Run (const char input);
	bool IsActive ();
	void SwitchActivation ();
	void InitializeWorld ();

	/*********************** Public Print functions */
	void PrintWelcomeScreen ();	
	void PrintBorder ();
	void PrintScore ();
private:
	/************************************ Atributes */
	std::vector<Hero*> _myHero;
	std::vector<Enemy*> _myEnemy;
	Ball* _myBall;
	bool _isActive;

	/********************************* Run functions */
	void RunHero (const char input);
	void RunEnemy ();
	void RunBall ( );

	/******************************* Print functions */
	void Print ( );
	void PrintEnemy ();
	void PrintHero ();
	void PrintBall ( );
	void PrintBlack ();
	/*************************** Collition functions */
	void Collitions ();

	/***************************** SpaceBuffer */
	std::string str;
};

