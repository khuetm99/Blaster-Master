#pragma once
#include "Object.h"
#include "Collision.h"

#define WORM_SPEED 0.03

class Worm : public Object
{
public:
	enum ANIMATIONS
	{
		IDLERIGHT,
		IDLELEFT,
		WALKRIGHT,
		WALKLEFT,
		DIE,
		_LENGHT
	};

	enum STATUSES {
		WALK,
		JUMP,
		DESTROY
	};

private:
	bool isInLava = false;

public:
	Worm(int x, int y, int width, int height);
	void Init();
	void Update(DWORD dt, vector<LPOBJECT>* objs);
	void PhysicalCalculate(DWORD dt);
	void Render();

	void DoActionOnCollision(int nx, int ny, Object* obj);
	void WalkRight();
	void WalkLeft();
	void Jump();
	void Die();
	
	RECT GetCollisionBox();
	D3DXVECTOR2 GetCollisionBoxCenter();
};
typedef Worm* LPWORM;