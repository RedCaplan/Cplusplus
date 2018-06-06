#include "utils.h"

//SLEEP
unsigned const int SLEEP_VALUE_IN_MS = 30;		//Default: 30

//SCORE 
unsigned static int LeftScore = 0;
unsigned static int RightScore = 0;

//MODELS-
const char BALL_MODEL = 'o';                    //Default: 'o'
const char HERO_MODEL = 176;                    //Default: 176
const char ENEMY_MODEL = 176;		        	//Default: 176

//NUMBER OF ENTITIES
unsigned const int BALL_SPEED = 1;		        //Default 2
unsigned const int HERO_SPEED = 1;		        //Default 1
unsigned const int ENEMY_INTELLIGENCE = 70;     //Default 50 (MAX = 100)
unsigned const int HERO_SIZE = 6;		        //Default 5
unsigned const int ENEMY_SIZE = 6;		        //Default 5

//KEY BINDINGS
const char CHAR_NOT_VALID = '!';				//Default: '!'
const char CHAR_MOVE_LEFT = 'a';				//Default: 'a'
const char CHAR_MOVE_RIGHT = 'd';				//Default: 'd'
const char CHAR_MOVE_UP = 'w';					//Default: 'w'
const char CHAR_MOVE_DOWN = 's';				//Default: 's'

//BORDER
unsigned const int BORDER_SIZE_X = 100;			//Default: 50
unsigned const int BORDER_SIZE_Y = 20;			//Default: 30

//GAME VALID POSITIONS 
unsigned const int POS_X_MIN = 1;				//Default: 1
unsigned const int POS_X_MAX = BORDER_SIZE_X-1;	//Default: 49
unsigned const int POS_Y_MIN = 1;				//Default: 1
unsigned const int POS_Y_MAX = BORDER_SIZE_Y-1;	//Default: 29

//ANIMATION FRAMES
unsigned const int QUANTITY_OF_REDRAWING_ENTITIES = 3;       //Default: 2

static void WelcomeScreenFrame1 ()
{
	Color (RandomInt (1 , 14));
	GoToXY (0 , POS_Y_MIN - 1);
	printf ("\n");
	printf ("\n");
	printf ("\n");
	printf ("                            ...press any key to scape!");
	Sleep (70);



}