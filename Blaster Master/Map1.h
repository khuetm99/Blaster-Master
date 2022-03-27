#include<fstream>
#include<iostream>
#include"TileSet1.h"
#include"Brick.h"
#include "Worm.h"
#include "Lava.h"
#include "Jumper.h"
#include "Insect.h"
#include "Skull.h"

#define Cell_Size 64
#define Cell_Count_X 32
#define Cell_Count_Y 32

using namespace std;


class Cell {
private:
	vector<LPOBJECT>objects;
public:
	void AddObject(LPOBJECT obj);
	vector<LPOBJECT>GetObjects() { return this->objects; }
};
typedef Cell* LPCELL;


class Map1
{
private:
	LPTILE** tiles; // ds cac title
	LPCELL** cells;
	 
	TileSet1* tileset;

	D3DXVECTOR2 size;

public:
	Map1();
	void LoadMap();
	D3DXVECTOR2 Size();
	RECT Border();
	vector<LPOBJECT> GetObjectsInCamera();
	vector<LPTILE> GetTilesInCamera();
};
typedef Map1* LPMAP1;


