#pragma once
#include "Object.h"
#include "Collision.h"

class Jason2Bullet : public Object
{
public:
	enum DIRECTIONS {
		UP,
		DOWN,
		LEFT,
		RIGHT
	};

	enum ANIMATIONS
	{
		FLY,
		DESTROY,
		_lenght
	};

private:
	float x, y;
	float ax, ay;

public:
	Jason2Bullet(int direction, float x, float y);
	void Update(DWORD dt, vector<LPOBJECT>* objs);
	void PhysicalCalculate(DWORD dt);
	void DoActionOnCollision(int nx, int ny, LPOBJECT obj);
	void Render();

	void FlyUp();
	void FlyDown();
	void FlyRight();
	void FlyLeft();
	void Destroy();

	RECT GetCollisionBox();
	D3DXVECTOR2 GetCollisionBoxCenter();
};
typedef Jason2Bullet* LPJASON2BULLET;

