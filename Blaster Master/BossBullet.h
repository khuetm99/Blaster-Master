#pragma once
#include "Object.h"
#include "Collision.h"
#include "Jason2.h"


class BossBullet : public Object
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
	D3DXVECTOR2 target;
	float x, y;
	float ax, ay;
	int damage = 1;

public:
	BossBullet(D3DXVECTOR2 target, float x, float y);
	void Update(DWORD dt);
	void PhysicalCalculate(DWORD dt);
	void DoActionOnCollision(int nx, int ny, float min_tx, float min_ty, LPOBJECT obj, DWORD dt);
	void Render();

	void Destroy();

	void SetDamage(int damage);

	int GetDamage();
	RECT GetCollisionBox();
	D3DXVECTOR2 GetCollisionBoxCenter();
};
typedef BossBullet* LPBOSSBULLET;