#pragma once
#include "Entity.h"
class Ball :
	public Entity
{
public:
	Ball ( );
	~Ball ( );
	void Run ();
	bool _MoveLeft;
	bool _MoveUp;
private:
	int _speed;
	
};

