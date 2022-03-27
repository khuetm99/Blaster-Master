#include "Teleporter.h"

Teleporter::Teleporter(int x, int y, int width, int height) : Object(x, y, width, height)
{
	this->SetTypeObj(TYPEOBJECT::TELEPORTER);
	this->wPosition = new D3DXVECTOR2(x, y);
	this->firstPos = D3DXVECTOR2(x, y);
	this->isCollision = true;
	this->isExist = true;
	this->width = width;
	this->height = height;
	Init();
}

void Teleporter::Init()
{
	LPDIRECT3DTEXTURE9 d3dtex = Textures::GetInstance()->GetDirect3DTexture(Textures::TEXTURES::ENEMY);
	LPDIRECT3DTEXTURE9 d3dtex1 = Textures::GetInstance()->GetDirect3DTexture(Textures::TEXTURES::CHARACTERLEFT);

	for (int i = 0; i < ANIMATIONS::_LENGHT; i++)
	{
		switch (i)
		{
		case ANIMATIONS::IDLEGRAY:
		{
			Animation* ani = new Animation();
			ani->Add(new Sprite(159, 568, 183, 600, d3dtex), 100);
			this->animations->Add(ani);
			ani->Repeat(true);
			this->animations->Start(ANIMATIONS::IDLEGRAY);
			break;
		}
		case ANIMATIONS::IDLEGREEN:
		{
			Animation* ani = new Animation();
			ani->Add(new Sprite(132, 568, 156, 600, d3dtex), 100);
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

	this->animations->Start(ANIMATIONS::IDLEGRAY);
}

void Teleporter::Update(DWORD dt)
{
	if (isExist) {


		//DebugOut(L"vx: %f  vy: %f\n ", this->wVelocity->x, this->wVelocity->y);


		// dich chuyen sau 3000ms
		this->teledelaytime += dt;
		if (this->teledelaytime > TELEPORTER_DELAY_TIME) {
			this->teledelaytime = 0;
			this->animations->Start(ANIMATIONS::IDLEGREEN);
			int x = wPosition->x + rand() % 60 - 30;
			int y = wPosition->y + rand() % 60 - 30;

			// gioi han vung tele
			if (x < firstPos.x - 80) {
				x = firstPos.x - 80;
			}
			if (x > firstPos.x + 80) {
				x = firstPos.x + 80;
			}
			if (y < firstPos.y - 80) {
				y = firstPos.y - 80;
			}
			if (y > firstPos.y + 80) {
				y = firstPos.y + 80;
			}

			this->wPosition->x = x;
			this->wPosition->y = y;

		}

		
		this->animations->Update(dt);
	}
}


void Teleporter::Render()
{
	if (animations != nullptr && isExist == true) {
		animations->Render(*wPosition);
	}
}

void Teleporter::DoActionOnCollision(int nx, int ny, Object* obj)
{
	/*if (obj->IsExist() && this->animations->GetCurrentAnimationID() == ANIMATIONS::IDLEGREEN) {
		LPJASON2BULLET bullet = dynamic_cast<LPJASON2BULLET>(obj);
		this->isExist = false;
	}*/
}

RECT Teleporter::GetCollisionBox()
{
	RECT r;
	r.left = wPosition->x;
	r.right = wPosition->x + width;
	r.top = wPosition->y;
	r.bottom = wPosition->y + height;
	return r;
}

D3DXVECTOR2 Teleporter::GetCollisionBoxCenter()
{
	RECT r = GetCollisionBox();
	return D3DXVECTOR2((r.left + r.right) / 2, (r.top + r.bottom) / 2);
}
