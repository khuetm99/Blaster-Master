#pragma once
#include "Object.h"
#include<unordered_map>

using namespace std;

#define tile_size 16
#define tileset_wight 218
#define titeset_hight 258



class Tile {
private:
	D3DXVECTOR2 size;
	LPSPRITE sprite;
	D3DXVECTOR2 position;
public:
	Tile(LPSPRITE sprite, D3DXVECTOR2 position, D3DXVECTOR2 size);
	void Render();
};
typedef Tile* LPTILE;


class TileSet1
{
private:
	unordered_map<int, LPSPRITE> tileset;
	int row, colum;
	int width, height;
public:
	TileSet1();
	LPSPRITE GetTile(int id);
};




