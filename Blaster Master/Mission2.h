#include <sstream>
#include <fstream>
#include <string>

#include "Global.h"
#include "Map2.h"
#include "Jason2.h"
#include "Door.h"
#include "Boss.h"

class Mission2
{
public:
	LPMAP2 map;
	LPJASON2 jason;
	LPBOSS boss;
	std::vector<LPDOOR> doors;

	bool isRuning = true;

public:
	Mission2();
	~Mission2();

	void Update(DWORD dt);
	void Render();
	void KeyEvents();
	void SetCameraAnchoToCharacter();
	void SetInRuning(bool isRuning);

	LPMAP2 GetMap();

	bool IsRuning();
};

