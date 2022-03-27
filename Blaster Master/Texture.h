#pragma once
#include <d3dx9.h>
#include <unordered_map>



class Texture {
private:
	LPDIRECT3DTEXTURE9 texture;
public:
	Texture(LPCWSTR filePath, D3DCOLOR transparentColor);
	LPDIRECT3DTEXTURE9 LPDIRECT3DTEXTURE();
	~Texture();
};

typedef Texture* LPTEXTURE;

class Textures {
private:
	static Textures* _instance;
	std::vector<LPDIRECT3DTEXTURE9> d3dxtextures;
public :
	enum TEXTURES {
		TILESET,
		MAP,
		MAP2,
		ENEMY,
		CHARACTERLEFT,
		CHARACTERRIGHT,
		BOSS,
		ITEM,
		_LENGHT
	};


public:
	Textures();
	void Init();
	LPDIRECT3DTEXTURE9 GetDirect3DTexture(int id);
	static Textures* GetInstance();
};
typedef Texture* LPTEXTURES;