#include "Ball.h"
#include "Enemy.h"
#include "Hero.h"
#include "World.h"
#include "InputManager.h"
#include "utils.h"
#include "base.h"
#include <ctime>

/*Aux Functions Declatarion*/
void WorldAndManagerInicialization ();
void WorldAndManagerDestruction ();
void GameLoop ();

/*Game Objects*/
World* gameWorld = NULL;
InputManager* userInputManager = NULL;

/*Main Function*/
int main ()
{
	srand (time (0));
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
	gameWorld->SwitchActivation ();
}

void WorldAndManagerDestruction ()
{
	delete gameWorld;
	delete userInputManager;
}



void GameLoop ()
{

	char aux = CHAR_NOT_VALID;
	
	gameWorld->PrintBorder ( );
	gameWorld->PrintScore ( );

	/* Game Playing */
	while ( gameWorld->IsActive () )
		userInputManager->Run ();

	WorldAndManagerDestruction ();
	WorldAndManagerInicialization ();
	GameLoop ( );
}