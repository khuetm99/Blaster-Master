#include "Jason1Bullet.h"


Jason1Bullet::Jason1Bullet(float x, float y)
{
	this->isExist = true;
	this->isCollision = true;
	SetBottomPostion(D3DXVECTOR2(x, y));

	////texture trái
	//LPTEXTURE tex = new Texture(L"textures/BlasterMaster.png", D3DCOLOR_XRGB(0, 57, 115));
	//LPDIRECT3DTEXTURE9 d3dtex = tex->LPDIRECT3DTEXTURE();
	////texture phải
	//LPTEXTURE texR = new Texture(L"textures/BlasterMaster1.png", D3DCOLOR_XRGB(0, 57, 115));
	//LPDIRECT3DTEXTURE9 d3dtexR = texR->LPDIRECT3DTEXTURE();

	LPDIRECT3DTEXTURE9 d3dtex = Textures::GetInstance()->GetDirect3DTexture(Textures::TEXTURES::CHARACTERLEFT);
	LPDIRECT3DTEXTURE9 d3dtexR = Textures::GetInstance()->GetDirect3DTexture(Textures::TEXTURES::CHARACTERRIGHT);



	for (int i = 0; i < ANIMATIONS::_lenght; i++)
	{
		switch (i)
		{
			case ANIMATIONS::FlYRIGHT: {
				Animation* ani = new Animation();
				ani->Add(new Sprite(331, 40, 335, 44, d3dtexR), 100);
				this->animations->Add(ani);
				ani->Repeat(true);
				break;
			}
			case ANIMATIONS::FLYLEFT: {
				Animation* ani = new Animation();
				ani->Add(new Sprite(75, 40, 79, 44, d3dtex), 100);
				this->animations->Add(ani);
				ani->Repeat(true);
				break;
			}
			case ANIMATIONS::DESTROY: {
				Animation* ani = new Animation();
				ani->Add(new Sprite(140, 101, 147, 109, d3dtex), D3DXVECTOR2(-4, -4), 30);
				ani->Add(new Sprite(149, 97, 165, 110, d3dtex), D3DXVECTOR2(-4, -4), 30);
				ani->Add(new Sprite(166, 97, 182, 113, d3dtex), D3DXVECTOR2(-4, -4), 30);
				//ani->Add(new Sprite(183, 93, 207, 117, d3dtex), 100);
				this->animations->Add(ani);
				break;
			}
		}
	}

}


void Jason1Bullet::Update(DWORD dt, vector<LPOBJECT>* objs) {

	if (isExist) {

		if (this->animations->GetCurrentAnimationID() == ANIMATIONS::DESTROY && this->animations->GetCurrentAnimation()->IsDone()) {
			this->isExist = false;
		}

		PhysicalCalculate(dt);

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

void Jason1Bullet::PhysicalCalculate(DWORD dt)
{
	this->wPosition->x += this->wVelocity->x * dt;
	this->wPosition->y += this->wVelocity->y * dt;
}

void Jason1Bullet::DoActionOnCollision(int nx, int ny, LPOBJECT obj)
{
	if (obj->GetTypeObj() == TYPEOBJECT::BRICK) {
		Destroy();
	}
	else
	if (obj->GetTypeObj() == TYPEOBJECT::JUMPER) {
		Destroy();
	}
}

void Jason1Bullet::Render() {

	/*if (tex->LPDIRECT3DTEXTURE() == nullptr) {
		tex = new Texture(L"textures/bbox.png", D3DCOLOR_XRGB(255, 255, 255));
	}
	LPDIRECT3DTEXTURE9 d3dtex = tex->LPDIRECT3DTEXTURE();

	D3DXVECTOR2 pos = D3DXVECTOR2(GetCollisionBox().left, GetCollisionBox().top);
	D3DXVECTOR3 p(Global::GetInstance()->_Camera->Convert(pos).x, Global::GetInstance()->_Camera->Convert(pos).y, 0);
	Global::GetInstance()->_SpriteHandler->Draw(d3dtex, &GetCollisionBox(), NULL, &p, D3DCOLOR_ARGB(255, 255, 255, 255));
*/

	if (isExist == true) {
		if (animations != nullptr)
			this->animations->Render(*wPosition);
	}
}

void Jason1Bullet::FlyRight()
{
	this->status = STATUSES::FLY;
	this->animations->Start(ANIMATIONS::FlYRIGHT);
	this->wVelocity->x = 0.1;
}

void Jason1Bullet::FlyLeft()
{
	this->status = STATUSES::FLY;
	this->animations->Start(ANIMATIONS::FLYLEFT);
	this->wVelocity->x = -0.1;
}

void Jason1Bullet::Destroy()
{
	this->isCollision = false;
	this->status = STATUSES::DESTROYED;
	this->animations->Start(ANIMATIONS::DESTROY);
}

RECT Jason1Bullet::GetCollisionBox()
{
	RECT r;
	r.left = wPosition->x - 0;
	r.right = wPosition->x + 3;
	r.top = wPosition->y - 0;
	r.bottom = wPosition->y + 3;
	return r;
}

D3DXVECTOR2 Jason1Bullet::GetCollisionBoxCenter()
{
	RECT r = GetCollisionBox();
	return D3DXVECTOR2((r.left + r.right) / 2, (r.top + r.bottom) / 2);
}
