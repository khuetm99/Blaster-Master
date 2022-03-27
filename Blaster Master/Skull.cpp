#include "Skull.h"
#include "Car.h"

Skull::Skull(int x, int y, int width, int height) : Object(x, y, width, height)
{
	this->SetTypeObj(TYPEOBJECT::SKULL);
	this->wPosition = new D3DXVECTOR2(x, y);
	this->isCollision = true;
	this->isExist = true;
	this->width = width;
	this->height = height;
	Init();
}
void Skull::Init()
{
	this->width = 18;
	this->height = 18;

	LPDIRECT3DTEXTURE9 d3dtex = Textures::GetInstance()->GetDirect3DTexture(Textures::TEXTURES::ENEMY);
	LPDIRECT3DTEXTURE9 d3dtex1 = Textures::GetInstance()->GetDirect3DTexture(Textures::TEXTURES::CHARACTERLEFT);

	for (int i = 0; i < ANIMATIONS::_LENGHT; i++)
	{
		switch (i)
		{
		case ANIMATIONS::IDLERIGHT:
		{
			Animation* ani = new Animation();
			ani->Add(new Sprite(194, 530, 212, 548, d3dtex), 100);
			this->animations->Add(ani);
			ani->Repeat(true);
			break;
		}
		case ANIMATIONS::IDLELEFT:
		{
			Animation* ani = new Animation();
			ani->Add(new Sprite(42, 530, 60, 548, d3dtex), 100);
			this->animations->Add(ani);
			ani->Repeat(true);
			break;
		}
		case ANIMATIONS::ATTACKRIGHT:
		{
			Animation* ani = new Animation();
			ani->Add(new Sprite(174, 527, 192, 548, d3dtex), 300);
			ani->Add(new Sprite(194, 530, 212, 548, d3dtex), 100);
			this->animations->Add(ani);
			ani->Repeat(true);
			break;
		}
		case ANIMATIONS::ATTACKLEFT:
		{
			Animation* ani = new Animation();
			ani->Add(new Sprite(62, 527, 80, 548, d3dtex), 300);
			ani->Add(new Sprite(42, 530, 60, 548, d3dtex), 100);
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

	this->animations->Start(ANIMATIONS::IDLELEFT);
	
}

void Skull::Update(DWORD dt, vector<LPOBJECT>* objs)
{
	if (isExist) {

		//DebugOut(L"vx: %f  vy: %f\n ", this->wVelocity->x, this->wVelocity->y);

		int dx = Car::Car::GetInstance()->GetCollisionBoxCenter().x - GetCollisionBoxCenter().x;
		int dy = Car::Car::GetInstance()->GetCollisionBoxCenter().y - GetCollisionBoxCenter().y;

		if (abs(dy) < 30) {
			if (GetCollisionBoxCenter().x < Car::GetInstance()->GetCollisionBoxCenter().x - 10) {
				FlyRight();
			}
			else
			if (GetCollisionBoxCenter().x > Car::GetInstance()->GetCollisionBoxCenter().x + 10) {
				FlyLeft();
			}
			else {
				Attack();
			}
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
					if (coEventsResult.at(i)->obj->GetTypeObj() == TYPEOBJECT::BRICK || coEventsResult.at(i)->obj->GetTypeObj() == TYPEOBJECT::SKULL) {
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


	// bullet
	if (this->bullet != nullptr) {
		// them car vao list objects
		//objs->push_back(Car::GetInstance());
		this->bullet->Update(dt, objs);
	}
}


void Skull::Render()
{
	if (animations != nullptr && isExist == true) {
		animations->Render(*wPosition);
	}

	if (this->bullet != nullptr) {
		this->bullet->Render();
	}
}

void Skull::FlyRight()
{
	this->wVelocity->x = SKULL_FLY_SPEED;
	this->direction = 1;
	this->animations->Start(ANIMATIONS::IDLERIGHT);
}

void Skull::FlyLeft()
{
	this->wVelocity->x = -SKULL_FLY_SPEED;
	this->direction = -1;
	this->animations->Start(ANIMATIONS::IDLELEFT);
}

void Skull::Attack()
{
	if (this->isAttacked == false) {
		if (direction == 1) {
			this->isAttacked = true;
			this->animations->Start(ANIMATIONS::ATTACKRIGHT);
			this->bullet = new SkullBullet(direction, GetCollisionBoxCenter().x, GetCollisionBoxCenter().y);
		}
		else
		if (direction == -1) {
			this->isAttacked = true;
			this->animations->Start(ANIMATIONS::ATTACKLEFT);
			this->bullet = new SkullBullet(direction, GetCollisionBoxCenter().x, GetCollisionBoxCenter().y);

		}
	}
	
}

void Skull::DoActionOnCollision(int nx, int ny, Object* obj)
{
}

RECT Skull::GetCollisionBox()
{
	RECT r;
	r.left = wPosition->x;
	r.right = wPosition->x + width;
	r.top = wPosition->y;
	r.bottom = wPosition->y + height;
	return r;
}

D3DXVECTOR2 Skull::GetCollisionBoxCenter()
{
	RECT r = GetCollisionBox();
	return D3DXVECTOR2((r.left + r.right) / 2, (r.top + r.bottom) / 2);
}
