#pragma once
#include"Object.h";

class Domes : public Object
{
public:
	enum ANIMATIONS
	{
		WALKRIGHT,
		WALKLEFT,
		WALKDOWNRIGHT,
		WALKDOWNLEFT,
		WALKUPRIGHT,
		WALKUPLEFT,
		WALKREVERSERIGHT,
		WALKREVERSELEFT,
		DIE,
		_LENGHT
	};

	Domes(int x, int y, int width, int height);
	void Init();
	void Update(DWORD dt);
	void PhysicalCalculate(DWORD dt);
	void Render();
	~Domes();
};
typedef Domes* LPDOMES;

