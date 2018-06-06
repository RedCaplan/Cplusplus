#include "Ammo.h"
#include "utils.h"
#include "base.h"



Ammo::~Ammo ( )
{
}
Ammo::Ammo ()
{
	_positionX = POS_X_MAX;
	_positionY = RandomInt (POS_Y_MIN , POS_Y_MAX);
	_color = 13;
	_color2 = 10;
}

void Ammo::Run ()
{
	if ( _positionX != POS_X_MIN - 1 )
		_positionX--;
}

int Ammo::GetColor ()
{
	return _color;
}
int Ammo::GetColor2 ()
{
	return _color2;
}
