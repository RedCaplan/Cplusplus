#include "InputManager.h"
#include <conio.h>
#include "utils.h"
#include "base.h"

InputManager::InputManager (World* myWorld)
{
	_myWorld = myWorld;
}

InputManager::~InputManager ()
{

}

void InputManager::Run ()
{
	char input = GetUserInput ();
	_myWorld->Run (input);
}

bool InputManager::GetAnyKey () const
{
	bool keyPressed = false;
	if ( _kbhit () )
		keyPressed = true;
	return keyPressed;
}

char InputManager::GetUserYesNo () const
{
	char keyPressed = CHAR_NOT_VALID;
	if ( _kbhit () )
	{
		keyPressed = _getch ();
		ValidateKeyYesNo (keyPressed);
	}
	return keyPressed;
}

char InputManager::GetUserInput () const
{
	char keyPressed = CHAR_NOT_VALID;
	if ( _kbhit () )
	{
		keyPressed = _getch ();
		ValidateKey (keyPressed);
	}
	return keyPressed;
}

void InputManager::ValidateKey (char& input) const
{
	if ( !( input == CHAR_MOVE_LEFT || input == CHAR_MOVE_RIGHT
		|| input == CHAR_MOVE_UP || input == CHAR_MOVE_DOWN
		|| input == CHAR_SHOT_BULLET ) )
	{
		input = CHAR_NOT_VALID;
	}
}

void InputManager::ValidateKeyYesNo (char& input) const
{
	if ( !( input == 'y' || input == 'n' ) )
		input = CHAR_NOT_VALID;
}