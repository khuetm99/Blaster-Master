#include <fstream>
#include <iostream>
#include "TileSet2.h"
#include "Brick.h"
#include "Teleporter.h"
#include "EyeBall.h"

#define Cell_Size 64
#define Cell_Count_X 32
#define Cell_Count_Y 32
using namespace std;

class Cell2 {
private:
	vector<LPOBJECT>objects;
public:
	void AddObject(LPOBJECT obj);
	vector<LPOBJECT>GetObjects() { return this->objects; }
};
typedef Cell2* LPCELL2;



class Map2
{
private:
	LPTILE2** tiles;
	TileSet2* tileset;

	LPCELL2** cells;

	D3DXVECTOR2 size;
public:
	Map2();
	void LoadMap();
	D3DXVECTOR2 Size();
	RECT Border();
	vector<LPOBJECT> GetObjectsInCamera();
	vector<LPTILE2> GetTilesInCamera();
};
typedef Map2* LPMAP2;
