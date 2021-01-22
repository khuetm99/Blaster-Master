#pragma once
#include"Object.h"
#include "Jason2Bullet.h"
#include "Door.h"

#define JASON2_DELAY_SHOOT_TIME 200

class Jason2 : public Object
{
private:
	int direction;
	int delaytime;
	std::vector<LPJASON2BULLET> bullets;

	bool isInDoor;

public:
	enum DIRECTIONS {
		UP,
		RIGHT,
		LEFT,
		DOWN
	};

	enum ANIMATIONS
	{
		IDLERIGHT,
		IDLELEFT,
		IDLEUP,
		IDLEDOWN,
		WALKRIGHT,
		WALKLEFT,
		WALKUP,
		WALKDOWN,
		DIERIGHT,
		_LENGTH
	};

	enum STATUSES
	{
		STAND,
		HURT,
		DIE
	};

	Jason2(float x, float y);
	void Init();
	void Update(DWORD dt, vector<LPOBJECT>* objs, vector<LPDOOR>* doors);
	void PhysicalCalculate(DWORD dt);
	void Render();
	void KeyEvents();
	void DoActionOnCollision(int nx, int ny, Object* obj);

	RECT GetCollisionBox();
	D3DXVECTOR2 GetCollisionBoxCenter();
};
typedef Jason2* LPJASON2;

