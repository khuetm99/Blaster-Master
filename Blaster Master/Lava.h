#pragma once
#include"Object.h"
class Lava : public Object
{

public:
	Lava(int x, int y, int width, int height);
	void Render();
	D3DXVECTOR2 GetCollisionBoxCenter();
	RECT GetCollisionBox();
};

