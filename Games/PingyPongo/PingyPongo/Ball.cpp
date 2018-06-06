#include "Ball.h"
#include "utils.h"
#include "base.h"


Ball::Ball ( )
{
	_positionX = ( POS_X_MIN + POS_X_MAX ) / 2;
	_positionY = ( POS_Y_MIN + POS_Y_MAX ) / 2;
	_model = BALL_MODEL;
	_color1 = 10;
	_MoveLeft = RandomDecision (50);
	_MoveUp = RandomDecision (50);
}


Ball::~Ball ( )
{
}

void Ball::Run ( )
{
	if ( _positionY == POS_Y_MIN || _positionY == POS_Y_MAX )
		_MoveUp = !_MoveUp;

	if ( _MoveUp )
		_positionY--;
	else
		_positionY++;

	if ( _MoveLeft )
		_positionX--;
	else
		_positionX++;
}
