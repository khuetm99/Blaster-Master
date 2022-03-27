#pragma once
#include"Object.h";
#include"Collision.h"

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
	void Update(DWORD dt, vector<LPOBJECT>* objs);
	void PhysicalCalculate(DWORD dt);
	void Render();

	void DoActionOnCollision(int nx, int ny, Object* obj);
	RECT GetCollisionBox();
	D3DXVECTOR2 GetCollisionBoxCenter();
	~Domes();
};
typedef Domes* LPDOMES;

