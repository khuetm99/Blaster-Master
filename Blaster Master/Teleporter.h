#pragma once
#include "Object.h"
#include"Collision.h"



#define TELEPORTER_DELAY_TIME 3000

class Teleporter : public Object
{

private:
	D3DXVECTOR2 firstPos;
	int teledelaytime = 0;
public:
	enum ANIMATIONS
	{
		IDLEGRAY,
		IDLEGREEN,
		DIE,
		_LENGHT
	};

	Teleporter(int x, int y, int width, int height);
	void Init();
	void Update(DWORD dt);
	void Render();
	void DoActionOnCollision(int nx, int ny, Object* obj);

	RECT GetCollisionBox();
	D3DXVECTOR2 GetCollisionBoxCenter();
};
typedef Teleporter* LPTELEPORTER;

