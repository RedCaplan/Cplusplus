#pragma once
#include "Entity.h"
class Bullet :
	public Entity
{
public:
	Bullet (int x, int y );
	virtual ~Bullet ( );
	void Run ( );
};

