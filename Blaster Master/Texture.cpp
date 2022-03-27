#include "Global.h"
#include "Texture.h"
#include "Debug.h"


Texture::Texture(LPCWSTR filePath, D3DCOLOR transparentColor)
{
	if (Global::GetInstance()->_D3DDV != nullptr) {
		D3DXIMAGE_INFO info;
		HRESULT result = D3DXGetImageInfoFromFile(filePath, &info);
		if (result != D3D_OK)
		{
			return;
		}

		result = D3DXCreateTextureFromFileEx(
			Global::GetInstance()->_D3DDV,								// Pointer to Direct3D device object
			filePath,							// Path to the image to load
			info.Width,							// Texture width
			info.Height,						// Texture height
			1,
			D3DUSAGE_DYNAMIC,
			D3DFMT_UNKNOWN,
			D3DPOOL_DEFAULT,
			D3DX_DEFAULT,
			D3DX_DEFAULT,
			transparentColor,
			&info,
			NULL,
			&texture);								// Created texture pointer

		if (result != D3D_OK)
		{
			OutputDebugString(L"[ERROR] CreateTextureFromFile failed\n");
			return;
		}
	}
}

LPDIRECT3DTEXTURE9 Texture::LPDIRECT3DTEXTURE()
{
	return texture;
}

Texture::~Texture()
{
}


Textures* Textures::_instance = new Textures();

Textures::Textures()
{
}

void Textures::Init()
{
	for (int i = 0; i < TEXTURES::_LENGHT; i++)
	{
		if (i == TEXTURES::TILESET) {
			LPTEXTURE tex = new Texture(L"textures/Area2TileSet.png", D3DCOLOR_XRGB(0, 57, 115));
			this->d3dxtextures.push_back(tex->LPDIRECT3DTEXTURE());
		}
		else 
		if (i == TEXTURES::MAP){
			LPTEXTURE tex = new Texture(L"textures/area2.png", D3DCOLOR_XRGB(0, 57, 115));
			this->d3dxtextures.push_back(tex->LPDIRECT3DTEXTURE());
		}
		else
		if (i == TEXTURES::MAP2) {
			LPTEXTURE tex = new Texture(L"textures/map2.png", D3DCOLOR_XRGB(0, 57, 115));
			this->d3dxtextures.push_back(tex->LPDIRECT3DTEXTURE());
		}
		else
		if (i == TEXTURES::ENEMY) {
			LPTEXTURE tex = new Texture(L"textures/Enemies.png", D3DCOLOR_XRGB(0, 38, 255));
			this->d3dxtextures.push_back(tex->LPDIRECT3DTEXTURE());
		}
		else 
		if (i == TEXTURES::CHARACTERLEFT){
			LPTEXTURE tex = new Texture(L"textures/BlasterMaster.png", D3DCOLOR_XRGB(0, 57, 115));
			this->d3dxtextures.push_back(tex->LPDIRECT3DTEXTURE());
		}
		else 
		if (i == TEXTURES::CHARACTERRIGHT){
			LPTEXTURE tex = new Texture(L"textures/BlasterMaster1.png", D3DCOLOR_XRGB(0, 57, 115));
			this->d3dxtextures.push_back(tex->LPDIRECT3DTEXTURE());
		}
		else
		if (i == TEXTURES::BOSS){
			LPTEXTURE tex = new Texture(L"textures/boss.png", D3DCOLOR_XRGB(0, 0, 0));
			this->d3dxtextures.push_back(tex->LPDIRECT3DTEXTURE());
		}
		else
		if (i == TEXTURES::ITEM){
			LPTEXTURE tex = new Texture(L"textures/items.png", D3DCOLOR_XRGB(0, 0, 0));
			this->d3dxtextures.push_back(tex->LPDIRECT3DTEXTURE());
		}
	}

	int n = d3dxtextures.size();
}

LPDIRECT3DTEXTURE9 Textures::GetDirect3DTexture(int id)
{
	return d3dxtextures.at(id);
}

Textures* Textures::GetInstance()
{
	if (_instance == NULL) _instance = new Textures();
	return _instance;
}


