#pragma once
#include "Object.h"
#include "Collision.h"
#include "Teleporter.h"
#include "EyeBall.h"

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

	enum STATUSES {
		NORMAL,
		DESTROYED
	};

private:
	float x, y;
	float ax, ay;
	int damage = 1;

public:
	Jason2Bullet(int direction, float x, float y);
	void Update(DWORD dt, vector<LPOBJECT>* objs);
	void PhysicalCalculate(DWORD dt);
	void DoActionOnCollision(int nx, int ny, LPOBJECT obj, DWORD dt);
	void Render();

	void FlyUp();
	void FlyDown();
	void FlyRight();
	void FlyLeft();
	void Destroy();

	void SetDamage(int damage);

	int GetDamage();
	RECT GetCollisionBox();
	D3DXVECTOR2 GetCollisionBoxCenter();
};
typedef Jason2Bullet* LPJASON2BULLET;

