#include "SkullBullet.h"


SkullBullet::SkullBullet(int direction, float x, float y)
{
	this->isExist = true;
	this->direction = direction;
	this->isCollision = true;
	this->wPosition = new D3DXVECTOR2(x, y);
	this->wVelocity->x = SKULLBULLET_HORIZONAL_SPEED * direction;
	this->ax = this->ay = 0.0f;
	this->x = x;
	this->y = y;

	LPDIRECT3DTEXTURE9 d3dtex = Textures::GetInstance()->GetDirect3DTexture(Textures::TEXTURES::ENEMY);
	LPDIRECT3DTEXTURE9 d3dtex1 = Textures::GetInstance()->GetDirect3DTexture(Textures::TEXTURES::CHARACTERLEFT);

	for (int i = 0; i < ANIMATIONS::_lenght; i++)
	{
		switch (i)
		{
		case ANIMATIONS::FLY: {
			Animation* ani = new Animation();
			ani->Add(new Sprite(192, 514, 202, 524, d3dtex), 100);
			ani->Repeat(true);
			this->animations->Add(ani);
			break;
		}
		case ANIMATIONS::DESTROY: {
			Animation* ani = new Animation();
			ani->Add(new Sprite(298, 103, 309, 116, d3dtex1), D3DXVECTOR2(-4, -4), 50);
			ani->Add(new Sprite(298, 103, 309, 116, d3dtex1), D3DXVECTOR2(-4, -4), 50);
			this->animations->Add(ani);
			break;
		}
		}
	}

	this->animations->Start(ANIMATIONS::FLY);
}


void SkullBullet::Update(DWORD dt, vector<LPOBJECT>* objs) {

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
					DoActionOnCollision(nx, ny, min_tx, min_ty, coEventsResult.at(i)->obj, dt);
				}

				for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
			}
		}

		this->animations->Update(dt);
	}

}

void SkullBullet::PhysicalCalculate(DWORD dt)
{
	this->wVelocity->y += (Global::_G) * dt;
}

void SkullBullet::DoActionOnCollision(int nx, int ny, float min_tx, float min_ty, LPOBJECT obj, DWORD dt)
{
	if (obj->GetTypeObj() == TYPEOBJECT::BRICK) {
		float x = this->wPosition->x + this->wVelocity->x * dt * min_tx;
		float y = this->wPosition->y + this->wVelocity->y * dt * min_ty;

		wPosition->x = x;
		wPosition->y = y;

		if (nx != 0) {
			this->wVelocity->x = 0.0f;

		}
		if (ny == -1) {
			float v = - this->wVelocity->y + 0.05;
			if ((-this->wVelocity->y + 0.05) >= 0) {
				v = 0;
				this->wVelocity->x = 0;
			}
			this->wVelocity->y = v;	
		}

	}
	else
	if(obj->GetTypeObj() == TYPEOBJECT::CAR){
		LPCAR car = dynamic_cast<LPCAR>(obj);
		if (car->GettIsHurt() == false) {
			Car::GetInstance()->HP(GetDamage());
			Car::GetInstance()->SetIsHurt(true);
			SetDamage(0);
			Destroy();
		}	
	}
}

void SkullBullet::Render() {

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


void SkullBullet::Destroy()
{
	this->isCollision = false;
	this->animations->Start(ANIMATIONS::DESTROY);
	this->status = STATUSES::DESTROYED;
	this->animations->Start(ANIMATIONS::DESTROY);
}

void SkullBullet::SetDamage(int damage)
{
	this->damage = damage;
}


int SkullBullet::GetDamage()
{
	return this->damage;
}

RECT SkullBullet::GetCollisionBox()
{
	RECT r;
	r.left = wPosition->x - 0;
	r.right = wPosition->x + 10;
	r.top = wPosition->y - 0;
	r.bottom = wPosition->y + 10;
	return r;
}

D3DXVECTOR2 SkullBullet::GetCollisionBoxCenter()
{
	RECT r = GetCollisionBox();
	return D3DXVECTOR2((r.left + r.right) / 2, (r.top + r.bottom) / 2);
}

