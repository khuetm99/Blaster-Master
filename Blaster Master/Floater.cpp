#include "Floater.h"

Floater::Floater(int x, int y, int width, int height) : Object(x, y, width, height)
{
	this->SetTypeObj(TYPEOBJECT::FLOATER);
	this->SetDirection(false, false, false, false);
}
void Floater::Init()
{
	LPDIRECT3DTEXTURE9 d3dtex = Textures::GetInstance()->GetDirect3DTexture(Textures::TEXTURES::ENEMY);
	LPDIRECT3DTEXTURE9 d3dtex1 = Textures::GetInstance()->GetDirect3DTexture(Textures::TEXTURES::CHARACTERLEFT);

	for (int i = 0; i < ANIMATIONS::_LENGHT; i++)
	{
		switch (i)
		{
		case ANIMATIONS::FLYRIGHT:
		{
			Animation* ani = new Animation();
			ani->Add(new Sprite(152, 407, 170, 422, d3dtex), 100);
			ani->Add(new Sprite(132, 406, 150, 422, d3dtex), 100);
			this->animations->Add(ani);
			ani->Repeat(true);
			break;
		}
		case ANIMATIONS::FLYLEFT:
		{
			Animation* ani = new Animation();
			ani->Add(new Sprite(84, 407, 102, 422, d3dtex), 100);
			ani->Add(new Sprite(104, 406, 122, 422, d3dtex), 100);
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
	this->animations->Start(ANIMATIONS::FLYLEFT);

}
void Floater::Update(DWORD dt)
{
	if (animations != NULL)
		animations->Update(dt);
}
void Floater::PhysicalCalculate(DWORD dt)
{
}
void Floater::Render()
{
	if (animations != NULL)
		animations->Render(*wPosition);
}
