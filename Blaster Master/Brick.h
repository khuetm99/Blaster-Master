#pragma once
#include"Object.h"

class Brick : public Object
{
private:

public:
	Brick(int x, int y, int width, int height);

	void Render();
};

