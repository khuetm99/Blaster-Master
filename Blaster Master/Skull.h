#pragma once
#include"Object.h";

class Skull : public Object
{
public:
	enum ANIMATIONS
	{
		IDLERIGHT,
		IDLELEFT,
		ATTACKRIGHT,
		ATTACKLEFT,
		DIE,
		_LENGHT
	};

	Skull(int x, int y, int width, int height);
	void Init();
	void Update(DWORD dt);
	void PhysicalCalculate(DWORD dt);
	void Render();
};
typedef Skull* LPSKULL;