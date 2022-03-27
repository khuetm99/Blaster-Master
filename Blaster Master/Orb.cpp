#include "Orb.h"

Orb::Orb(int x, int y, int width, int height) : Object(x, y, width, height)
{
	this->SetTypeObj(TYPEOBJECT::ORB);
	this->wPosition = new D3DXVECTOR2(x, y);
	this->isCollision = true;
	this->isExist = true;
	this->width = width;
	this->height = height;
	//Init();
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

void Orb::Update(DWORD dt, vector<LPOBJECT>* objs)
{
	if (isExist) {

		//DebugOut(L"vx: %f  vy: %f\n ", this->wVelocity->x, this->wVelocity->y);

		PhysicalCalculate(dt);



		// khoi tao trang thai khong va cham voi 2 phuong X, Y
		this->isImpacted_X = this->isImpacted_Y = false;

		if (isCollision && objs->size() > 0) {

			vector<LPCOEVENT> coEvents;
			vector<LPCOEVENT> coEventsResult;

			coEvents.clear();
			Colision* col = new  Colision(this);
			col->CalcPotentialCollisions(objs, coEvents, dt);

			//DebugOut(L"vy: %f  dy: %d  dt: %d\n", wVelocity->y, (int)(this->wVelocity->y * dt), dt);

			if (coEvents.size() == 0)
			{
				wPosition->x += this->wVelocity->x * dt;
				wPosition->y += this->wVelocity->y * dt;

				//DebugOut(L"vy: %f  dy: %d  dt: %d\n", wVelocity->y, (int)(this->wVelocity->y * dt), dt);
			}
			else {
				float min_tx, min_ty, nx = 0, ny = 0;
				col->FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);
				for (int i = 0; i < coEventsResult.size(); i++) {
					if (coEventsResult.at(i)->obj->GetTypeObj() == TYPEOBJECT::BRICK) {
						if (coEventsResult.at(i)->nx != 0) {
							wPosition->x = this->wPosition->x + this->wVelocity->x * dt * min_tx;
							if (nx == -1 && this->wVelocity->x > 0) { // va cham voi vat the ben duoi
								this->wVelocity->x = 0.0f;
							}
							if (nx == 1 && this->wVelocity->x < 0) { // va cham voi vat the ben tren
								this->wVelocity->x = 0.0f;
							}
							this->isImpacted_X = true;
						}

						if (coEventsResult.at(i)->ny != 0) {
							wPosition->y = this->wPosition->y + this->wVelocity->y * dt * min_ty;
							if (ny == -1 && this->wVelocity->y > 0) { // va cham voi vat the ben duoi
								this->wVelocity->y = 0.0f;
							}
							if (ny == 1 && this->wVelocity->y < 0) { // va cham voi vat the ben tren
								this->wVelocity->y = 0.0f;
							}
							this->isImpacted_Y = true;
						}
					}

					DoActionOnCollision(nx, ny, coEventsResult.at(i)->obj);
				}

				// cap nhat toa do khi khong va cham 
				if (isImpacted_X == false) {
					wPosition->x += this->wVelocity->x * dt;
				}
				if (isImpacted_Y == false) {
					wPosition->y += this->wVelocity->y * dt;
				}

				for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
			}
		}
		else {
			wPosition->x += this->wVelocity->x * dt;
			wPosition->y += this->wVelocity->y * dt;
		}

		this->animations->Update(dt);
	}
}

void Orb::PhysicalCalculate(DWORD dt)
{
	this->wVelocity->y += (Global::_G + wAcceleration->y) * dt;
}
void Orb::Render()
{
	if (animations != nullptr && isExist == true) {
		animations->Render(*wPosition);
	}
}

void Orb::DoActionOnCollision(int nx, int ny, Object* obj)
{
}

RECT Orb::GetCollisionBox()
{
	RECT r;
	r.left = wPosition->x;
	r.right = wPosition->x + width;
	r.top = wPosition->y;
	r.bottom = wPosition->y + height;
	return r;
}

D3DXVECTOR2 Orb::GetCollisionBoxCenter()
{
	RECT r = GetCollisionBox();
	return D3DXVECTOR2((r.left + r.right) / 2, (r.top + r.bottom) / 2);
}
