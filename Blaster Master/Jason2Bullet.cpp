#include "Jason2Bullet.h"

Jason2Bullet::Jason2Bullet(int direction, float x, float y)
{
	this->isExist = true;
	this->direction = direction;
	this->isCollision = true;
	this->wPosition = new D3DXVECTOR2(x, y);
	this->ax = this->ay = 0.0f;
	this->x = x;
	this->y = y;

	LPDIRECT3DTEXTURE9 d3dtex = Textures::GetInstance()->GetDirect3DTexture(Textures::TEXTURES::CHARACTERLEFT);
	
	for (int i = 0; i < ANIMATIONS::_lenght; i++)
	{
		switch (i)
		{
			case ANIMATIONS::FLY: {
				Animation* ani = new Animation();
				ani->Add(new Sprite(313, 106, 321, 114, d3dtex), 100);
				ani->Repeat(true);
				this->animations->Add(ani);
				break;
			}
			case ANIMATIONS::DESTROY: {
				Animation* ani = new Animation();
				ani->Add(new Sprite(298, 103, 309, 116, d3dtex), D3DXVECTOR2(-4, -4), 50);
				ani->Add(new Sprite(298, 103, 309, 116, d3dtex), D3DXVECTOR2(-4, -4), 50);
				this->animations->Add(ani);
				break;
			}
		}
	}

}


void Jason2Bullet::Update(DWORD dt, vector<LPOBJECT>* objs) {

	if (isExist) {

		if (this->animations->GetCurrentAnimationID() == ANIMATIONS::DESTROY && this->animations->GetCurrentAnimation()->IsDone()) {
			this->isExist = false;
		}

		PhysicalCalculate(dt);

		if (isCollision && objs->size() > 0) {
			vector<LPCOEVENT> coEvents;
			vector<LPCOEVENT> coEventsResult;

			coEvents.clear();
			Colision* a = new  Colision(this);
			a->CalcPotentialCollisions(objs, coEvents, dt);

			//DebugOut(L"vy: %f  dy: %d  dt: %d\n", wVelocity->y, (int)(this->wVelocity->y * dt), dt);

			if (coEvents.size() == 0)
			{
				wPosition->x += (int)(this->wVelocity->x * dt);
				wPosition->y += (int)(this->wVelocity->y * dt);

				//DebugOut(L"vy: %f  dy: %d  dt: %d\n", wVelocity->y, (int)(this->wVelocity->y * dt), dt);
			}
			else {
				float min_tx, min_ty, nx = 0, ny = 0;
				a->FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);
				for (int i = 0; i < coEventsResult.size(); i++) {
					DoActionOnCollision(nx, ny, coEventsResult.at(i)->obj, dt);
				}

				for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
			}
		}

		this->animations->Update(dt);
	}

}

void Jason2Bullet::PhysicalCalculate(DWORD dt)
{
	//this->wPosition->x += this->wVelocity->x * dt;
	//this->wPosition->y += this->wVelocity->y * dt;

	if (direction == DIRECTIONS::UP) {
		if (wPosition->x + 30 <= x) {
			wVelocity->x = 0.2;
		}
		if (wPosition->x - 30 >= x) {
			wVelocity->x = -0.2;
		}
	}
	if (direction == DIRECTIONS::DOWN) {
		if (wPosition->x + 30 <= x) {
			wVelocity->x = 0.2;
		}
		if (wPosition->x - 30 >= x) {
			wVelocity->x = -0.2;
		}
	}
	if (direction == DIRECTIONS::LEFT) {
		if (wPosition->y + 30 <= y) {
			wVelocity->y = 0.2;
		}
		if (wPosition->y - 30 >= y) {
			wVelocity->y = -0.2;
		}
	}
	if (direction == DIRECTIONS::RIGHT) {
		if (wPosition->y + 30 <= y) {
			wVelocity->y = 0.2;
		}
		if (wPosition->y - 30 >= y) {
			wVelocity->y = -0.2;
		}
	}
}

void Jason2Bullet::DoActionOnCollision(int nx, int ny, LPOBJECT obj, DWORD dt)
{
	if (obj->IsExist()) {
		if (obj->GetTypeObj() == TYPEOBJECT::BRICK) {
			Destroy();
		}
		else
		if (obj->GetTypeObj() == TYPEOBJECT::TELEPORTER) {
			LPTELEPORTER teleporter = dynamic_cast<LPTELEPORTER>(obj);
			if (teleporter->GetAnimations()->GetCurrentAnimationID() == Teleporter::ANIMATIONS::IDLEGREEN) {
				teleporter->SetExist(false);
			}	
			Destroy();
		}
		else
		if (obj->GetTypeObj() == TYPEOBJECT::EYEBALL) {
			LPEYEBALL eyeball = dynamic_cast<LPEYEBALL>(obj);
			eyeball->SetExist(false);
			Destroy();
		}
	}
	else {
		wPosition->x += (int)(this->wVelocity->x * dt);
		wPosition->y += (int)(this->wVelocity->y * dt);
	}
}

void Jason2Bullet::Render() {

	/*if (tex->LPDIRECT3DTEXTURE() == nullptr) {
		tex = new Texture(L"textures/bbox.png", D3DCOLOR_XRGB(255, 255, 255));
	}
	LPDIRECT3DTEXTURE9 d3dtex = tex->LPDIRECT3DTEXTURE();

	D3DXVECTOR2 pos = D3DXVECTOR2(GetCollisionBox().left, GetCollisionBox().top);
	D3DXVECTOR3 p(Global::GetInstance()->_Camera->Convert(pos).x, Global::GetInstance()->_Camera->Convert(pos).y, 0);
	Global::GetInstance()->_SpriteHandler->Draw(d3dtex, &GetCollisionBox(), NULL, &p, D3DCOLOR_ARGB(255, 255, 255, 255));*/


	if (isExist == true) {
		if (animations != nullptr)
			this->animations->Render(*wPosition);
	}
}

void Jason2Bullet::FlyUp()
{
	this->direction = DIRECTIONS::UP;
	this->animations->Start(ANIMATIONS::FLY);
	this->wVelocity->y = -0.1;
	this->wVelocity->x = -0.2;
}

void Jason2Bullet::FlyDown()
{
	this->direction = DIRECTIONS::DOWN;
	this->animations->Start(ANIMATIONS::FLY);
	this->wVelocity->y = 0.1;
	this->wVelocity->x = 0.2;
}

void Jason2Bullet::FlyRight()
{
	this->direction = DIRECTIONS::RIGHT;
	this->animations->Start(ANIMATIONS::FLY);
	this->wVelocity->y = -0.2;
	this->wVelocity->x = 0.1;
}

void Jason2Bullet::FlyLeft()
{
	this->direction = DIRECTIONS::LEFT;
	this->animations->Start(ANIMATIONS::FLY);
	this->wVelocity->y = 0.2;
	this->wVelocity->x = -0.1;
}


void Jason2Bullet::Destroy()
{
	this->isCollision = false;
	this->animations->Start(ANIMATIONS::DESTROY);
	this->status = STATUSES::DESTROYED;
	this->animations->Start(ANIMATIONS::DESTROY);
}

void Jason2Bullet::SetDamage(int damage)
{
	this->damage = damage;
}


int Jason2Bullet::GetDamage()
{
	return this->damage;
}

RECT Jason2Bullet::GetCollisionBox()
{
	RECT r;
	r.left = wPosition->x - 0;
	r.right = wPosition->x + 5;
	r.top = wPosition->y - 0;
	r.bottom = wPosition->y + 5;
	return r;
}

D3DXVECTOR2 Jason2Bullet::GetCollisionBoxCenter()
{
	RECT r = GetCollisionBox();
	return D3DXVECTOR2((r.left + r.right) / 2, (r.top + r.bottom) / 2);
}
