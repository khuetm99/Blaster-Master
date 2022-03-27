#pragma once
#include"Object.h";
#include"Collision.h"

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
	void Update(DWORD dt, vector<LPOBJECT>* objs);
	void PhysicalCalculate(DWORD dt);
	void Render();

	void DoActionOnCollision(int nx, int ny, Object* obj);
	RECT GetCollisionBox();
	D3DXVECTOR2 GetCollisionBoxCenter();
};
typedef Orb* LPORB;