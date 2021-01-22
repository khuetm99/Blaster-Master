#pragma once
#include"Object.h";

class Floater : public Object {
public:
	enum ANIMATIONS
	{
		FLYRIGHT,
		FLYLEFT,
		DIE,
		_LENGHT
	};

	Floater(int x, int y, int width, int height);
	void Init();
	void Update(DWORD dt);
	void PhysicalCalculate(DWORD dt);
	void Render();
};
typedef Floater* LPFLOATER;

