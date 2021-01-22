#include "Cannons.h"

Cannons::Cannons(int x, int y, int width, int height) : Object(x,y,width,height)
{
	this->SetTypeObj(TYPEOBJECT::CANNONS);
	this->SetDirection(false, false, false, false);
}
void Cannons::Init()
{
	LPDIRECT3DTEXTURE9 d3dtex = Textures::GetInstance()->GetDirect3DTexture(Textures::TEXTURES::ENEMY);
	LPDIRECT3DTEXTURE9 d3dtex1 = Textures::GetInstance()->GetDirect3DTexture(Textures::TEXTURES::CHARACTERLEFT);

	for (int i = 0; i < ANIMATIONS::_LENGHT; i++)
	{
		switch (i)
		{
		case ANIMATIONS::IDLE:
		{
			Animation* ani = new Animation();
			ani->Add(new Sprite(132, 603, 158, 629, d3dtex), 100);
			this->animations->Add(ani);
			ani->Repeat(true);
			break;
		}
		case ANIMATIONS::ATTACKHORIZONTAL:
		{
			Animation* ani = new Animation();
			ani->Add(new Sprite(162, 603, 184, 629, d3dtex), 100);
			this->animations->Add(ani);
			ani->Repeat(true);
			break;
		}
		case ANIMATIONS::ATTACKVERTICAL:
		{
			Animation* ani = new Animation();
			ani->Add(new Sprite(187, 607, 213, 629, d3dtex), 100);
			this->animations->Add(ani);
			ani->Repeat(true);
			break;
		}
		case ANIMATIONS::DIE: {
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

void Cannons::Update(DWORD dt)
{
	if (animations != NULL)
		animations->Update(dt);
}

void Cannons::PhysicalCalculate(DWORD dt)
{
}

void Cannons::Render()
{
	if (animations != NULL)
		animations->Render(*wPosition);
}
