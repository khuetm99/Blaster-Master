#pragma once
#include "Object.h"
class CarGun : public Object
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
		DOWN,
		UP,
		ROTATE
	};

private:
	LPD3DXVECTOR2 relativePosition;
	LPD3DXVECTOR2 anchorPoint;

public:
	CarGun(LPD3DXVECTOR2 anchor);

	void Update(DWORD dt);
	void Render(float opacity = 1.0f);
	void SetRelativePosition(float x, float y);
	void RightToLeft();
	void LeftToRight();
	void UpRight();
	void UpLeft();
	void DownRight();
	void DownLeft();
	void RotateRight();
	void RotateLeft();
	~CarGun();
};
typedef CarGun* LPCARGUN;

