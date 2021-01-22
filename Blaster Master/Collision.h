#pragma once
#include"Object.h"
#include <algorithm>
//#include<d3d9.h>

using namespace std;

struct CCollisionEvent
{
	LPOBJECT obj;
	float t, nx, ny;
	CCollisionEvent(float t, float nx, float ny, LPOBJECT obj = NULL) { this->t = t; this->nx = nx; this->ny = ny; this->obj = obj; }
};
typedef CCollisionEvent* LPCOEVENT;

class Colision
{
private:

	LPOBJECT character;
	vector<LPOBJECT>objects;
	vector<LPCOEVENT>coEvents;

	void SweppAABB(float ml, float mt, float mr, float mb,
		float dx, float dy,
		float sl, float st, float sr, float sb,
		float& t, float& nx, float& ny, LPOBJECT& obj);
	LPCOEVENT SweptAABBEx(LPOBJECT obj, DWORD dt);

public:
	Colision() {};
	Colision(LPOBJECT character)
	{
		this->character = character;
	}
	void init(LPOBJECT obj, vector<LPOBJECT> ListObj);//va cham
	void CalcPotentialCollisions(vector<LPOBJECT>* coObjects, vector<LPCOEVENT>& coEvents, DWORD dt);
	void FilterCollision(
		vector<LPCOEVENT>& coEvents,
		vector<LPCOEVENT>& coEventsResult,
		float& min_tx,
		float& min_ty,
		float& nx,
		float& ny);
};
typedef Colision* LPCOLLISION;