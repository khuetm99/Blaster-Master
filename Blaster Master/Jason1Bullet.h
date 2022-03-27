#pragma once
#include "Object.h"
#include "Collision.h"
class Jason1Bullet : public Object
{
public:
	enum ANIMATIONS
	{
		FlYRIGHT,
		FLYLEFT,
		DESTROY,
		_lenght
	};

	enum STATUSES {
		FLY,
		DESTROYED,
	};

public:
	Jason1Bullet(float x, float y);
	void Update(DWORD dt, vector<LPOBJECT>* objs);
	void PhysicalCalculate(DWORD dt);
	void DoActionOnCollision(int nx, int ny, LPOBJECT obj);
	void Render();

	void FlyRight();
	void FlyLeft();
	void Destroy();

	RECT GetCollisionBox();
	D3DXVECTOR2 GetCollisionBoxCenter();
};
typedef Jason1Bullet* LPJASON1BULLET;