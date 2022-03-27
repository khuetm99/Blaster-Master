#pragma once
#include "Object.h"
#include "Collision.h"

class Door : public Object
{
public:
	enum TYPES {
		LEFT,
		RIGHT
	};

	enum ANIMATIONS
	{
		IDLE,
		_LENGHT
	};

	enum STATUSES {
		FLY,
		DESTROYED,
	};

private:
	int map, x, y, width, height;

public:
	Door(int map, int x, int y, int width, int height);
	void Update(DWORD dt, vector<LPOBJECT>* objs);
	void DoActionOnCollision(int nx, int ny, LPOBJECT obj);
	void Render();

	RECT GetCollisionBox();
	D3DXVECTOR2 GetCollisionBoxCenter();
};
typedef Door* LPDOOR;

