#pragma once
#include "Object.h"

class EyeBall : public Object
{
public:
	enum ANIMATIONS
	{
		IDLE,
		OPENEYERIGHT,
		OPENEYELEFT,
		ROLLEYE,
		DIE,
		_LENGHT
	};

	EyeBall(int x, int y, int width, int height);
	void Init();
	void Update(DWORD dt);
	void PhysicalCalculate(DWORD dt);
	void Render();
};
typedef EyeBall* LPEYEBALL;