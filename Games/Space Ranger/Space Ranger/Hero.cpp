#include "Hero.h"
#include "utils.h"
#include "base.h"

Hero::Hero ()
{
	_positionX = HERO_STARTING_X;
	_positionY = HERO_STARTING_Y;
	_speed = HERO_SPEED;
	_model = HERO_MODEL;
}

Hero::~Hero ( )
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
			if ( _positionY != POS_Y_MIN )
				aux = true;
			break;
		case CHAR_MOVE_DOWN:
			if ( _positionY != POS_Y_MAX )
				aux = true;
			break;
		case CHAR_MOVE_LEFT:
			if ( _positionX != POS_X_MIN )
				aux = true;
			break;
		case CHAR_MOVE_RIGHT:
			if ( _positionX != POS_X_MAX )
				aux = true;
			break;
	}
	return aux;
}

void Hero::MoveHero (const char direction)
{
	switch ( direction )
	{
		case CHAR_MOVE_LEFT:
			_positionX = _positionX - _speed;
			break;
		case CHAR_MOVE_RIGHT:
			_positionX = _positionX + _speed;
			break;
		case CHAR_MOVE_UP:
			_positionY = _positionY - _speed;
			break;
		case CHAR_MOVE_DOWN:
			_positionY = _positionY + _speed;
			break;
	}
}