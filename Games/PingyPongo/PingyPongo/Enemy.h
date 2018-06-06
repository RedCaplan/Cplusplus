#pragma once
#include "Entity.h"
#include "Ball.h"
class Enemy :
	public Entity
{
public:
	Enemy ();
	virtual ~Enemy ();
	void Run ( ){};
	void Run (char* obj);
};

