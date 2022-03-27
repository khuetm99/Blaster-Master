#pragma once
#include "Collision.h"
#include "Jason1Bullet.h" 
#include "Door.h"

#define JASON_BULLET_COUNT_ONE_TIME 40
#define JASON_SHOOT_TIME 300


class Jason1 : public Object
{
private:
	bool isControlling;
	bool isPhysical;
	bool isPassMission = false;

	std::vector<LPJASON1BULLET> bullets;

public:
	enum ANIMATIONS
	{
		IDLERIGHT,
		IDLELEFT,
		WALKRIGHT,
		WALKLEFT,
		CRAWLRIGHT,
		CRAWLLEFT,
		JUMPRIGHT,
		JUMPLEFT,
		DIERIGHT,
		DIELEFT,
		JUMPOUTCARRIGHT,
		JUMPOUTCARLEFT,
		JUMPINCARRIGHT,
		JUMPINCARLEFT,
		_LENGHT
	};

	enum STATUSES
	{
		STAND,
		JUMP,
		DOWN,
		CRAWL,
		INTOCAR,
		DIE
	};

	Jason1(float x, float y);
	void Update(DWORD dt, vector<LPOBJECT>* objs, vector<LPDOOR>* doors);
	void PhysicalCalculate(DWORD dt);
	void Render();
	void KeyEvents();
	void IntoCar(D3DXVECTOR2 center);
	void OutCar(D3DXVECTOR2 center, int direction);

	void DoActionOnCollision(int nx, int ny, Object* obj);

	bool IsControlling();

	void SetIsControlling(bool isControlling);
	void SetIsPassMission(bool isPass);

	bool GetIsPassMission();
	RECT GetCollisionBox();
	D3DXVECTOR2 GetCollisionBoxCenter();



};
typedef Jason1* LPJASON1;

