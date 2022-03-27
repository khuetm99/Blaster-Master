#include "EyeBall.h"

EyeBall::EyeBall(int x, int y, int width, int height) : Object(x, y, width, height)
{
	this->SetTypeObj(TYPEOBJECT::EYEBALL);
	this->wPosition = new D3DXVECTOR2(x, y);
	this->isCollision = true;
	this->isExist = true;
	this->width = width;
	this->height = height;
	Init();
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

	this->animations->Start(ANIMATIONS::IDLE);
}
void EyeBall::Update(DWORD dt)
{
	if (isExist) {

		//DebugOut(L"vx: %f  vy: %f\n ", this->wVelocity->x, this->wVelocity->y);

		// dich chuyen sau 3000ms
		this->teledelaytime += dt;
		if (this->teledelaytime > EYEBALL_DELAY_TIME) {
			this->teledelaytime = 0;
			int x = wPosition->x + rand() % 40 - 20;
			int y = wPosition->y + rand() % 40 - 20;

			if (x < wPosition->x) {
				this->animations->Start(ANIMATIONS::OPENEYELEFT);
			}
			if (x > wPosition->x) {
				this->animations->Start(ANIMATIONS::OPENEYERIGHT);
			}
			
		}

		this->animations->Update(dt);
	}
}

void EyeBall::PhysicalCalculate(DWORD dt)
{
	this->wVelocity->y += (Global::_G + wAcceleration->y) * dt;
}
void EyeBall::Render()
{
	if (animations != nullptr && isExist == true) {
		animations->Render(*wPosition);
	}
}

void EyeBall::DoActionOnCollision(int nx, int ny, Object* obj)
{
}

RECT EyeBall::GetCollisionBox()
{
	RECT r;
	r.left = wPosition->x;
	r.right = wPosition->x + width;
	r.top = wPosition->y;
	r.bottom = wPosition->y + height;
	return r;
}

D3DXVECTOR2 EyeBall::GetCollisionBoxCenter()
{
	RECT r = GetCollisionBox();
	return D3DXVECTOR2((r.left + r.right) / 2, (r.top + r.bottom) / 2);
}

EyeBall::~EyeBall()
{
}
