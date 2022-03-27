#pragma once
#include"Object.h";
#include"Collision.h"
#include"SkullBullet.h"

#define SKULL_FLY_SPEED 0.05

class Skull : public Object
{
private:
	LPSKULLBULLET bullet = nullptr;
	bool isAttacked = false;
public:
	enum ANIMATIONS
	{
		IDLERIGHT,
		IDLELEFT,
		ATTACKRIGHT,
		ATTACKLEFT,
		DIE,
		_LENGHT
	};

	Skull(int x, int y, int width, int height);
	void Init();
	void Update(DWORD dt, vector<LPOBJECT>* objs);
	void Render();
	void FlyRight();
	void FlyLeft();
	void Attack();

	void DoActionOnCollision(int nx, int ny, Object* obj);
	RECT GetCollisionBox();
	D3DXVECTOR2 GetCollisionBoxCenter();
};
typedef Skull* LPSKULL;