#pragma once
#include "Object.h"

class Teleporter : public Object
{
public:
	enum ANIMATIONS
	{
		IDLEGRAY,
		IDLEGREEN,
		DIE,
		_LENGHT
	};

	Teleporter(int x, int y, int width, int height);
	void Init();
	void Update(DWORD dt);
	void PhysicalCalculate(DWORD dt);
	void Render();
};
typedef Teleporter* LPTELEPORTER;

