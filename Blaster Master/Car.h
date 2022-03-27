#pragma once
#include "Object.h"
#include "CarBody.h"
#include "CarGun.h"
#include "CarHead.h"
#include "CarWheelLeft.h"
#include "CarWheelRight.h"
#include "Collision.h"
#include "CarBullet.h"
#include "Door.h"

#define CAR_HURT_TIME 1000
#define CAR_HP 100

class Car : public Object
{
public:
	enum STATUSES {
		IDLE,
		JUMP,
		DOWN,
		OPENDOOR,
		CLOSEDOOR
	};

private:

	static Car* _instance;

	std::vector<LPCARBULLET> bullets;
	LPD3DXVECTOR2 wheelAnchorPoint;
	LPD3DXVECTOR2 wheelAnchorVelocity;
	int delaytime;
	int hp = CAR_HP;
	long t = 0;
	int hurtime = 0;
	bool isHurt = false;
	float wheelAnchorDistance;
	bool isControlling;
	bool isPhysical;
	bool isInDoor;
	bool isOnBrick;

	LPCARBODY _body;
	LPCARGUN _gun;
	LPCARHEAD _head;
	LPCARWHEELLEFT _wheelleft;
	LPCARWHEELRIGHT _wheellright;

public:
	Car();
	void Init();
	void Update(DWORD dt, vector<LPOBJECT>* objs, vector<LPDOOR>* doors);
	void KeyEvents();
	void PhysicalCalculate(DWORD dt);
	void Car::DoActionOnCollision(int nx, int ny, LPOBJECT obj);
	void Render();
	void HP(int damage);
	void SetIsHurt(bool isHurt);

	bool GettIsHurt();
	void Jump();
	void Down();
	void Idle();
	void OpenDoor();
	void CloseDoor();

	void SetIsControlling(bool isControlling);

	bool IsControlling();

	RECT GetCollisionBox();
	D3DXVECTOR2 GetCollisionBoxCenter();
	static Car* GetInstance();
	
	~Car();
};

typedef Car* LPCAR;

