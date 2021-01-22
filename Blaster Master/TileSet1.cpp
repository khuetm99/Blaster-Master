#include "TileSet1.h"



TileSet1::TileSet1()
{
	//new text ture 
	/*LPCWSTR path = L"textures/Area2TileSet.png";
	Texture *texture = new Texture(path, D3DCOLOR_XRGB(0, 0, 0));*/

	LPDIRECT3DTEXTURE9 d3dtex = Textures::GetInstance()->GetDirect3DTexture(Textures::TEXTURES::TILESET);

	this->row = (titeset_hight+2) / (tile_size + 4);
	this->colum = (tileset_wight+2) / (tile_size + 4);
	int index = 1;
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < colum; j++)
		{
			int left = j* (tile_size+4)+1;
			int top = i* (tile_size+4)+1;
			int right = left + tile_size;
			int bottom = top + tile_size;
			LPSPRITE tile = new Sprite(left, top, right, bottom, d3dtex);
			tileset[index] = tile;
			index++;
		}
	}
}

LPSPRITE TileSet1::GetTile(int id)
{
	if (tileset.size() > 0 && id > 0)
		return tileset.at(id);
	else
	{
		return nullptr;
	}
}


Tile::Tile(LPSPRITE sprite, D3DXVECTOR2 position, D3DXVECTOR2 size)
{
	this->sprite = sprite;
	this->position = position;
	this->size = size;
}

void Tile::Render()
{
	if (this->sprite != nullptr) {
		sprite->Draw(this->position);
	}
}


