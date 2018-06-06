#pragma once

#include "Hero.h"
#include "Enemy.h"
#include "Bullet.h"
#include "Star.h"
#include "Ammo.h"
#include "ScorePoint.h"
#include <vector>	



class World
{
public:
	unsigned int INITIAL_DIFFICULTY = 1;		//Default: 1

	/***************************** Public functions */
	World ();
	~World ();
	void Run (const char input);
	bool IsActive ();
	void SwitchActivation ();
	void InitializeWorld ();

	/*********************** Public Print functions */
	void PrintWelcomeScreen ();
	void PrintGameOverScreen ();
	void PrintGameOverAnimation ();
	void PrintBorder ();
	void PrintHelp ();

private:
	/************************************ Atributes */
	Hero* _myHero;
	std::vector<Enemy*> _myEnemies;
	std::vector<Bullet*> _myBullets;
	std::vector<Star*> _myStars;
	std::vector<Ammo*> _myAmmo;
	std::vector<ScorePoint*> _myScorePoint;
	int _difficulty;
	int _enemiesLeft;
	int _bulletsLeft;
	int _starsLeft;
	int _score;
	int _difficultyCounter;
	bool _isActive;

	/**************************** Generate functions */
	void GenerateEnemies ();
	void GenerateAmmo ();
	void GenerateScorePoint ();
	void GenerateStars ();
	void GenerateBullets (const char input);

	/********************************* Run functions */
	void RunHero (const char input);
	void RunEnemies ();
	void RunAmmo ();
	void RunScorePoint ();
	void RunBullets ();
	void RunStars ();
	void UpdateScoreAndDifficulty ();

	/******************************* Print functions */
	void Print ();
	
	void PrintStars ();
	void PrintAmmo ( );
	void PrintScorePoint ();
	void PrintBullets ();
	void PrintEnemies ();
	void PrintHero ();
	void PrintGameInfo ();
	void PrintBlack ();

	/*************************** Collition functions */
	void Collitions ();
	void HeroCollitions ();

	/***************************** SpaceBuffer */
	std::string str;
};

