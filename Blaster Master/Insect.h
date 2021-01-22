#pragma once
#include"Object.h";

class Insect : public Object
{
public:
	enum ANIMATIONS
	{
		IDLERIGHT,
		IDLELEFT,
		FLYRIGHT,
		FLYLEFT,
		DIE,
		_LENGHT
	};

	Insect(int x, int y, int width, int height);
	void Init();
	void Update(DWORD dt);
	void PhysicalCalculate(DWORD dt);
	void Render();
};
typedef Insect* LPINSECT;

