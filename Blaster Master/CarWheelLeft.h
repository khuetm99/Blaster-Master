#pragma once
#include "Object.h"
class CarWheelLeft : public Object
{
public:
	enum ANIMATIONS {
		WALK,
		_LENGHT
	};

private:
	LPD3DXVECTOR2 relativePosition;
	LPD3DXVECTOR2 anchorPoint;
	bool isShrinking;

public:
	CarWheelLeft(LPD3DXVECTOR2 anchor);
	void Update(DWORD dt);
	void Render(float opacity = 1.0f);

	void SetRelativePosition(float x, float y);
	void Idle();
	void WalkRight();
	void WalkLeft();
	void SetIsShrinking(bool shrinking);
	bool IsShrinking();

	~CarWheelLeft();
};
typedef CarWheelLeft* LPCARWHEELLEFT;

