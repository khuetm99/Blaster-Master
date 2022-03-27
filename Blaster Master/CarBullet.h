#pragma once
#include "Object.h"
#include "Collision.h"

class CarBullet : public Object
{
public:
	enum ANIMATIONS
	{
		FlYRIGHT,
		FLYLEFT,
		FLYUP,
		DESTROY,
		_LENGHT
	};

	enum STATUSES {
		FLY,
		DESTROYED,
	};

public:
	CarBullet(float x, float y);
	void Update(DWORD dt, vector<LPOBJECT>* objs);
	void DoActionOnCollision(int nx, int ny, LPOBJECT obj);
	void Render();

	void FlyRight();
	void FlyLeft();
	void FlyUp();
	void Destroy();

	RECT GetCollisionBox();
	D3DXVECTOR2 GetCollisionBoxCenter();
};
typedef CarBullet* LPCARBULLET;
