#pragma once
#include "Entity.h"
class Hero :
	public Entity
{
public:
	Hero ();
	~Hero ();
	void Run ();
	void Run (const char moveDirection);
private:
	int _speed;
	bool ValidateMovement (const char direction);
	void MoveHero (const char direction);
};

