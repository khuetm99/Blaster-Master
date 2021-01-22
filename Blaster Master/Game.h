#pragma once
#include "Global.h"
#include "Mission1.h"
#include "Mission2.h"

using namespace std;

#define BACKGROUND_COLOR D3DCOLOR_XRGB(0, 0, 0)

class Game
{
private:

	static Game* _instance;

	Mission1* mission1;
	Mission2* mission2;
	
public:
	static Game* GetInstance();
	void Init(HWND hWnd);
	void LoadResource();
	void KeyEvents();
	void Run();
	void Update(DWORD dt);
	void Render();
	void End();

	~Game();
};

