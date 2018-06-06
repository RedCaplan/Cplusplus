#include "ScorePoint.h"
#include "utils.h"
#include "base.h"

ScorePoint::~ScorePoint ()
{
}
ScorePoint::ScorePoint ()
{
	_positionX = POS_X_MAX;
	_positionY = RandomInt (POS_Y_MIN , POS_Y_MAX);
	_color = 3;
	_color2 = 14;
}

void ScorePoint::Run ()
{
	if ( _positionX != POS_X_MIN - 1 )
		_positionX--;
}

int ScorePoint::GetColor ()
{
	return _color;
}

int ScorePoint::GetColor2 ()
{
	return _color2;
}
