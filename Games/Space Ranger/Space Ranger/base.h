#include "utils.h"


//SLEEP
unsigned const int SLEEP_VALUE_IN_MS = 30;		//Default: 30

//MAX SCORE 
unsigned static int maxScore = 0;

//MODELS
const char BULLET_MODEL = '-';                  //Default: 10
const char HERO_MODEL = 1;                      //Default: 1 (Happy Smiley)
const char ENEMY_MODEL = 2;						//Default: 2 (Sad Smiley)
const char STAR_MODEL = '*';					//Default: '*'
const char AMMO_MODEL = 'A';					//Default: 'A'
const char SCORE_POINT_MODEL = 'S';				//Default: 'S'

//DIFICULTY
unsigned const int DIFFICULTY_UP_TIMER = 100;	//Default: 100

//NUMBER OF ENTITIES
unsigned const int STAR_SPEED = 2;		        //Default 2
unsigned const int NUMBER_OF_BULLETS = 10;		//Default: 10
unsigned const int NEW_ENEMY_NUMBER = 1;		//Default 1
unsigned const int NEW_AMMO_NUMBER = 1;	     	//Default 1
unsigned const int NEW_SCORE_POINT_NUMBER = 1;	//Default 1
unsigned const int MAX_OF_ENEMIES = 15;			//Default 50
unsigned const int MAX_OF_AMMO = 2;		      	//Default 2
unsigned const int MAX_OF_SCORE_POINT = 1;		//Default 1
unsigned const int NUMBER_OF_STARS = 15;		//Default: 30

//HERO STARTING ATTRIBUTES
unsigned const int HERO_STARTING_X = 10;		//Default: 10
unsigned const int HERO_STARTING_Y = 10;		//Default: 10
unsigned const int HERO_SPEED = 1;				//Default: 1

//GAME VALID POSITIONS 
unsigned const int POS_X_MIN = 1;				//Default: 1
unsigned const int POS_X_MAX = 100;				//Default: 100 
unsigned const int POS_Y_MIN = 5;				//Default: 5
unsigned const int POS_Y_MAX = 30;				//Default: 30
//KEY BINDINGS
const char CHAR_NOT_VALID = '!';				//Default: '!'
const char CHAR_MOVE_LEFT = 'a';				//Default: 'a'
const char CHAR_MOVE_RIGHT = 'd';				//Default: 'd'
const char CHAR_MOVE_UP = 'w';					//Default: 'w'
const char CHAR_MOVE_DOWN = 's';				//Default: 's'
const char CHAR_SHOT_BULLET = 'p';				//Default: 'p'

//BORDER
unsigned const int BORDER_SIZE_X = 101;			//Default: 101
unsigned const int BORDER_SIZE_Y = 32;			//Default: 32
unsigned const int COUNTER_POSITION = 2;		//Default: 2
unsigned const int HELP_POSITION = 40;		    //Default: 40

//ANIMATION FRAMES
unsigned const int GAME_OVER_FRAME_X = 8;       //Default: 8
unsigned const int QUANTITY_OF_REDRAWING_ENTITIES = 1;       //Default: 2

static void GameOverFrame1 (int x , int y)
{
	Color (4);
	GoToXY (x - 2 , y - 1);
	printf (" *   *");
	GoToXY (x - 2 , y);
	printf ("   *  ");
	GoToXY (x - 1 , y + 1);
	printf ("*   *");
}

static void GameOverFrame2 (int x , int y)
{
	Color (6);
	GoToXY (x - 2 , y - 1);
	printf ("   *   ");
	GoToXY (x - 2 , y);
	printf (" *   * ");
	GoToXY (x - 2 , y + 1);
	printf ("   *   ");
}

static void GameOverFrame3 (int x , int y)
{
	Color (0);
	GoToXY (x - 2 , y - 1);
	printf ("       ");
	GoToXY (x - 2 , y);
	printf ("       ");
	GoToXY (x - 1 , y + 1);
	printf ("       ");
}

static void GameOverFrame4 (int x , int y)
{
	Color (0);
	GoToXY (x - 2 , y);
	printf ("      ");
}

static void WelcomeScreenFrame1 ()
{
	Color (RandomInt (1 , 14));
	GoToXY (0 , POS_Y_MIN - 1);
	printf ("\n");
	printf ("\n");
	printf ("\n");
	printf ("  ▄▄▄▄▄▄▄▄▄▄   ▄▄▄▄▄▄▄▄▄▄▄   ▄▄▄▄▄▄▄▄▄▄▄   ▄▄▄▄▄▄▄▄▄▄▄   ▄▄▄▄▄▄▄▄▄▄▄            ▄▄▄▄▄▄▄▄▄▄▄   ▄▄▄▄▄▄▄▄▄▄▄   ▄▄        ▄   ▄▄▄▄▄▄▄▄▄▄▄   ▄▄▄▄▄▄▄▄▄▄▄   ▄▄▄▄▄▄▄▄▄▄▄ \n");
	printf (" ▐░░░░░░░░░░░▌ ▐░░░░░░░░░░░▌ ▐░░░░░░░░░░░▌ ▐░░░░░░░░░░░▌ ▐░░░░░░░░░░░▌          ▐░░░░░░░░░░░▌ ▐░░░░░░░░░░░▌ ▐░░▌      ▐░▌ ▐░░░░░░░░░░░▌ ▐░░░░░░░░░░░▌ ▐░░░░░░░░░░░▌\n");
	printf (" ▐░█▀▀▀▀▀▀▀▀▀  ▐░█▀▀▀▀▀▀▀█░▌ ▐░█▀▀▀▀▀▀▀█░▌ ▐░█▀▀▀▀▀▀▀▀▀  ▐░█▀▀▀▀▀▀▀▀▀           ▐░█▀▀▀▀▀▀▀█░▌ ▐░█▀▀▀▀▀▀▀█░▌ ▐░▌░▌     ▐░▌ ▐░█▀▀▀▀▀▀▀▀▀  ▐░█▀▀▀▀▀▀▀▀▀  ▐░█▀▀▀▀▀▀▀█░▌\n");
	printf (" ▐░▌           ▐░▌       ▐░▌ ▐░▌       ▐░▌ ▐░▌           ▐░▌                    ▐░▌       ▐░▌ ▐░▌       ▐░▌ ▐░▌▐░▌    ▐░▌ ▐░▌           ▐░▌           ▐░▌       ▐░▌\n");
	printf (" ▐░█▄▄▄▄▄▄▄▄▄  ▐░█▄▄▄▄▄▄▄█░▌ ▐░█▄▄▄▄▄▄▄█░▌ ▐░▌           ▐░█▄▄▄▄▄▄▄▄▄           ▐░█▄▄▄▄▄▄▄█░▌ ▐░█▄▄▄▄▄▄▄█░▌ ▐░▌ ▐░▌   ▐░▌ ▐░▌ ▄▄▄▄▄▄▄▄  ▐░█▄▄▄▄▄▄▄▄▄  ▐░█▄▄▄▄▄▄▄█░▌\n");
	printf (" ▐░░░░░░░░░░░▌ ▐░░░░░░░░░░░▌ ▐░░░░░░░░░░░▌ ▐░▌           ▐░░░░░░░░░░░▌          ▐░░░░░░░░░░░▌ ▐░░░░░░░░░░░▌ ▐░▌  ▐░▌  ▐░▌ ▐░▌▐░░░░░░░░▌ ▐░░░░░░░░░░░▌ ▐░░░░░░░░░░░▌\n");
	printf ("  ▀▀▀▀▀▀▀▀▀█░▌ ▐░█▀▀▀▀▀▀▀▀▀  ▐░█▀▀▀▀▀▀▀█░▌ ▐░▌           ▐░█▀▀▀▀▀▀▀▀▀           ▐░█▀▀▀▀█░█▀▀  ▐░█▀▀▀▀▀▀▀█░▌ ▐░▌   ▐░▌ ▐░▌ ▐░▌ ▀▀▀▀▀▀█░▌ ▐░█▀▀▀▀▀▀▀▀▀  ▐░█▀▀▀▀█░█▀▀ \n");
	printf ("           ▐░▌ ▐░▌           ▐░▌       ▐░▌ ▐░▌           ▐░▌                    ▐░▌     ▐░▌   ▐░▌       ▐░▌ ▐░▌    ▐░▌▐░▌ ▐░▌       ▐░▌ ▐░▌           ▐░▌     ▐░▌  \n");
	printf ("  ▄▄▄▄▄▄▄▄▄█░▌ ▐░▌           ▐░▌       ▐░▌ ▐░█▄▄▄▄▄▄▄▄▄  ▐░█▄▄▄▄▄▄▄▄▄           ▐░▌      ▐░▌  ▐░▌       ▐░▌ ▐░▌     ▐░▐░▌ ▐░█▄▄▄▄▄▄▄█░▌ ▐░█▄▄▄▄▄▄▄▄▄  ▐░▌      ▐░▌ \n");
	printf (" ▐░░░░░░░░░░░▌ ▐░▌           ▐░▌       ▐░▌ ▐░░░░░░░░░░░▌ ▐░░░░░░░░░░░▌          ▐░▌       ▐░▌ ▐░▌       ▐░▌ ▐░▌      ▐░░▌ ▐░░░░░░░░░░░▌ ▐░░░░░░░░░░░▌ ▐░▌       ▐░▌\n");
	printf ("  ▀▀▀▀▀▀▀▀▀▀▀   ▀             ▀         ▀   ▀▀▀▀▀▀▀▀▀▀▀   ▀▀▀▀▀▀▀▀▀▀▀            ▀         ▀   ▀         ▀   ▀        ▀▀   ▀▀▀▀▀▀▀▀▀▀▀   ▀▀▀▀▀▀▀▀▀▀▀   ▀         ▀ \n");
	printf ("\n");
	printf ("\n");
	printf ("                            ...press any key to scape!");
	Sleep (70);


                                                                                                                                                         
}