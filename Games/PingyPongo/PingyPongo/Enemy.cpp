#include "Enemy.h"
#include "utils.h"
#include "base.h"
#include "Ball.h"

Enemy::Enemy ()
{
	_positionX = POS_X_MAX;
	_positionY = ( POS_Y_MIN + POS_Y_MAX ) / 2 + ENEMY_SIZE/2;
	_model = ENEMY_MODEL;
	_color1 = 9;
}


Enemy::~Enemy ()
{
}

void Enemy::Run (char* obj)
{
	if ( obj == "UP" )
		_positionY--;
	else if ( obj == "DOWN" )
		_positionY++;
}