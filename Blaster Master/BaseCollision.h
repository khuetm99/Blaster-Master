#pragma once
#include"Object.h"
#include <algorithm>

class BaseCollisionEvent
{
public:
	BaseCollisionEvent(LPOBJECT &objA, LPOBJECT &objB, int objA_nx, int objA_ny, double dtime);
	double dtime;
	LPOBJECT objA;
	LPOBJECT objB;
	int objA_nx;
	int objA_ny;
};
typedef BaseCollisionEvent* LPBASECOLLISIONEVENT;


class BaseCollision
{
private:
	double remainderTime;

	void SweppAABB(float ml, float mt, float mr, float mb,float dx, float dy,float sl, float st, float sr, float sb,float& t, float& nx, float& ny, LPOBJECT& objA);
	LPBASECOLLISIONEVENT Calculate(LPOBJECT &A, LPOBJECT &B, double dt);
	LPBASECOLLISIONEVENT GetEvent(std::vector<LPBASECOLLISIONEVENT> events);
	void RunEvent(std::vector<LPOBJECT> objs, LPBASECOLLISIONEVENT event);
public:
	void Run(std::vector<LPOBJECT> objs, DWORD dt);
};
typedef BaseCollision* LPBASECOLLISION;
