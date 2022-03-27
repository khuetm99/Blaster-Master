#pragma once
#include <sstream>
#include <fstream>
#include <string>

#include "Global.h"
#include "Car.h"
#include "Jason1.h"
#include "Map1.h"
#include "Door.h"

class Mission1
{
public:
	LPMAP1 map;
	LPCAR car;
	LPJASON1 jason;
	std::vector<LPDOOR> doors;

	bool isRuning = true;

public:
	Mission1();
	~Mission1();

	void Update(DWORD dt);
	void Render();
	void KeyEvents();
	void SetCameraAnchoToCharacter();
	void SetInRuning(bool isRuning);

	LPMAP1 GetMap();

	bool IsRuning();

};

