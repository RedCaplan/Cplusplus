#include "Bullet.h"
#include "utils.h"
#include "base.h"

Bullet::Bullet (int x , int y)
{
	_positionX = x;
	_positionY = y;
	_model = BULLET_MODEL;
}

Bullet::~Bullet ( )
{
}

void Bullet::Run ()
{
	_positionX++;
}
