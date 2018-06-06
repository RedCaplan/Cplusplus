#include "World.h"
#include "utils.h"
#include "base.h"
#include <string>
/***************************** Public functions */
World::World ()
{
	_isActive = false;
	_myBall = new Ball;
	for ( int x = 0; x <= POS_X_MAX + 2; x++ )
		str.push_back (' ');
}

World::~World ()
{
	delete _myBall;
	_myEnemy.clear ();
	_myHero.clear ();
}

void World::Run (const char input)
{

	for ( int i = 0; i < BALL_SPEED; i++ )
		RunBall ();
	Color (10);
	GoToXY (160 , 30);
	printf ("%c" , input);
	Color (7);
	RunHero (input);
	RunEnemy ();
	Collitions ();
	Print ();
	Sleep (SLEEP_VALUE_IN_MS);
}

bool World::IsActive ()
{
	return _isActive;
}

void World::SwitchActivation ()
{
	_isActive = !_isActive;
}

void World::InitializeWorld ()
{
	for ( int i = 0; i < HERO_SIZE; i++ )
	{
		_myHero.push_back (new Hero);
		_myHero[i]->_positionY -= i;
	}
	for ( int i = 0; i < ENEMY_SIZE; i++ )
	{
		_myEnemy.push_back (new Enemy);
		_myEnemy[i]->_positionY -= i;
	}
}

/*********************** Public Print functions */
void World::PrintWelcomeScreen ()
{
	WelcomeScreenFrame1 ();
}



/********************************* Run functions */
void World::RunHero (const char input)
{
	
	if ( input != CHAR_NOT_VALID )
	{
		if ( input == 'w' && _myHero[HERO_SIZE-1]->_positionY!=POS_Y_MIN ||
			input == 's' && _myHero[0]->_positionY != POS_Y_MAX )
		for ( int i = 0; i < HERO_SIZE; i++ )
		{
			_myHero[i]->Run (input);
		}
	}
		
}

void World::RunEnemy ( )
{
	
		
	if ( RandomDecision (ENEMY_INTELLIGENCE) ){
		if ( _myBall->_MoveUp ){
			if ( _myEnemy[0]->_positionY != POS_Y_MIN + ENEMY_SIZE - 1 )
			for ( int i = 0; i < ENEMY_SIZE; i++ )
				_myEnemy[i]->Run ("UP");
		}
		else {
			if ( _myEnemy[ENEMY_SIZE - 1]->_positionY != POS_Y_MAX - ENEMY_SIZE + 1 )
			for ( int i = 0; i < ENEMY_SIZE; i++ )
				_myEnemy[i]->Run ("DOWN");
		}
	}
	else
	{
		if ( _myBall->_positionY > _myEnemy[ENEMY_SIZE / 2]->_positionY ){
			if ( _myEnemy[0]->_positionY != POS_Y_MIN + ENEMY_SIZE - 1 )
			for ( int i = 0; i < ENEMY_SIZE; i++ )
				_myEnemy[i]->Run ("UP");
		}

		else {
			if ( _myEnemy[ENEMY_SIZE - 1]->_positionY != POS_Y_MAX - ENEMY_SIZE + 1 )
			for ( int i = 0; i < ENEMY_SIZE; i++ )
				_myEnemy[i]->Run ("DOWN");
		}
	}

}

void World::RunBall ( )
{
	_myBall->Run ( );
}

/******************************* Print functions */
void World::Print ()
{
	PrintBlack ();

	for ( int i = 0; i < QUANTITY_OF_REDRAWING_ENTITIES; i++ ){
		PrintHero ();
		PrintEnemy ();
		PrintBall ( );
		PrintHero ();
	}
}

void World::PrintBorder ()
{
	GoToXY (0 , 0);
	Color (10);
	for ( int x = 0; x <= BORDER_SIZE_X; x++ )
		printf ("%c" , 178);
	GoToXY (0 , BORDER_SIZE_Y);
	for ( int x = 0; x <= BORDER_SIZE_X; x++ )
		printf ("%c" , 178);

	Color (7);

}


void World::PrintEnemy ()
{
	Color (_myEnemy[0]->_color1);
	for ( int i = 0; i < ENEMY_SIZE; i++ )
	{
		GoToXY (_myEnemy[i]->_positionX , _myEnemy[i]->_positionY);
		printf ("%c" , _myEnemy[i]->_model);
	}

	Color (0);
}

void World::PrintHero ()
{
	Color (_myHero[0]->_color1);
	for ( int i = 0; i < HERO_SIZE; i++ )
	{
		GoToXY (_myHero[i]->_positionX , _myHero[i]->_positionY);
		printf ("%c",_myHero[i]->_model);
	}
	
	Color (0);
}

void World::PrintBall ( )
{
	Color (_myBall->_color1);
	GoToXY (_myBall->_positionX , _myBall->_positionY);
	printf ("%c" , _myBall->_model);
}

void World::PrintBlack ()
{

	GoToXY (POS_X_MIN , POS_Y_MIN);
	for ( int y = POS_Y_MIN; y <= POS_Y_MAX; y++ )
	{
		printf ("%s\n" , str.c_str ());
	}
}

void World::PrintScore ()
{
	GoToXY (( POS_X_MIN + POS_X_MAX ) / 2 , POS_Y_MAX + 4);
	printf ("%d | %d" , LeftScore , RightScore);
}

/*************************** Collition functions */
void World::Collitions ()
{
	bool flag = true;
	if ( _myBall->_positionX == POS_X_MIN )
	{
		flag = true;
		for ( int i = 0; i < HERO_SIZE;i++ )
		if ( _myHero[i]->_positionY == _myBall->_positionY )
			flag = false;
		if ( flag )
		{
			SwitchActivation ( );
			RightScore++;
		}
		else
			_myBall->_MoveLeft = !_myBall->_MoveLeft;
	}
	if ( _myBall->_positionX == POS_X_MAX )
	{
		flag = true;
		for ( int i = 0; i < ENEMY_SIZE; i++ )
		if ( _myEnemy[i]->_positionY == _myBall->_positionY )
			flag = false;
		if ( flag )
		{
			SwitchActivation ();
			LeftScore++;
		}
		else
			_myBall->_MoveLeft = !_myBall->_MoveLeft;
	}
}
