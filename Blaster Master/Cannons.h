#pragma once
#include "Object.h"
#include "Collision.h"

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
	void Update(DWORD dt, vector<LPOBJECT>* objs);
	void PhysicalCalculate(DWORD dt);
	void Render();

	void DoActionOnCollision(int nx, int ny, Object* obj);
	RECT GetCollisionBox();
	D3DXVECTOR2 GetCollisionBoxCenter();
};
typedef Cannons* LPCANNONS;