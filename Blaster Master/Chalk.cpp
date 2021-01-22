#include "Chalk.h"

Chalk::Chalk(int x, int y, int width, int height) :Object(x, y, width, height)
{
	this->SetTypeObj(TYPEOBJECT::CHALK);
	this->SetDirection(false, false, false, false);
}

void Chalk::Init()
{
	LPDIRECT3DTEXTURE9 d3dtex = Textures::GetInstance()->GetDirect3DTexture(Textures::TEXTURES::TILESET);
	LPDIRECT3DTEXTURE9 d3dtex1 = Textures::GetInstance()->GetDirect3DTexture(Textures::TEXTURES::CHARACTERLEFT);

	for (int i = 0; i < ANIMATIONS::_LENGHT; i++)
	{
		switch (i)
		{
		case ANIMATIONS::IDLE:
		{
			Animation* ani = new Animation();
			ani->Add(new Sprite(121, 1, 137, 17, d3dtex), 100);
			this->animations->Add(ani);
			ani->Repeat(true);
			break;
		}
		case ANIMATIONS::DESTROY: {
			Animation* ani = new Animation();
			ani->Add(new Sprite(140, 101, 147, 109, d3dtex1), 30);
			ani->Add(new Sprite(149, 97, 165, 110, d3dtex1), 30);
			ani->Add(new Sprite(166, 97, 182, 113, d3dtex1), 30);
			ani->Add(new Sprite(183, 93, 207, 117, d3dtex1), 100);
			this->animations->Add(ani);
			break;
		}
		}
	}
}

void Chalk::Update(DWORD dt)
{
	if (animations != NULL)
		animations->Update(dt);
}

void Chalk::Render()
{
}
