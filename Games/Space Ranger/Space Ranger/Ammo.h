#pragma once
#include "Entity.h"
class Ammo :
	public Entity
{
public:
	Ammo ( );
	~Ammo ( );
	void Run ();
	int GetColor ();
	int GetColor2 ();
private:
	int _color;
	int _color2;
};

