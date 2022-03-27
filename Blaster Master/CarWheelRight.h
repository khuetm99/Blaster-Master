#pragma once
#include "Object.h"
class CarWheelRight :public Object
{
public:
	enum ANIMATIONS {
		WALK,
		_LENGHT
	};

	enum STATUSES {
		IDLE
	};

private:
	LPD3DXVECTOR2 relativePosition;
	LPD3DXVECTOR2 anchorPoint;
	bool isShrinking;

public:
	CarWheelRight(LPD3DXVECTOR2 anchor);
	void Update(DWORD dt);
	void Render(float opacity = 1.0f);

	void SetRelativePosition(float x, float y);
	void Idle();
	void WalkRight();
	void WalkLeft();
	void SetIsShrinking(bool shrinking);

	bool IsShrinking();

	~CarWheelRight();
};
typedef CarWheelRight* LPCARWHEELRIGHT;


