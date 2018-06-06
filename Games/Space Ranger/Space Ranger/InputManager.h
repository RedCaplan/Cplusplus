#pragma once

#include "World.h"

class InputManager
{
public:
	InputManager (World* myWorld);
	~InputManager ();
	void Run ();
	bool GetAnyKey () const;
	char GetUserYesNo () const;

private:
	World* _myWorld;
	char GetUserInput () const;
	void ValidateKey (char& input) const;
	void ValidateKeyYesNo (char& input) const;
};


