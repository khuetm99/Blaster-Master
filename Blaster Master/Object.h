#pragma once
#include <math.h>
#include <vector>

#include "Animation.h"
#include "Debug.h"
#include "Texture.h"
#include "Global.h"


using namespace std;



class Object
{
public:
	enum POSITION
	{
		LEFT,
		TOP,
		RIGHT,
		BOTTOM,
		CENTER
	};

protected:
	LPD3DXVECTOR2 wAcceleration;
	LPD3DXVECTOR2 wVelocity;
	LPD3DXVECTOR2 wPosition;
	LPD3DXVECTOR2 move;
	D3DXVECTOR2 centerPostion;
	D3DXVECTOR2 bottomPostion;
	D3DXVECTOR2 topPostion;
	D3DXVECTOR2 leftPostion;
	D3DXVECTOR2 rightPostion;
	double width, height;
	double friction;
	LPANIMATIONS animations;
	double t;
	int status;
	int direction;
	int posType;
	int objType;
	LPTEXTURE tex;
	bool isCollision = false;
	bool direction_l = false;
	bool direction_t = false;
	bool direction_r = false;
	bool direction_b = false;
	bool isExist;
	bool isImpacted_X = false;
	bool isImpacted_Y = false;

public:
	enum TYPEOBJECT {
		BRICK = 1,
		CHALK, //gạch phá dc
		LAVA, //dung nham ,chông
		DOOR, // cửa
		FLOATER,
		DOMES,
		JUMPER,
		INSECT,
		ORB,
		WORM,
		SKULL,
		CANNONS,
		EYEBALL,
		TELEPORTER,
		CAR,
		JASON1,
		JASON2,
		BOSS
	};
	Object();
	Object(float x, float y, float width, float height);

	void SetPostion(float x, float y);
	void SetVelocity(D3DXVECTOR2 velocity);
	void SetAcceleration(D3DXVECTOR2 acceleration);
	void SetCenterPostion(D3DXVECTOR2 center);
	void SetBottomPostion(D3DXVECTOR2 bottom);
	void SetTopPostion(D3DXVECTOR2 top);
	void SetLeftPostion(D3DXVECTOR2 left);
	void SetRightPostion(D3DXVECTOR2 right);
	virtual void SetTypeObj(int type) { this->objType = type; }
	virtual int GetTypeObj() { return this->objType; }

	D3DXVECTOR2 GetVelocity();
	D3DXVECTOR2 GetAcceleration();
	D3DXVECTOR2 GetCenterPostion();
	D3DXVECTOR2 GetBottomPostion();
	D3DXVECTOR2 GetTopPostion();
	D3DXVECTOR2 GetLeftPostion();
	D3DXVECTOR2 GetRightPostion();
	LPD3DXVECTOR2 GetMove();
	LPD3DXVECTOR2 GetPosition();
	int GetDirection();

	virtual double GetWidth();
	virtual double GetHeight();
	virtual RECT GetCollisionBox();
	virtual RECT GetHitBox();
	virtual int GetStatus();
	virtual bool IsExist();
	virtual void SetExist(bool ex) { this->isExist = ex; }
	virtual LPANIMATIONS GetAnimations();

	virtual void Init();
	virtual void PhysicalCalculate(DWORD dt);
	virtual void Update(DWORD dt);
	virtual void Update(DWORD dt, vector<Object*>* objs);
	virtual void Render();

	virtual void DoActionOnCollision(int nx, int ny, Object* obj);

	virtual void SetisCo(bool check) {
		this->isCollision = check;
	}
	virtual bool GetIsCo()
	{
		return isCollision;
	}

	virtual bool GetDirection_l() { return direction_l; }
	virtual bool GetDirection_t() { return direction_t; }
	virtual bool GetDirection_r() { return direction_r; }
	virtual bool GetDirection_b() { return direction_b; }
	virtual void SetDirection(bool left, bool top, bool right, bool bottom) { direction_l = left; direction_t = top; direction_r = right; direction_b = bottom; }
};

typedef Object* LPOBJECT;
