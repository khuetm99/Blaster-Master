#pragma once
#include"Object.h";

class Orb : public Object
{
public:
	enum ANIMATIONS
	{
		TURN,
		TURNRIGHT,
		TURNLEFT,
		FLYRIGHT,
		FLYLEFT,
		DIE,
		_LENGHT
	};

	Orb(int x, int y, int width, int height);
	void Init();
	void Update(DWORD dt);
	void PhysicalCalculate(DWORD dt);
	void Render();
};
typedef Orb* LPORB;