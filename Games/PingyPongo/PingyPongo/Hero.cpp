#include "Hero.h"
#include "utils.h"
#include "base.h"

Hero::Hero ()
{
	_positionX = POS_X_MIN;
	_positionY = (POS_Y_MIN + POS_Y_MAX) / 2 + HERO_SIZE/2;
	_speed = HERO_SPEED;
	_model = HERO_MODEL;
	_color1 = 12;
}

Hero::~Hero ()
{
}

void Hero::Run ()
{

}

void Hero::Run (const char direction)
{
	if ( ValidateMovement (direction) == true )
		MoveHero (direction);
}

bool Hero::ValidateMovement (const char direction)
{
	bool aux = false;
	switch ( direction )
	{
		case CHAR_MOVE_UP:
				aux = true;
			break;
		case CHAR_MOVE_DOWN:
				aux = true;
			break;
	}
	return aux;
}

void Hero::MoveHero (const char direction)
{
	switch ( direction )
	{
		case CHAR_MOVE_UP:
			_positionY = _positionY - _speed;
			break;
		case CHAR_MOVE_DOWN:
			_positionY = _positionY + _speed;
			break;
	}
}