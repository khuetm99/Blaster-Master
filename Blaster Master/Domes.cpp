#include "Domes.h"

Domes::Domes(int x, int y, int width, int height) : Object(x, y, width, height)
{
	this->SetTypeObj(TYPEOBJECT::DOMES);
	this->wPosition = new D3DXVECTOR2(x, y);
	this->isCollision = true;
	this->isExist = true;
	this->width = width;
	this->height = height;
	//Init();
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
void Domes::Update(DWORD dt , vector<LPOBJECT>* objs)
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
void Domes::PhysicalCalculate(DWORD dt)
{
	this->wVelocity->y += (Global::_G + wAcceleration->y) * dt;
}

void Domes::Render()
{
	if (animations != nullptr && isExist == true) {
		animations->Render(*wPosition);
	}
}

void Domes::DoActionOnCollision(int nx, int ny, Object* obj)
{
}

RECT Domes::GetCollisionBox()
{
	RECT r;
	r.left = wPosition->x;
	r.right = wPosition->x + width;
	r.top = wPosition->y;
	r.bottom = wPosition->y + height;
	return r;
}

D3DXVECTOR2 Domes::GetCollisionBoxCenter()
{
	RECT r = GetCollisionBox();
	return D3DXVECTOR2((r.left + r.right) / 2, (r.top + r.bottom) / 2);
}

Domes::~Domes()
{
}

