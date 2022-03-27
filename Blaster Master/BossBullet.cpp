#include "BossBullet.h"




BossBullet::BossBullet(D3DXVECTOR2 target, float x, float y)
{
	this->isExist = true;
	this->direction = direction;
	this->isCollision = true;
	this->wPosition = new D3DXVECTOR2(x, y);
	this->target = target;
	this->ax = this->ay = 0.0f;
	this->x = x;
	this->y = y;

	this->wVelocity->x = (target.x - this->wPosition->x) * 0.0003;
	this->wVelocity->y = (target.y - this->wPosition->y) * 0.0003;

	LPDIRECT3DTEXTURE9 d3dtex = Textures::GetInstance()->GetDirect3DTexture(Textures::TEXTURES::CHARACTERLEFT);
	LPDIRECT3DTEXTURE9 d3dtex1 = Textures::GetInstance()->GetDirect3DTexture(Textures::TEXTURES::ITEM);

	for (int i = 0; i < ANIMATIONS::_lenght; i++)
	{
		switch (i)
		{
		case ANIMATIONS::FLY: {
			Animation* ani = new Animation();
			ani->Add(new Sprite(57, 61, 66, 70, d3dtex1), 100);
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

	this->animations->Start(ANIMATIONS::FLY);
}


void BossBullet::Update(DWORD dt) {

	if (isExist) {

		wPosition->x += this->wVelocity->x * dt;
		wPosition->y += this->wVelocity->y * dt;


		D3DXVECTOR2 center = GetCollisionBoxCenter();
		RECT box = Jason2::GetInstance()->GetCollisionBox();

		// bien mat sau khi no
		if (this->animations->GetCurrentAnimationID() == ANIMATIONS::DESTROY && this->animations->GetCurrentAnimation()->IsDone()) {
			this->isExist = false;
		}

		// xet va cham vs jason
		if (center.x > box.left && center.x < box.right && center.y > box.top && center.y < box.bottom) {
			if (Jason2::GetInstance()->GettIsHurt() == false) {
				Jason2::GetInstance()->SetIsHurt(true);
				Jason2::GetInstance()->HP(1);
			}
			this->Destroy();
		}
		
		this->animations->Update(dt);
	}

}

void BossBullet::PhysicalCalculate(DWORD dt)
{
	this->wVelocity->y += (Global::_G) * dt;
}

void BossBullet::DoActionOnCollision(int nx, int ny, float min_tx, float min_ty, LPOBJECT obj, DWORD dt)
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
			float v = -this->wVelocity->y + 0.01;
			if ((-this->wVelocity->y + 0.01) >= 0) {
				v = 0;
				this->wVelocity->x = 0;
			}
			this->wVelocity->y = v;
		}

	}
	else
	if (obj->GetTypeObj() == TYPEOBJECT::CAR) {
			
	}
}

void BossBullet::Render() {

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


void BossBullet::Destroy()
{
	this->isCollision = false;
	this->animations->Start(ANIMATIONS::DESTROY);
	this->status = STATUSES::DESTROYED;
	this->animations->Start(ANIMATIONS::DESTROY);
}

void BossBullet::SetDamage(int damage)
{
	this->damage = damage;
}


int BossBullet::GetDamage()
{
	return this->damage;
}

RECT BossBullet::GetCollisionBox()
{
	RECT r;
	r.left = wPosition->x - 0;
	r.right = wPosition->x + 5;
	r.top = wPosition->y - 0;
	r.bottom = wPosition->y + 5;
	return r;
}

D3DXVECTOR2 BossBullet::GetCollisionBoxCenter()
{
	RECT r = GetCollisionBox();
	return D3DXVECTOR2((r.left + r.right) / 2, (r.top + r.bottom) / 2);
}

