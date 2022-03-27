#pragma once
#include"Object.h";
#include"Collision.h"

#define INSECT_FLY_SPEED 0.05
#define INSECT_DELAY_TIME 2000

class Insect : public Object
{
private: 
	int delaytime = 0;
public:
	enum ANIMATIONS
	{
		IDLERIGHT,
		IDLELEFT,
		FLYRIGHT,
		FLYLEFT,
		DIE,
		_LENGHT
	};

	Insect(int x, int y, int width, int height);
	void Init();
	void Update(DWORD dt, vector<LPOBJECT>* objs);
	void PhysicalCalculate(DWORD dt);
	void Render();
	void FlyRight();
	void FlyLeft();

	void DoActionOnCollision(int nx, int ny, Object* obj);
	RECT GetCollisionBox();
	D3DXVECTOR2 GetCollisionBoxCenter();
	~Insect();
};
typedef Insect* LPINSECT;

