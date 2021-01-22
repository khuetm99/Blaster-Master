#include "Door.h"

Door::Door(int map, int x, int y, int width, int height)
{
	this->isExist = true;
	this->isCollision = true;
	this->wPosition = new D3DXVECTOR2(x, y);
	this->map = map;
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;

	////texture trái
	//LPTEXTURE tex = new Texture(L"textures/area2.png", D3DCOLOR_XRGB(255, 255, 255));
	//LPDIRECT3DTEXTURE9 d3dtex = tex->LPDIRECT3DTEXTURE();
	LPDIRECT3DTEXTURE9 d3dtex = nullptr;
	if (map == 1) {
		d3dtex =  Textures::GetInstance()->GetDirect3DTexture(Textures::TEXTURES::MAP);
	}
	else
	if (map == 2) {
		d3dtex = Textures::GetInstance()->GetDirect3DTexture(Textures::TEXTURES::MAP2);
	}

	for (int i = 0; i < ANIMATIONS::_LENGHT; i++)
	{
		switch (i)
		{
			case ANIMATIONS::IDLE: {
				Animation* ani = new Animation();
				ani->Add(new Sprite(x, y, x + width, y + height, d3dtex), 100);
				this->animations->Add(ani);
				break;
			}
		}
	}

	this->animations->Start(ANIMATIONS::IDLE);
}


void Door::Update(DWORD dt, vector<LPOBJECT>* objs) {

	if (isExist) {

		if (isCollision) {
			vector<LPCOEVENT> coEvents;
			vector<LPCOEVENT> coEventsResult;

			coEvents.clear();
			Colision* a = new  Colision(this);
			a->CalcPotentialCollisions(objs, coEvents, dt);

			if (coEvents.size() == 0)
			{
				wPosition->x += (int)(this->wVelocity->x * dt);
				wPosition->y += (int)(this->wVelocity->y * dt);

			}
			else {
				float min_tx, min_ty, nx = 0, ny = 0;
				a->FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);
				for (int i = 0; i < coEventsResult.size(); i++) {
					if (coEventsResult.at(i)->obj->GetTypeObj() == TYPEOBJECT::BRICK) {
						float x = this->wPosition->x + this->wVelocity->x * dt * min_tx;
						float y = this->wPosition->y + this->wVelocity->y * dt * min_ty;

						wPosition->x = x;
						wPosition->y = y;

						if (nx != 0) {
							this->wVelocity->x = 0.0f;
							this->wAcceleration->x = 0.0f;
						}
						if (ny != 0) {
							this->wVelocity->y = 0.0f;
							this->wAcceleration->y = 0.0f;
						}

						DoActionOnCollision(nx, ny, coEventsResult.at(i)->obj);

					}
				}

				for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
			}
		}

		this->animations->Update(dt);
	}

}


void Door::DoActionOnCollision(int nx, int ny, LPOBJECT obj)
{
	if (obj->GetTypeObj() == TYPEOBJECT::BRICK) {
		//Destroy();
	}
}

void Door::Render() {

	if (isExist == true) {
		if (animations != nullptr)
			this->animations->Render(*wPosition);
	}

	/*if (tex->LPDIRECT3DTEXTURE() == nullptr) {
		tex = new Texture(L"textures/bbox.png", D3DCOLOR_XRGB(255, 255, 255));
	}
	LPDIRECT3DTEXTURE9 d3dtex = tex->LPDIRECT3DTEXTURE();

	D3DXVECTOR2 pos = D3DXVECTOR2(GetCollisionBox().left, GetCollisionBox().top);
	D3DXVECTOR3 p(Global::GetInstance()->_Camera->Convert(pos).x, Global::GetInstance()->_Camera->Convert(pos).y, 0);
	Global::GetInstance()->_SpriteHandler->Draw(d3dtex, &GetCollisionBox(), NULL, &p, D3DCOLOR_ARGB(255, 255, 255, 255));*/

}


RECT Door::GetCollisionBox()
{
	RECT r;

	if (map == 1) {
		r.left = wPosition->x;
		r.right = wPosition->x + width;
		r.top = wPosition->y;
		r.bottom = wPosition->y + height;
	}
	else
	if (map == 2) {
		if (width == 32) {
			r.left = wPosition->x + 10;
			r.right = wPosition->x + width - 10;
			r.top = wPosition->y - 13;
			r.bottom = wPosition->y + height + 33;
		}
		else 
		if (width == 64) {
			r.left = wPosition->x - 13;
			r.right = wPosition->x + width + 13;
			r.top = wPosition->y + 35;
			r.bottom = wPosition->y + height - 10;
		}	
	}
	
	return r;
}

D3DXVECTOR2 Door::GetCollisionBoxCenter()
{
	RECT r = GetCollisionBox();
	return D3DXVECTOR2((r.left + r.right) / 2, (r.top + r.bottom) / 2);
}

