#include "Star.h"
#include "utils.h"
#include "base.h"

Star::Star ()
{
	_positionX = RandomInt (POS_X_MIN , POS_X_MAX);
	_positionY = RandomInt (POS_Y_MIN , POS_Y_MAX);
	if ( RandomDecision (50) )
		_color = 7;
	else
		_color = 8;
}

Star::~Star ()
{

}

void Star::Run ()
{
	_positionX--;
	if ( _positionX == POS_X_MIN )
		ResetStar ();
}

int Star::GetColor ()
{
	return _color;
}

void Star::ResetStar ()
{
	_positionX = POS_X_MAX;
	_positionY = RandomInt (POS_Y_MIN , POS_Y_MAX);
	if ( RandomDecision (50) )
		_color = 7;
	else
		_color = 8;
}