#include "Domes.h"

Domes::Domes(int x, int y, int width, int height) : Object(x, y, width, height)
{
	this->SetTypeObj(TYPEOBJECT::DOMES);
	this->SetDirection(false, false, false, false);
}
void Domes::Init()
{
	LPDIRECT3DTEXTURE9 d3dtex = Textures::GetInstance()->GetDirect3DTexture(Textures::TEXTURES::ENEMY);
	LPDIRECT3DTEXTURE9 d3dtex1 = Textures::GetInstance()->GetDirect3DTexture(Textures::TEXTURES::CHARACTERLEFT);

	for (int i = 0; i < ANIMATIONS::_LENGHT; i++)
	{
		switch (i)
		{
		case ANIMATIONS::WALKRIGHT:
		{
			Animation* ani = new Animation();
			ani->Add(new Sprite(149, 425, 167, 441, d3dtex), 100);
			ani->Add(new Sprite(169, 424, 187, 441, d3dtex), 100);
			this->animations->Add(ani);
			ani->Repeat(true);
			break;
		}
		case ANIMATIONS::WALKLEFT:
		{
			Animation* ani = new Animation();
			ani->Add(new Sprite(87, 425, 105, 441, d3dtex), 100);
			ani->Add(new Sprite(67, 424, 85, 441, d3dtex), 100);
			this->animations->Add(ani);
			ani->Repeat(true);
			break;
		}
		case ANIMATIONS::WALKDOWNRIGHT:
		{
			Animation* ani = new Animation();
			ani->Add(new Sprite(187, 441, 203, 459, d3dtex), 100);
			ani->Add(new Sprite(187, 461, 204, 479, d3dtex), 100);
			this->animations->Add(ani);
			ani->Repeat(true);
			break;
		}
		case ANIMATIONS::WALKDOWNLEFT:
		{
			Animation* ani = new Animation();
			ani->Add(new Sprite(51, 441, 67, 459, d3dtex), 100);
			ani->Add(new Sprite(50, 461, 67, 479, d3dtex), 100);
			this->animations->Add(ani);
			ani->Repeat(true);
			break;
		}
		case ANIMATIONS::WALKUPRIGHT:
		{
			Animation* ani = new Animation();
			ani->Add(new Sprite(105, 461, 121, 479, d3dtex), 100);
			ani->Add(new Sprite(105, 441, 122, 459, d3dtex), 100);
			this->animations->Add(ani);
			ani->Repeat(true);
			break;
		}
		case ANIMATIONS::WALKUPLEFT:
		{
			Animation* ani = new Animation();
			ani->Add(new Sprite(133, 461, 149, 479, d3dtex), 100);
			ani->Add(new Sprite(132, 441, 149, 459, d3dtex), 100);
			this->animations->Add(ani);
			ani->Repeat(true);
			break;
		}
		case ANIMATIONS::WALKREVERSERIGHT:
		{
			Animation* ani = new Animation();
			ani->Add(new Sprite(67, 479, 85, 495, d3dtex), 100);
			ani->Add(new Sprite(87, 479, 105, 496, d3dtex), 100);
			this->animations->Add(ani);
			ani->Repeat(true);
			break;
		}
		case ANIMATIONS::WALKREVERSELEFT:
		{
			Animation* ani = new Animation();
			ani->Add(new Sprite(169, 479, 187, 495, d3dtex), 100);
			ani->Add(new Sprite(149, 479, 167, 496, d3dtex), 100);
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
void Domes::Update(DWORD dt)
{
	if (animations!=nullptr)
	{
		this->animations->Update(dt);
	}
}
void Domes::PhysicalCalculate(DWORD dt)
{
}

void Domes::Render()
{
	if (animations != NULL)
		animations->Render(*wPosition);
}

Domes::~Domes()
{
}

