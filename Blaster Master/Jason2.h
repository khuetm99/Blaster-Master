#pragma once
#include"Object.h"
#include "Jason2Bullet.h"
#include "Door.h"

#define JASON2_DELAY_SHOOT_TIME 200
#define JASON2_HURT_TIME 1000

class Jason2 : public Object
{
private:
	static Jason2* _instance;
	int direction;
	int delaytime;
	std::vector<LPJASON2BULLET> bullets;
	int hp = 100;
	long t = 0;
	int hurtime = 0;
	bool isHurt = false;
	bool isInDoor = false;
	bool isPassMission = false;
	bool isFightingWithBoss = false;

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

	Jason2();
	void Init();
	void Update(DWORD dt, vector<LPOBJECT>* objs, vector<LPDOOR>* doors);
	void PhysicalCalculate(DWORD dt);
	void Render();
	void KeyEvents();
	void DoActionOnCollision(int nx, int ny, Object* obj);
	void GoToBoss();
	void HP(int damage);
	void SetIsHurt(bool isHurt);
	void SetIsPassMission(bool isPass);
	void SetIsFightingWithBoss(bool isfighting);

	bool GetIsPassMission();
	bool GettIsHurt();
	std::vector<LPOBJECT>* GetListObjectBullets();
	bool GetIsFightingWithBoss();
	RECT GetCollisionBox();
	D3DXVECTOR2 GetCollisionBoxCenter();
	static Jason2* GetInstance();
};
typedef Jason2* LPJASON2;

