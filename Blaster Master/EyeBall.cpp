#include "EyeBall.h"

EyeBall::EyeBall(int x, int y, int width, int height) : Object(x, y, width, height)
{
	this->SetTypeObj(TYPEOBJECT::EYEBALL);
	this->SetDirection(false, false, false, false);
}
void EyeBall::Init()
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
			ani->Add(new Sprite(119, 550, 135, 566, d3dtex), 100);
			this->animations->Add(ani);
			ani->Repeat(true);
			break;
		}
		case ANIMATIONS::OPENEYERIGHT:
		{
			Animation* ani = new Animation();
			ani->Add(new Sprite(136, 550, 152, 566, d3dtex), 100);
			this->animations->Add(ani);
			ani->Repeat(true);
			break;
		}
		case ANIMATIONS::OPENEYELEFT:
		{
			Animation* ani = new Animation();
			ani->Add(new Sprite(102, 550, 118, 566, d3dtex), 100);
			this->animations->Add(ani);
			ani->Repeat(true);
			break;
		}
		case ANIMATIONS::ROLLEYE:
		{
			Animation* ani = new Animation();
			ani->Add(new Sprite(102, 550, 118, 566, d3dtex), 300);
			ani->Add(new Sprite(136, 550, 152, 566, d3dtex), 300);
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
void EyeBall::Update(DWORD dt)
{
	if (animations != NULL)
		animations->Update(dt);
}
void EyeBall::PhysicalCalculate(DWORD dt)
{
}
void EyeBall::Render()
{
	if (animations != NULL)
		animations->Render(*wPosition);
}
