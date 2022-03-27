#pragma once
#include "Object.h"
#include "Collision.h"
#include "Jason2.h"
#include "BossBullet.h"

#define BOSS_PINCER_CHANGE_DIRECTION_TIME 500
#define BOSS_PINCER_MOVE_TIME 4000
#define BOSS_PINCER_MOVE_SPEED 0.1
#define BOSS_DISTANCE_BETWEEN_PINCERS 50
#define BOSS_MOVE_SPEED 0.02
#define BOSS_HP 50
#define BOSS_SHOOT_DELAY_TIME 300


class BossHandNode : public Object
{
public:
	enum STATUSES {
		IDLE
	};

	enum ANIMATIONS {
		NORMAL,
		LOWHP,
		_LENGHT
	};

private:


public:
	BossHandNode();
	void Update(DWORD dt, vector<LPOBJECT>* objs);
	void KeyEvents();
	void DoActionOnCollision(int nx, int ny, LPOBJECT obj);
	void Render();
	void SetCenterPosstion(D3DXVECTOR2 center);
	RECT GetCollisionBox();
	D3DXVECTOR2 GetCollisionBoxCenter();

	~BossHandNode();
};
typedef BossHandNode* LPBOSSHANDNODE;



class BossPincerLeft : public Object
{
public:

	enum ANIMATIONS {
		NORMAL,
		LOWHP,
		_LENGHT
	};

	enum DIRECTIONS {
		UP,
		DOWN,
		LEFT, 
		RIGHT
	};

private:
	int change_direction_time = 0;
	int move_time = 0;
	bool isMoving = false;
	BossPincerLeft* pincer1st;
	RECT zone;

public:
	BossPincerLeft();
	BossPincerLeft(BossPincerLeft* pincer1st);
	void Update(DWORD dt, vector<LPOBJECT>* objs);
	void KeyEvents();
	void DoActionOnCollision(int nx, int ny, LPOBJECT obj);
	void Render();

	RECT GetCollisionBox();
	D3DXVECTOR2 GetCollisionBoxCenter();

	~BossPincerLeft();
};
typedef BossPincerLeft* LPBOSSPINCERLEFT;



class BossPincerRight : public Object
{
public:

	enum ANIMATIONS {
		NORMAL,
		LOWHP,
		_LENGHT
	};

	enum DIRECTIONS {
		UP,
		DOWN,
		LEFT,
		RIGHT
	};

private:
	int change_direction_time = 0;
	int move_time = 0;
	bool isMoving = false;
	BossPincerRight* pincer1st;
	RECT zone;

public:
	BossPincerRight();
	BossPincerRight(BossPincerRight* pincer1st);
	void Update(DWORD dt, vector<LPOBJECT>* objs);
	void KeyEvents();
	void DoActionOnCollision(int nx, int ny, LPOBJECT obj);
	void Render();

	RECT GetCollisionBox();
	D3DXVECTOR2 GetCollisionBoxCenter();

	~BossPincerRight();
};
typedef BossPincerRight* LPBOSSPINCERRIGHT;



class BossHandLeft : public Object
{
public:
	enum STATUSES {
		IDLE
	};

public:
	LPBOSSHANDNODE _node1;
	LPBOSSHANDNODE _node2;
	LPBOSSHANDNODE _node3;
	LPBOSSHANDNODE _node4;
	LPBOSSPINCERLEFT _pincer;
	BossHandLeft* hand1st;

public:
	BossHandLeft();
	BossHandLeft(BossHandLeft* hand1st);
	void Update(DWORD dt, vector<LPOBJECT>* objs);
	void KeyEvents();
	void DoActionOnCollision(int nx, int ny, LPOBJECT obj);
	void Render();

	~BossHandLeft();
};
typedef BossHandLeft* LPBOSSHANDLEFT;



class BossHandRight : public Object
{
public:
	enum STATUSES {
		IDLE
	};

public:
	LPBOSSHANDNODE _node1;
	LPBOSSHANDNODE _node2;
	LPBOSSHANDNODE _node3;
	LPBOSSHANDNODE _node4;
	LPBOSSPINCERRIGHT _pincer;
	BossHandRight* hand1st;

public:
	BossHandRight(); 
	BossHandRight(BossHandRight* hand1st);
	void Update(DWORD dt, vector<LPOBJECT>* objs);
	void KeyEvents();
	void DoActionOnCollision(int nx, int ny, LPOBJECT obj);
	void Render();

	~BossHandRight();
};
typedef BossHandRight* LPBOSSHANDRIGHT;



class BossHead : public Object
{
public:
	enum STATUSES {
		IDLEs
	};

	enum ANIMATIONS {
		IDLE,
		LITLELOWHP,
		LOWHP,
		VERYLOWHP,
		_LENGHT
	};

private:
	RECT zone;

public:
	BossHead();
	void Update(DWORD dt, vector<LPOBJECT>* objs);
	void KeyEvents();
	void DoActionOnCollision(int nx, int ny, LPOBJECT obj);
	void Render();

	RECT GetCollisionBox();
	D3DXVECTOR2 GetCollisionBoxCenter();

	~BossHead();
};
typedef BossHead* LPBOSSHEAD;



class Boss : public Object
{
public:
	
	enum STATUSES {
		IDLE
	};

private:
	static Boss* _instance;
	RECT zone;
	bool isDieing = false;
	int hp = BOSS_HP;
	int died_time = 3000;
	int shoot_delay_time = 0;
	std::vector<LPBOSSBULLET>* bullets;

	LPBOSSHEAD _head;
	LPBOSSHANDLEFT _handleft1;
	LPBOSSHANDLEFT _handleft2;
	LPBOSSHANDRIGHT _handright1;
	LPBOSSHANDRIGHT _handright2;

public:
	Boss();
	void Init();
	void Update(DWORD dt, vector<LPOBJECT>* objs);
	void KeyEvents();
	void DoActionOnCollision(int nx, int ny, LPOBJECT obj);
	void Render();
	void HP(int damage);
	RECT GetCollisionBox();
	D3DXVECTOR2 GetCollisionBoxCenter();
	static Boss* GetInstance();
	~Boss();
};
typedef Boss* LPBOSS;




