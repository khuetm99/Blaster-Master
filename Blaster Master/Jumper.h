#pragma once
#include "Object.h"
#include "Collision.h"


#define JUMPER_SPEED_WALK 0.01
#define JUMPER_SPEED_JUMP_HORIZONTAL 0.03
#define JUMPER_SPEED_JUMP_VERTICAL 0.15
#define JUMPER_TIME_DELAY_JUMP 3000

class Jumper : public Object
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
	int delayjumptime = 0;
public:
	Jumper(int x, int y, int width, int height);
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
typedef Jumper* LPJUMPER;