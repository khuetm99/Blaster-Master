#pragma once
#include "Object.h"
#include<unordered_map>

using namespace std;

#define tile_size 16
#define tileset_wight 203
#define titeset_hight 815



class Tile2 {
private:
	D3DXVECTOR2 size;
	LPSPRITE sprite;
	D3DXVECTOR2 position;
public:
	Tile2(LPSPRITE sprite, D3DXVECTOR2 position, D3DXVECTOR2 size);
	void Render();
};
typedef Tile2* LPTILE2;


class TileSet2
{
private:
	unordered_map<int, LPSPRITE> tileset;
	int row, colum;
	int width, height;
public:
	TileSet2();
	LPSPRITE GetTile(int id);
};




