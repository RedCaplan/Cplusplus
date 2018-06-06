#pragma comment(lib,"Winmm.lib")

#include "Bullet.h"
#include "Enemy.h"
#include "Hero.h"
#include "Star.h"
#include "World.h"
#include "InputManager.h"
#include "utils.h"
#include "base.h"
#include "Menu.h"

/*Aux Functions Declatarion*/
void WorldAndManagerInicialization ();
void WorldAndManagerDestruction ();
void GameIntroScreen ();
void GameLoop ();

/*Game Objects*/
World* gameWorld = NULL;
InputManager* userInputManager = NULL;

/*Main Function*/
int main ()
{
	HideCursor ();
	WorldAndManagerInicialization ();
	GameLoop ();
	WorldAndManagerDestruction ();
	return 0;
}

/*Aux Functions Definition*/
void WorldAndManagerInicialization ()
{
	
	system ("cls");
	gameWorld = new World ();
	userInputManager = new InputManager (gameWorld);
	gameWorld->InitializeWorld ();
	gameWorld->SwitchActivation ( );
}

void WorldAndManagerDestruction ()
{
	delete gameWorld;
	delete userInputManager;
}

void GameIntroScreen ()
{
	PlaySound (TEXT ("Sounds\\MainMenu.wav") , NULL , SND_FILENAME | SND_ASYNC | SND_LOOP);
	char CheckHit=0;
	system ("cls");
	while ( !CheckHit )
	{
		CheckHit = _kbhit ( );
		gameWorld->PrintWelcomeScreen ( );
	}
	Sleep (200);
}

void PlayAgain (char& aux , bool& wantPlay)
{
	aux = CHAR_NOT_VALID;
	while ( aux == CHAR_NOT_VALID )
	{
		aux = userInputManager->GetUserYesNo ();
		if ( aux == 'y' )
		{
			WorldAndManagerDestruction ();
			WorldAndManagerInicialization ();
		}
		else if ( aux == 'n' )
			wantPlay = false;
	}
}

void DifficultyMenu ()
{
	system ("cls");
	Menu DifficultyMenu;
	int diff = DifficultyMenu.Show ( );
	switch ( diff )
	{
		case 0: gameWorld->INITIAL_DIFFICULTY = 1; break;
		case 1: gameWorld->INITIAL_DIFFICULTY = 5; break;
		case 2: gameWorld->INITIAL_DIFFICULTY = 10; break;
		case 3: exit(0); break;
	}
}

void GameLoop ()
{
	
	char aux = CHAR_NOT_VALID;
	bool wantPlay = true;



	while ( wantPlay )
	{
		GameIntroScreen ();
		DifficultyMenu ();
		PlaySound (TEXT ("Sounds\\GamePlay.wav") , NULL , SND_FILENAME | SND_ASYNC | SND_LOOP);
		/* Game Playing */
		gameWorld->PrintHelp ( );
		gameWorld->PrintBorder ();
		while ( gameWorld->IsActive () )
			userInputManager->Run ();
		/* Game Over */
		gameWorld->PrintGameOverAnimation ();
		gameWorld->PrintGameOverScreen ();
		/* Play Again ? */
		PlayAgain (aux , wantPlay);
	}
}

