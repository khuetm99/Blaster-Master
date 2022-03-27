#pragma once
#include "Object.h"
#include"Collision.h"


#define EYEBALL_DELAY_TIME 3000

class EyeBall : public Object
{
private:
	D3DXVECTOR2 firstPos;
	int teledelaytime = 0;
public:
	enum ANIMATIONS
	{
		IDLE,
		OPENEYERIGHT,
		OPENEYELEFT,
		ROLLEYE,
		DIE,
		_LENGHT
	};

	EyeBall(int x, int y, int width, int height);
	void Init();
	void Update(DWORD dt);
	void PhysicalCalculate(DWORD dt);
	void Render();

	void DoActionOnCollision(int nx, int ny, Object* obj);
	RECT GetCollisionBox();
	D3DXVECTOR2 GetCollisionBoxCenter();
	~EyeBall();
};
typedef EyeBall* LPEYEBALL;