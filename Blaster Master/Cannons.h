#pragma once
#include "Object.h"

class Cannons : public Object
{
public:
	enum ANIMATIONS
	{
		IDLE,
		ATTACKHORIZONTAL,
		ATTACKVERTICAL,
		DIE,
		_LENGHT
	};

	Cannons(int x, int y, int width, int height);
	void Init();
	void Update(DWORD dt);
	void PhysicalCalculate(DWORD dt);
	void Render();
};
typedef Cannons* LPCANNONS;