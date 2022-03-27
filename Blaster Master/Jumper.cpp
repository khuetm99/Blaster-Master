#include "Jumper.h"
#include "Car.h"

Jumper::Jumper(int x, int y, int width, int height) : Object(x, y, width, height)
{
	this->SetTypeObj(TYPEOBJECT::JUMPER);
	this->wPosition = new D3DXVECTOR2(x, y);
	this->isCollision = true;
	this->isExist = true;
	this->width = width;
	this->height = height;
	Init();
	this->WalkRight();
}

void Jumper::Init()
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
			ani->Add(new Sprite(152, 499, 167, 525, d3dtex), 100);
			this->animations->Add(ani);
			ani->Repeat(true);
			this->animations->Start(ANIMATIONS::IDLERIGHT);
			break;
		}
		case ANIMATIONS::IDLELEFT:
		{
			Animation* ani = new Animation();
			ani->Add(new Sprite(87, 499, 102, 525, d3dtex), 100);
			this->animations->Add(ani);
			ani->Repeat(true);
			break;
		}
		case ANIMATIONS::WALKRIGHT:
		{
			Animation* ani = new Animation();
			ani->Add(new Sprite(132, 500, 149, 525, d3dtex), 100);
			ani->Add(new Sprite(152, 499, 167, 525, d3dtex), 100);
			ani->Add(new Sprite(170, 500, 185, 525, d3dtex), 100);
			ani->Add(new Sprite(152, 499, 167, 525, d3dtex), 100);
			this->animations->Add(ani);
			ani->Repeat(true);
			break;
		}
		case ANIMATIONS::WALKLEFT:
		{
			Animation* ani = new Animation();
			ani->Add(new Sprite(105, 500, 122, 525, d3dtex), 100);
			ani->Add(new Sprite(87, 499, 102, 525, d3dtex), 100);
			ani->Add(new Sprite(69, 500, 84, 525, d3dtex), 100);
			ani->Add(new Sprite(87, 499, 102, 525, d3dtex), 100);
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

	this->WalkLeft();
}

void Jumper::Update(DWORD dt, vector<LPOBJECT>* objs)
{
	if (isExist) {

		//DebugOut(L"vx: %f  vy: %f\n ", this->wVelocity->x, this->wVelocity->y);

		PhysicalCalculate(dt);


		// Nhay sau một thời gia nhất định
		delayjumptime += dt;
		if (delayjumptime > JUMPER_TIME_DELAY_JUMP) {
			delayjumptime = 0;
		}
		if (delayjumptime == 0) {
			this->Jump();
		}

		D3DXVECTOR2 center = GetCollisionBoxCenter();
		RECT box = Car::GetInstance()->GetCollisionBox();

		// xet va cham vs car
		if (center.x > box.left && center.x < box.right && center.y > box.top && center.y < box.bottom) {
			if (Car::GetInstance()->GettIsHurt() == false) {
				Car::GetInstance()->SetIsHurt(true);
				Car::GetInstance()->HP(1);
			}
		}

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

void Jumper::PhysicalCalculate(DWORD dt)
{
	this->wVelocity->y += (Global::_G + wAcceleration->y) * dt;
}


void Jumper::Render()
{
	/*if (tex->LPDIRECT3DTEXTURE() == nullptr) {
		tex = new Texture(L"textures/bbox.png", D3DCOLOR_XRGB(255, 255, 255));
	}
	LPDIRECT3DTEXTURE9 d3dtex = tex->LPDIRECT3DTEXTURE();

	D3DXVECTOR2 pos = D3DXVECTOR2(GetCollisionBox().left, GetCollisionBox().top);
	D3DXVECTOR3 p(Global::GetInstance()->_Camera->Convert(pos).x, Global::GetInstance()->_Camera->Convert(pos).y, 0);
	Global::GetInstance()->_SpriteHandler->Draw(d3dtex, &GetCollisionBox(), NULL, &p, D3DCOLOR_ARGB(255, 255, 255, 255));*/

	if (animations != nullptr && isExist == true) {
		animations->Render(*wPosition);
	}
}

void Jumper::DoActionOnCollision(int nx, int ny, Object* obj)
{
	if (obj->GetTypeObj() == TYPEOBJECT::BRICK) {
		if (nx != 0) {
			if (direction == 1) {
				if (status == STATUSES::JUMP) {
					this->direction = -1;
					this->wVelocity->x = -JUMPER_SPEED_JUMP_HORIZONTAL;
					this->animations->Start(ANIMATIONS::IDLELEFT);
				}
				else
				if (status == STATUSES::WALK) {
					this->WalkLeft();
					this->wVelocity->x = -JUMPER_SPEED_WALK;
				}
			}
			else
			if (direction == -1) {
				if (status == STATUSES::JUMP) {
					this->direction = 1;
					this->wVelocity->x = JUMPER_SPEED_JUMP_HORIZONTAL;
					this->animations->Start(ANIMATIONS::IDLERIGHT);
				}
				else
				if (status == STATUSES::WALK) {
					this->WalkRight();
					this->wVelocity->x = JUMPER_SPEED_WALK;
				}
			}
		}

		if (ny == -1 && status == STATUSES::JUMP) {
			if (direction == 1) {
				this->WalkRight();
			}
			else
			if (direction == -1) {
				this->WalkLeft();
			}
		}
	}

	
}

void Jumper::WalkRight()
{
	this->direction = 1;
	this->status = STATUSES::WALK;
	this->animations->Start(ANIMATIONS::WALKRIGHT);
	this->wVelocity->x = JUMPER_SPEED_WALK;
}

void Jumper::WalkLeft()
{
	this->direction = -1;
	this->status = STATUSES::WALK;
	this->animations->Start(ANIMATIONS::WALKLEFT);
	this->wVelocity->x = -JUMPER_SPEED_WALK;
}

void Jumper::Jump()
{
	this->status = STATUSES::JUMP;
	this->wVelocity->y = -JUMPER_SPEED_JUMP_VERTICAL;
	if (this->direction == 1) {
		this->wVelocity->x = JUMPER_SPEED_JUMP_HORIZONTAL;
		this->animations->Start(ANIMATIONS::IDLERIGHT);
	}
	else 
	if (this->direction == -1) {
		this->wVelocity->x = -JUMPER_SPEED_JUMP_HORIZONTAL;
		this->animations->Start(ANIMATIONS::IDLELEFT);
	}
	
}

void Jumper::Die()
{
}

RECT Jumper::GetCollisionBox()
{
	RECT r;
	r.left = wPosition->x;
	r.right = wPosition->x + width;
	r.top = wPosition->y;
	r.bottom = wPosition->y + height;
	return r;
}

D3DXVECTOR2 Jumper::GetCollisionBoxCenter()
{
	RECT r = GetCollisionBox();
	return D3DXVECTOR2((r.left + r.right) / 2, (r.top + r.bottom) / 2);
}


