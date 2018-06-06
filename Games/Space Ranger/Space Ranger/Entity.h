#pragma once
class Entity	
{
public:
	Entity ( );
	virtual ~Entity ( );
	virtual void Run () = 0;
	unsigned int _positionX;
	unsigned int _positionY;
	char _model;
};

