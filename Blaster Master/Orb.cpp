#include "Orb.h"

Orb::Orb(int x, int y, int width, int height) : Object(x, y, width, height)
{
	this->SetTypeObj(TYPEOBJECT::ORB);
	this->SetDirection(false, false, false, false);
}
void Orb::Init()
{
	LPDIRECT3DTEXTURE9 d3dtex = Textures::GetInstance()->GetDirect3DTexture(Textures::TEXTURES::ENEMY);
	LPDIRECT3DTEXTURE9 d3dtex1 = Textures::GetInstance()->GetDirect3DTexture(Textures::TEXTURES::CHARACTERLEFT);

	for (int i = 0; i < ANIMATIONS::_LENGHT; i++)
	{
		switch (i)
		{
		case ANIMATIONS::TURN:
		{
			Animation* ani = new Animation();
			ani->Add(new Sprite(118, 387, 136, 405, d3dtex), 100);
			ani->Add(new Sprite(98, 387, 116, 405, d3dtex), 100);
			ani->Add(new Sprite(118, 387, 136, 405, d3dtex), 100);
			ani->Add(new Sprite(138, 387, 156, 405, d3dtex), 100);
			this->animations->Add(ani);
			ani->Repeat(true);
			break;
		}
		case ANIMATIONS::TURNRIGHT:
		{
			Animation* ani = new Animation();
			ani->Add(new Sprite(118, 387, 136, 405, d3dtex), 100);
			ani->Add(new Sprite(138, 387, 156, 405, d3dtex), 100);
			this->animations->Add(ani);
			ani->Repeat(true);
			break;
		}
		case ANIMATIONS::TURNLEFT:
		{
			Animation* ani = new Animation();
			ani->Add(new Sprite(118, 387, 136, 405, d3dtex), 100);
			ani->Add(new Sprite(98, 387, 116, 405, d3dtex), 100);
			this->animations->Add(ani);
			ani->Repeat(true);
			break;
		}
		case ANIMATIONS::FLYRIGHT:
		{
			Animation* ani = new Animation();
			ani->Add(new Sprite(138, 387, 156, 405, d3dtex), 100);
			ani->Add(new Sprite(158, 387, 176, 405, d3dtex), 600);
			this->animations->Add(ani);
			ani->Repeat(true);
			break;
		}
		case ANIMATIONS::FLYLEFT:
		{
			Animation* ani = new Animation();
			ani->Add(new Sprite(98, 387, 116, 405, d3dtex), 100);
			ani->Add(new Sprite(78, 387, 96, 405, d3dtex), 600);
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
void Orb::Update(DWORD dt)
{
	if (animations != NULL)
		animations->Update(dt);
}
void Orb::PhysicalCalculate(DWORD dt)
{
}
void Orb::Render()
{
	if (animations != NULL)
		animations->Render(*wPosition);
}
