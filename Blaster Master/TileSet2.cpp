#include "TileSet2.h"



TileSet2::TileSet2()
{
	//new text ture 
	LPCWSTR path = L"textures/Area2OverworldTileSet.png";
	Texture* texture = new Texture(path, D3DCOLOR_XRGB(0, 0, 0));
	this->row = (titeset_hight + 1) / (tile_size+1);
	this->colum = (tileset_wight + 1) / (tile_size+1);
	int index = 1;
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < colum; j++)
		{
			int left = j * (tile_size + 1);
			int top = i * (tile_size + 1);
			int right = left + tile_size;
			int bottom = top + tile_size;
			LPSPRITE tile = new Sprite(left, top, right, bottom, texture->LPDIRECT3DTEXTURE());
			tileset[index] = tile;
			index++;
		}
	}
}

LPSPRITE TileSet2::GetTile(int id)
{
	if (tileset.size() > 0 && id > 0)
		return tileset.at(id);
	else
	{
		return nullptr;
	}
}


Tile2::Tile2(LPSPRITE sprite, D3DXVECTOR2 position, D3DXVECTOR2 size)
{
	this->sprite = sprite;
	this->position = position;
	this->size = size;
}

void Tile2::Render()
{
	if (this->sprite != nullptr) {
		sprite->Draw(this->position);
	}
}

