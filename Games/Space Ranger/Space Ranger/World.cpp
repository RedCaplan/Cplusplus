#include "World.h"
#include "utils.h"
#include "base.h"
#include <string>


/***************************** Public functions */
World::World ()
{
	_isActive = false;
	_myHero = new Hero;
	_bulletsLeft = NUMBER_OF_BULLETS;
	_enemiesLeft = NEW_ENEMY_NUMBER;
	_starsLeft = NUMBER_OF_STARS;
	_difficulty = INITIAL_DIFFICULTY;
	_difficultyCounter = 0;
	_score = 0;

	for ( int x = 0; x <= POS_X_MAX+2; x++ )
		str.push_back (' ');
}

World::~World ()
{
	delete _myHero;
	_myEnemies.clear ();
	_myBullets.clear ();
	_myStars.clear ();
}

void World::Run (const char input)
{
	for ( int i = 0; i < STAR_SPEED; i++ )
		RunStars ( );
	GenerateEnemies ();
	GenerateBullets (input);
	GenerateAmmo ( );
	GenerateScorePoint ();
	RunHero (input);
	RunAmmo ( );
	RunScorePoint ();
	HeroCollitions ();
	RunBullets ();
	Collitions ();
	RunEnemies ();
	Collitions ();
	HeroCollitions ();
	Print ();
	UpdateScoreAndDifficulty ();

	Sleep (SLEEP_VALUE_IN_MS / INITIAL_DIFFICULTY);
}

bool World::IsActive ()
{
	return _isActive;
}

void World::SwitchActivation ()
{
	_isActive = !_isActive;
	if ( _isActive == false )
		_bulletsLeft = 0;
}

void World::InitializeWorld ()
{
	GenerateStars ();
}

/*********************** Public Print functions */
void World::PrintWelcomeScreen ()
{
	WelcomeScreenFrame1 ();
}

void World::PrintGameOverScreen ()
{
	PrintGameInfo ();
	GoToXY (26 , 11);
	printf ("GAME OVER: PLAY AGAIN? (Y/N)");
}

void World::PrintGameOverAnimation ()
{
	bool aux = true;
	if ( ( _myHero->_positionX > POS_X_MIN ) && /*If Hero position = game borders*/
		( _myHero->_positionX < POS_X_MAX ) && /*do not print the animation*/
		( _myHero->_positionY > POS_Y_MIN ) &&
		( _myHero->_positionY < POS_Y_MAX ) )
	{
		for ( int i = 0; i < GAME_OVER_FRAME_X; i++ )
		{
			if ( aux )
				GameOverFrame1 (_myHero->_positionX , _myHero->_positionY);
			else
				GameOverFrame2 (_myHero->_positionX , _myHero->_positionY);
			PlaySound (TEXT ("Sounds\\Destroying.wav") , NULL , SND_FILENAME | SND_SYNC);
			aux = !aux;
		}
		GameOverFrame3 (_myHero->_positionX , _myHero->_positionY);
	}
	else{ /*If Hero position just delete Hero*/
		PlaySound (TEXT ("Sounds\\Destroying.wav") , NULL , SND_FILENAME | SND_SYNC);
		GameOverFrame4 (_myHero->_positionX , _myHero->_positionY);
		PlaySound (TEXT ("Sounds\\Destroying.wav") , NULL , SND_FILENAME | SND_SYNC);
	}
	PlaySound (TEXT ("Sounds\\Death.wav") , NULL , SND_FILENAME | SND_ASYNC | SND_LOOP);
}

/**************************** Generate functions */
void World::GenerateEnemies ()
{
	if ( _myEnemies.size ()<MAX_OF_ENEMIES )
	if ( RandomDecision (_difficulty) )
	for ( int i = 0; i < NEW_ENEMY_NUMBER; i++ )
		_myEnemies.push_back (new Enemy);
}

void World::GenerateAmmo ()
{
	if ( _myAmmo.size ( ) < MAX_OF_AMMO )
	if ( RandomDecision (2) )
	for ( int i = 0; i < NEW_AMMO_NUMBER; i++ )
		_myAmmo.push_back (new Ammo);
}

void World::GenerateStars ()
{
	for ( int i = 0; i<_starsLeft; i++ )
		_myStars.push_back (new Star);
}

void World::GenerateBullets (const char input)
{
	
	if ( input == CHAR_SHOT_BULLET )
	if ( _bulletsLeft > 0 )
	{
		Beep (2900 , 20);
		_myBullets.push_back (new Bullet (_myHero->_positionX + 1 ,
			_myHero->_positionY));
		_bulletsLeft--;
	}
}

void World::GenerateScorePoint ()
{
	if ( _myScorePoint.size () < MAX_OF_SCORE_POINT)
	if ( RandomDecision (1) )
	for ( int i = 0; i < NEW_SCORE_POINT_NUMBER; i++ )
		_myScorePoint.push_back (new ScorePoint);
}


/********************************* Run functions */
void World::RunHero (const char input)
{
	if ( input != CHAR_NOT_VALID )
		_myHero->Run (input);
}

void World::RunEnemies ()
{
	for ( unsigned int i = 0; i < _myEnemies.size (); i++ ) //Run all the Enemies
		_myEnemies[i]->Run ();
	for ( unsigned int i = 0; i < _myEnemies.size (); i++ ) //Delete out of limit Enemies
	{
		if ( _myEnemies[i]->_positionX == ( POS_X_MIN - 1 ) )
		{
			delete _myEnemies[i];
			_myEnemies.erase (_myEnemies.begin () + i);
		}
	}
}

void World::RunBullets ()
{
	for ( unsigned int i = 0; i < _myBullets.size (); i++ ) //Run all the Bullets
		_myBullets[i]->Run ();
	for ( unsigned int i = 0; i < _myBullets.size (); i++ ) //Delete out of limit Bullets
	if ( _myBullets[i]->_positionX >= BORDER_SIZE_X )
	{
		delete _myBullets[i];
		_myBullets.erase (_myBullets.begin () + i);
	}
}

void World::RunStars ()
{
	for ( unsigned int i = 0; i<_myStars.size (); i++ ) //Run all the Stars
		_myStars[i]->Run ();
}
void World::RunAmmo ()
{
	for ( unsigned int i = 0; i < _myAmmo.size (); i++ ) //Run all the Enemies
		_myAmmo[i]->Run ();
	for ( unsigned int i = 0; i < _myAmmo.size (); i++ ) //Delete out of limit Enemies
	{
		if ( _myAmmo[i]->_positionX == ( POS_X_MIN - 1 ) )
		{
			delete _myAmmo[i];
			_myAmmo.erase (_myAmmo.begin () + i);
		}
	}
}
void World::RunScorePoint ()
{
	for ( unsigned int i = 0; i < _myScorePoint.size (); i++ ) //Run all the Enemies
		_myScorePoint[i]->Run ();
	for ( unsigned int i = 0; i < _myScorePoint.size (); i++ ) //Delete out of limit Enemies
	{
		if ( _myScorePoint[i]->_positionX == ( POS_X_MIN - 1 ) )
		{
			delete _myScorePoint[i];
			_myScorePoint.erase (_myScorePoint.begin () + i);
		}
	}
}

void World::UpdateScoreAndDifficulty ()
{
	_score++;				/*score*/
	if ( maxScore<_score )
		maxScore = _score;
	/*difficulty*/
	_difficultyCounter++;
	if ( ( _difficultyCounter / DIFFICULTY_UP_TIMER ) == 1 )
	{
		_difficultyCounter = 0;
		_difficulty++;
		if ( _enemiesLeft<MAX_OF_ENEMIES )
			_enemiesLeft++;
	}
}

/******************************* Print functions */
void World::Print ()
{
	PrintBlack ();

	for ( int i = 0; i < QUANTITY_OF_REDRAWING_ENTITIES; i++ ){
		PrintStars ();
		PrintHero ( );
		PrintBullets ( );
		PrintAmmo ( );
		PrintScorePoint ( );
		PrintEnemies ( );
		PrintHero ( );
	}
	PrintGameInfo ();
}

void World::PrintBorder ()
{
	GoToXY (0 , COUNTER_POSITION - 1);
	Color (172);
	printf ("%s   \n" , str.c_str ());
	printf ("%s   \n" , str.c_str ());
	printf ("%s   \n" , str.c_str ());
	printf ("%s   \n" , str.c_str ());
	GoToXY (0 , POS_Y_MAX+1);
	printf ("%s   \n" , str.c_str ());
	for ( int i = 0; i < POS_Y_MAX + 1; i++ )
	{
		GoToXY (POS_X_MAX + 5 , i+1);
		printf (" ");
	}
	Color (7);

}

void World::PrintHelp ()
{
	GoToXY (0 , HELP_POSITION);
	Color (15);
	_myAmmo.push_back (new Ammo);
	_myScorePoint.push_back (new ScorePoint);
	
	//CONTROL HELP
	printf ("CONTROLS: w-UP | s-DOWN | a-LEFT | d-RIGHT | p-SHOOT\n");
	
	//AMMO ICON
	printf ("AMMO: ",AMMO_MODEL);
	Color (_myAmmo[0]->GetColor () , _myAmmo[0]->GetColor2 ());
	printf ("%c" , AMMO_MODEL);
	Color (15);
	printf (" (+1 AMMO)\n");
	
	//SCORE_POINT ICON
	
	printf ("SCORE POINT: " , AMMO_MODEL);
	Color (_myScorePoint[0]->GetColor () , _myScorePoint[0]->GetColor2 ());
	printf ("%c" , SCORE_POINT_MODEL);
	Color (15);
	printf (" (+500 SCORE)\n");

	//HERO ICON
	Color (10);
	printf ("HERO: %c\n",HERO_MODEL);
	
	//ENEMY ICON
	Color (14);
	printf ("ENEMY: %c\n" , ENEMY_MODEL);

	delete _myAmmo[0];
	_myAmmo.erase (_myAmmo.begin ());
	delete _myScorePoint[0];
	_myScorePoint.erase (_myScorePoint.begin ());


	Color (7);
}

void World::PrintStars ()
{
	for ( unsigned int i = 0; i < _myStars.size (); i++ )
	{
		GoToXY (_myStars[i]->_positionX ,
				_myStars[i]->_positionY);
		Color (_myStars[i]->GetColor ());
		printf ("%c  " , STAR_MODEL);
		Color (7);
	}
	Color (7);
}
void World::PrintAmmo ()
{
	for ( unsigned int i = 0; i < _myAmmo.size (); i++ )
	{
		GoToXY (_myAmmo[i]->_positionX ,
				_myAmmo[i]->_positionY);
		Color (_myAmmo[i]->GetColor () , _myAmmo[i]->GetColor2 ());
		printf ("%c" , AMMO_MODEL);
		Color (7);
	}
	Color (7);
}
void World::PrintScorePoint ()
{
	for ( unsigned int i = 0; i < _myScorePoint.size (); i++ )
	{
		GoToXY (_myScorePoint[i]->_positionX ,
				_myScorePoint[i]->_positionY);
		Color (_myScorePoint[i]->GetColor () , _myScorePoint[i]->GetColor2 ());
		printf ("%c" , SCORE_POINT_MODEL);
		Color (7);
	}
	Color (7);
}

void World::PrintBullets ()
{
	Color (10);
	for ( unsigned int i = 0; i < _myBullets.size (); i++ )
	{
		GoToXY (_myBullets[i]->_positionX ,
				_myBullets[i]->_positionY);
		printf ("%c " , BULLET_MODEL);
	}
	Color (7);
}

void World::PrintEnemies ()
{
	for ( unsigned int i = 0; i < _myEnemies.size (); i++ )
	{
		GoToXY (_myEnemies[i]->_positionX ,
				_myEnemies[i]->_positionY);
		{
			Color (14);
			printf ("%c" , ENEMY_MODEL);
			Color (12);
			printf ("[=-");
		}
	}
	Color (7);
}

void World::PrintHero ()
{
	Color (12);
	if ( _myHero->_positionX > POS_X_MIN )
	{
		GoToXY (_myHero->_positionX - 2 , _myHero->_positionY);
		printf ("=}");
	}
	Color (10);
	GoToXY (_myHero->_positionX , _myHero->_positionY);
	printf ("%c" , HERO_MODEL);
	GoToXY (_myHero->_positionX + 1 , _myHero->_positionY);
	printf ("c");
	Color (7);
}

void World::PrintGameInfo ()
{
	Color (162);
	GoToXY (0 , COUNTER_POSITION);
	Color (160);
	printf ("  AMMO ");
	Color (172);
	for ( int i = 0; i < _bulletsLeft; i++ )
	{
		printf (" ");
		Color (204);
		printf (" ");
		Color (172);
	}
	for ( unsigned int i = 0; i < ( NUMBER_OF_BULLETS - _bulletsLeft ); i++ )
	{
		printf (" ");
		Color (34);
		printf (" ");
		Color (172);
	}
	for ( int i = 0; i<( 33 - NUMBER_OF_BULLETS ); i++ )
	{
		Color (162);
		printf (" ");
	}
	Color (160);
	printf (" RECORD ");
	Color (32);
	printf ("%6i " , maxScore);
	Color (162);
	GoToXY (64 , COUNTER_POSITION);
	Color (160);
	printf (" SCORE ");
	Color (32);
	printf ("%6i " , _score);
	Color (162);
	GoToXY (0 , COUNTER_POSITION + 1);
	Color (172);
	GoToXY (0 , COUNTER_POSITION + 2);
	Color (7);
}

void World::PrintBlack ()
{
	
	GoToXY (POS_X_MIN - 1 , COUNTER_POSITION+3);
	for ( int y = POS_Y_MIN; y <= POS_Y_MAX; y++ )
	{
		printf ("%s\n" , str.c_str ( ));
	}
}

/*************************** Collition functions */
void World::Collitions ()
{
	bool flag = false;
	for ( unsigned int b = 0; b < _myBullets.size (); b++ ) /*For each Bullet*/
	{
		flag = false;
		for ( unsigned int e = 0; e < _myEnemies.size (); e++ ) /*If pos = an enemy*/
		{
			if ( ( _myEnemies[e]->_positionX == _myBullets[b]->_positionX )
				&& ( _myEnemies[e]->_positionY == _myBullets[b]->_positionY ) )
			{
				Beep (450 , 10);
				delete _myEnemies[e]; /*Delete that enemy*/
				_myEnemies.erase (_myEnemies.begin () + e);
				//_enemiesLeft++;
				flag = true;
				_score += 100;
			}
		}
		if ( flag ) /*And delete that bullet*/
		{
			delete _myBullets[b];
			_myBullets.erase (_myBullets.begin () + b);
		}
	}
}

void World::HeroCollitions ()
{
	for ( unsigned int e = 0; e < _myEnemies.size (); e++ )
	{
		if ( ( _myEnemies[e]->_positionX == _myHero->_positionX )
			&& ( _myEnemies[e]->_positionY == _myHero->_positionY ) )
		{
			SwitchActivation ();
		}
	}
	for ( unsigned int e = 0; e < _myAmmo.size (); e++ )
	{
		if ( ( _myAmmo[e]->_positionX == _myHero->_positionX )
			&& ( _myAmmo[e]->_positionY == _myHero->_positionY ) )
		{
			Beep (3500 , 10);
			if ( _bulletsLeft < NUMBER_OF_BULLETS )
				_bulletsLeft++;
			delete _myAmmo[e]; /*Delete that enemy*/
			_myAmmo.erase (_myAmmo.begin () + e);
		}
	}
	for ( unsigned int e = 0; e < _myScorePoint.size (); e++ )
	{
		if ( ( _myScorePoint[e]->_positionX == _myHero->_positionX )
			&& ( _myScorePoint[e]->_positionY == _myHero->_positionY ) )
		{
			Beep (3500 , 10);
			_score += 500;
			delete _myScorePoint[e]; /*Delete that enemy*/
			_myScorePoint.erase (_myScorePoint.begin () + e);
		}
	}
}