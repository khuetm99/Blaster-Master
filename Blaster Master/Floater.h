#pragma once
#include"Object.h";
#include"Collision.h"

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
	void Update(DWORD dt, vector<LPOBJECT>* objs);
	void PhysicalCalculate(DWORD dt);
	void Render();

	void DoActionOnCollision(int nx, int ny, Object* obj);
	RECT GetCollisionBox();
	D3DXVECTOR2 GetCollisionBoxCenter();
};
typedef Floater* LPFLOATER;

