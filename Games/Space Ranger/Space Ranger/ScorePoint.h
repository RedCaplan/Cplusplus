#pragma once
#include "Entity.h"
class ScorePoint :
	public Entity
{
public:
	ScorePoint ( );
	~ScorePoint ( );
	void Run ();
	int GetColor ();
	int GetColor2 ();
private:
	int _color;
	int _color2;
};

