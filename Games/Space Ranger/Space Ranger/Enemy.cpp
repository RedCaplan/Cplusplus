#include "Enemy.h"
#include "utils.h"
#include "base.h"


Enemy::Enemy ( )
{
	_positionX = POS_X_MAX;
	_positionY = RandomInt (POS_Y_MIN , POS_Y_MAX + 1);
	_model = ENEMY_MODEL;
}


Enemy::~Enemy ( )
{
}

void Enemy::Run ()
{
	if ( _positionX != POS_X_MIN - 1 )
		_positionX--;
}