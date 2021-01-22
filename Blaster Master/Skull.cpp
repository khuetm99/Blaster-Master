#include "Skull.h"

Skull::Skull(int x, int y, int width, int height) : Object(x, y, width, height)
{
	this->SetTypeObj(TYPEOBJECT::SKULL);
	this->SetDirection(false, false, false, false);
}
void Skull::Init()
{
	LPDIRECT3DTEXTURE9 d3dtex = Textures::GetInstance()->GetDirect3DTexture(Textures::TEXTURES::ENEMY);
	LPDIRECT3DTEXTURE9 d3dtex1 = Textures::GetInstance()->GetDirect3DTexture(Textures::TEXTURES::CHARACTERLEFT);

	for (int i = 0; i < ANIMATIONS::_LENGHT; i++)
	{
		switch (i)
		{
		case ANIMATIONS::IDLERIGHT:
		{
			Animation* ani = new Animation();
			ani->Add(new Sprite(194, 530, 212, 548, d3dtex), 100);
			this->animations->Add(ani);
			ani->Repeat(true);
			break;
		}
		case ANIMATIONS::IDLELEFT:
		{
			Animation* ani = new Animation();
			ani->Add(new Sprite(42, 530, 60, 548, d3dtex), 100);
			this->animations->Add(ani);
			ani->Repeat(true);
			break;
		}
		case ANIMATIONS::ATTACKRIGHT:
		{
			Animation* ani = new Animation();
			ani->Add(new Sprite(174, 527, 192, 548, d3dtex), 300);
			ani->Add(new Sprite(194, 530, 212, 548, d3dtex), 100);
			this->animations->Add(ani);
			ani->Repeat(true);
			break;
		}
		case ANIMATIONS::ATTACKLEFT:
		{
			Animation* ani = new Animation();
			ani->Add(new Sprite(62, 527, 80, 548, d3dtex), 300);
			ani->Add(new Sprite(42, 530, 60, 548, d3dtex), 100);
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
void Skull::Update(DWORD dt)
{
	if (animations != NULL)
		animations->Update(dt);
}
void Skull::PhysicalCalculate(DWORD dt)
{
}
void Skull::Render()
{
	if (animations != NULL)
		animations->Render(*wPosition);
}
