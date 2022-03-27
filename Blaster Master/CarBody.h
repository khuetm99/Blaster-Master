#pragma once
#include "Object.h"

class CarBody : public Object
{
public:
	enum ANIMATIONS {
		IDLERIGHT,
		IDLELEFT,
		UPRIGHT,
		UPLEFT,
		DOWNRIGHT,
		DOWNLEFT,
		ROTATERIGHT,
		ROTATELEFT,
		_LENGHT
	};

	enum STATUSES {
		IDLE
	};

private:
	LPD3DXVECTOR2 relativePosition;
	LPD3DXVECTOR2 anchorPoint;
	bool isUndulating;

public:
	CarBody(LPD3DXVECTOR2 anchor);
	void Update(DWORD dt);
	void Render(float opacity = 1.0f);
	void Physical(DWORD dt);
	void SetRelativePosition(float x, float y);
	void SetIsUndulating(bool isUndulating);
	void RightToLeft();
	void LeftToRight();
	void UpRight();
	void UpLeft();
	void IdleRight();
	void IdleLeft();
	void DownRight();
	void DownLeft();
	void RotateRight();
	void RotateLeft();

	D3DXVECTOR2 GetRelativePosition();
	
	~CarBody();
};

typedef CarBody* LPCARBODY;

