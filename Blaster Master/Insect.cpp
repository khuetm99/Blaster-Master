#include "Insect.h"

Insect::Insect(int x, int y, int width, int height) : Object(x, y, width, height)
{
	this->SetTypeObj(TYPEOBJECT::INSECT);
	this->SetDirection(false, false, false, false);
}
void Insect::Init()
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
			ani->Add(new Sprite(132, 530, 150, 548, d3dtex), 100);
			this->animations->Add(ani);
			ani->Repeat(true);
			this->animations->Start(ANIMATIONS::IDLERIGHT);
			break;
		}
		case ANIMATIONS::IDLELEFT:
		{
			Animation* ani = new Animation();
			ani->Add(new Sprite(102, 530, 121, 544, d3dtex), 100);
			this->animations->Add(ani);
			ani->Repeat(true);
			break;
		}
		case ANIMATIONS::FLYRIGHT:
		{
			Animation* ani = new Animation();
			ani->Add(new Sprite(132, 530, 150, 548, d3dtex), 100);
			ani->Add(new Sprite(151, 533, 170, 549, d3dtex), 600);
			this->animations->Add(ani);
			ani->Repeat(true);
			break;
		}
		case ANIMATIONS::FLYLEFT:
		{
			Animation* ani = new Animation();
			ani->Add(new Sprite(102, 530, 121, 544, d3dtex), 100);
			ani->Add(new Sprite(82, 530, 101, 447, d3dtex), 600);
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
void Insect::Update(DWORD dt)
{
	if (animations != NULL)
		animations->Update(dt);
}
void Insect::PhysicalCalculate(DWORD dt)
{
}
void Insect::Render()
{
	if (animations != NULL)
		animations->Render(*wPosition);
}