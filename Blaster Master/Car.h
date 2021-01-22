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
	std::vector<LPCARBULLET> bullets;

	LPD3DXVECTOR2 wheelAnchorPoint;
	LPD3DXVECTOR2 wheelAnchorVelocity;
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
	Car(float x, float y);
	void Update(DWORD dt, vector<LPOBJECT>* objs, vector<LPDOOR>* doors);
	void KeyEvents();
	void PhysicalCalculate(DWORD dt);
	void Car::DoActionOnCollision(int nx, int ny, LPOBJECT obj);
	void Render();

	void Jump();
	void Down();
	void Idle();
	void OpenDoor();
	void CloseDoor();

	void SetIsControlling(bool isControlling);

	bool IsControlling();

	RECT GetCollisionBox();
	D3DXVECTOR2 GetCollisionBoxCenter();
	
	
	~Car();
};

typedef Car* LPCAR;

