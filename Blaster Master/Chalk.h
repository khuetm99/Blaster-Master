#pragma once
#include "Object.h"
class Chalk : public Object
{
private:
	
public:
	enum ANIMATIONS
	{
		IDLE,
		DESTROY,
		_LENGHT
	};
	Chalk(int x, int y, int width, int height);
	void Init();
	void Update(DWORD dt);
	void Render();
};
typedef Chalk* LPCHALK;

