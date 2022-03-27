#pragma once
#include "Object.h"
#include "Car.h"

#define SKULLBULLET_HORIZONAL_SPEED 0.02

class SkullBullet : public Object
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
	SkullBullet(int direction, float x, float y);
	void Update(DWORD dt, vector<LPOBJECT>* objs);
	void PhysicalCalculate(DWORD dt);
	void DoActionOnCollision(int nx, int ny, float min_tx, float min_ty, LPOBJECT obj, DWORD dt);
	void Render();

	void Destroy();

	void SetDamage(int damage);

	int GetDamage();
	RECT GetCollisionBox();
	D3DXVECTOR2 GetCollisionBoxCenter();
};
typedef SkullBullet* LPSKULLBULLET;