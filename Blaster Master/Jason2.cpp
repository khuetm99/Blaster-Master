#include "Jason2.h"


Jason2* Jason2::_instance = nullptr;

Jason2::Jason2()
{
	Init();
	this->objType = Object::TYPEOBJECT::JASON2;
	this->isExist = true;
	this->isInDoor = false;
	this->isCollision = true;
	this->direction = -1;
	this->delaytime = 0;
	this->wPosition->x = 150;
	this->wPosition->y = 1900;
}

void Jason2::Init()
{
	LPDIRECT3DTEXTURE9 d3dtex = Textures::GetInstance()->GetDirect3DTexture(Textures::TEXTURES::CHARACTERLEFT);
	LPDIRECT3DTEXTURE9 d3dtexR = Textures::GetInstance()->GetDirect3DTexture(Textures::TEXTURES::CHARACTERRIGHT);

	for (int i = 0; i < ANIMATIONS::_LENGTH; i++)
	{
		switch (i)
		{
			case ANIMATIONS::IDLERIGHT: {
				//đứng yên phải
				Animation* ani = new Animation();
				ani->Add(new Sprite(153, 69, 177, 101, d3dtexR), 100);
				this->animations->Add(ani);
				ani->Repeat(true);
				break;
			}
			case ANIMATIONS::IDLELEFT: {
				// đứng yên trái
				Animation* ani = new Animation();
				ani->Add(new Sprite(233, 69, 257, 101, d3dtex), 100);
				this->animations->Add(ani);
				ani->Repeat(true);
				break;
			}
			case ANIMATIONS::IDLEUP: {
				// đứng yên lên
				Animation* ani = new Animation();
				ani->Add(new Sprite(235, 36, 255, 68, d3dtex), 100);
				this->animations->Add(ani);
				ani->Repeat(true);
				break;
			}
			case ANIMATIONS::IDLEDOWN: {
				// đứng yên xuống
				Animation* ani = new Animation();
				ani->Add(new Sprite(235, 3, 255, 35, d3dtex), 100);
				this->animations->Add(ani);
				ani->Repeat(true);
				break;
			}
			case ANIMATIONS::WALKRIGHT: {
				// Đi phải
				Animation* ani = new Animation();
				ani->Add(new Sprite(128, 69, 152, 100, d3dtexR), 100);
				ani->Add(new Sprite(153, 69, 177, 101, d3dtexR), 100);
				ani->Add(new Sprite(178, 69, 202, 100, d3dtexR), 100);
				ani->Add(new Sprite(153, 69, 177, 101, d3dtexR), 100);
				this->animations->Add(ani);
				ani->Repeat(true);
				break;
			}
			case ANIMATIONS::WALKLEFT: {
				// Đi trái
				Animation* ani = new Animation();
				ani->Add(new Sprite(258, 69, 282, 100, d3dtex), 100);
				ani->Add(new Sprite(233, 69, 257, 101, d3dtex), 100);
				ani->Add(new Sprite(208, 69, 232, 100, d3dtex), 100);
				ani->Add(new Sprite(233, 69, 257, 101, d3dtex), 100);
				this->animations->Add(ani);
				ani->Repeat(true);
				break;
			}
			case ANIMATIONS::WALKUP: {
				// Đi lên
				Animation* ani = new Animation();
				ani->Add(new Sprite(261, 36, 280, 67, d3dtex), 100);
				ani->Add(new Sprite(235, 36, 255, 68, d3dtex), 100);
				ani->Add(new Sprite(210, 36, 230, 67, d3dtex), 100);
				ani->Add(new Sprite(235, 36, 255, 68, d3dtex), 100);
				this->animations->Add(ani);
				ani->Repeat(true);
				break;
			}
			case ANIMATIONS::WALKDOWN: {
				// Đi xuống
				Animation* ani = new Animation();
				ani->Add(new Sprite(260, 3, 280, 34, d3dtex), 100);
				ani->Add(new Sprite(235, 3, 255, 35, d3dtex), 100);
				ani->Add(new Sprite(210, 3, 230, 34, d3dtex), 100);
				ani->Add(new Sprite(235, 3, 255, 35, d3dtex), 100);
				this->animations->Add(ani);
				ani->Repeat(true);
				break;
			}
			case ANIMATIONS::DIERIGHT: {
				// Chết
				Animation* ani = new Animation();
				ani->Add(new Sprite(284, 4, 307, 35, d3dtex), 100);
				ani->Add(new Sprite(308, 6, 332, 35, d3dtex), 100);
				ani->Add(new Sprite(333, 8, 356, 35, d3dtex), 100);
				ani->Add(new Sprite(358, 10, 382, 35, d3dtex), 100);
				ani->Add(new Sprite(383, 19, 407, 35, d3dtex), 100);
				this->animations->Add(ani);
				break;
			}
		}
	}

	this->animations->Start(ANIMATIONS::IDLEDOWN);
}

void Jason2::Update(DWORD dt, vector<LPOBJECT>* objs, vector<LPDOOR>* doors)
{
	
	if (isExist) {


		DebugOut(L"Jason2 HP: %d  isHurt: %d\n", this->hp, this->isHurt);

		// thoi gia de nhap nhay khi bi tong thunog (moi 100ms)
		this->t += dt;


		// bi ton thuong
		if (isHurt) {
			hurtime += dt;
			if (hurtime > JASON2_HURT_TIME) {
				hurtime = 0;
				isHurt = false;
			}
		}

		// delay dan ban ra
		delaytime += dt;
		if (delaytime > JASON2_DELAY_SHOOT_TIME) {
			delaytime = 0;
		}

		KeyEvents();

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
				wPosition->x += (this->wVelocity->x * dt);
				wPosition->y += (this->wVelocity->y * dt);

				//DebugOut(L"vy: %f  dy: %d  dt: %d\n", wVelocity->y, (int)(this->wVelocity->y * dt), dt);
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
		else {
			wPosition->x += (int)(this->wVelocity->x * dt);
			wPosition->y += (int)(this->wVelocity->y * dt);
		}

		this->animations->Update(dt);

		// xet khi vao cổng
		this->isInDoor = false;
		for each (LPDOOR door in *doors)
		{
			D3DXVECTOR2 center = this->GetCollisionBoxCenter();
			RECT box = door->GetCollisionBox();
			if (box.left < center.x && center.x < box.right && box.top < center.y && center.y < box.bottom) {
				this->isInDoor = true;
				break;
			}
		}

		if (isInDoor) {
			this->isCollision = false;
		}
		else {
			this->isCollision = true;
		}
	}


	// Bullets
	if (bullets.size() > 0) {
		for each (LPJASON2BULLET bullet in bullets)
		{
			bullet->Update(dt, objs);
		}
	}

}

void Jason2::PhysicalCalculate(DWORD dt)
{
}

void Jason2::Render()
{

	/*if (tex->LPDIRECT3DTEXTURE() == nullptr) {
		tex = new Texture(L"textures/bbox.png", D3DCOLOR_XRGB(255, 255, 255));
	}
	LPDIRECT3DTEXTURE9 d3dtex = tex->LPDIRECT3DTEXTURE();

	D3DXVECTOR2 pos = D3DXVECTOR2(GetCollisionBox().left, GetCollisionBox().top);
	D3DXVECTOR3 p(Global::GetInstance()->_Camera->Convert(pos).x, Global::GetInstance()->_Camera->Convert(pos).y, 0);
	Global::GetInstance()->_SpriteHandler->Draw(d3dtex, &GetCollisionBox(), NULL, &p, D3DCOLOR_ARGB(255, 255, 255, 255));*/


	if (animations != nullptr) {
		if (isHurt) {
			// moi 100ms se chop nhay 1 lan
			bool flag = (t / 100) % 2;
			this->animations->Render(*wPosition, 0.7 * flag  + 0.3);
		}
		else {
			this->animations->Render(*wPosition);
		}
	}
		

	// Bullets
	if (bullets.size() > 0) {
		for each (LPJASON2BULLET bullet in bullets)
		{
			bullet->Render();
		}
	}
}

void Jason2::KeyEvents()
{
	LPKEYBOARD keyboard = Global::GetInstance()->_Keyboard;

	bool keyLeft = keyboard->IsKeyDown(DIK_LEFT);
	bool pressLeft = keyboard->IsKeyPress(DIK_LEFT);
	bool keyRight = keyboard->IsKeyDown(DIK_RIGHT);
	bool pressRight = keyboard->IsKeyPress(DIK_RIGHT);
	bool keyUp = keyboard->IsKeyDown(DIK_UP);
	bool keyDown = keyboard->IsKeyDown(DIK_DOWN);
	bool keyC = keyboard->IsKeyPress(DIK_C);
	bool keyZ = keyboard->IsKeyDown(DIK_Z);
	bool keyX = keyboard->IsKeyPress(DIK_X);
	bool keyShift = (keyboard->IsKeyPress(DIK_RSHIFT) || keyboard->IsKeyPress(DIK_LSHIFT));

	int aniId = this->animations->GetCurrentAnimationID();

	if (status != STATUSES::DIE) {

		// ============= UP - DOWN ========================
		if (keyUp && keyDown){
			
		}
		else
		if (!keyUp && !keyDown) {
		
		}
		else
		if (keyUp) {
			if (aniId != ANIMATIONS::WALKUP) {
				this->direction = DIRECTIONS::UP;
				this->wVelocity->x = 0;
				this->wVelocity->y = -0.1;
				this->animations->Start(ANIMATIONS::WALKUP);
			}
		}
		else
		if (keyDown){
			if (isFightingWithBoss) {
				if (aniId != ANIMATIONS::WALKUP) {
					this->direction = DIRECTIONS::UP;
					this->animations->Start(ANIMATIONS::WALKUP);
				}
				this->wVelocity->x = 0;
				this->wVelocity->y = 0.1;
			}
			else {
				if (aniId != ANIMATIONS::WALKDOWN) {
					this->direction = DIRECTIONS::DOWN;
					this->wVelocity->x = 0;
					this->wVelocity->y = 0.1;
					this->animations->Start(ANIMATIONS::WALKDOWN);
				}		
			}
			
		}


		// ============= RIGHT - LEFT ========================
		if ((!keyRight && !keyLeft) || (keyRight && keyLeft)) {
			
		}
		else
		if (keyRight) {
			if (isFightingWithBoss) {
				if (aniId != ANIMATIONS::WALKUP) {
					this->direction = DIRECTIONS::UP;
					this->animations->Start(ANIMATIONS::WALKUP);
				}
				this->wVelocity->x = 0.1;
				this->wVelocity->y = 0;
			}
			else {
				if (aniId != ANIMATIONS::WALKRIGHT) {
					this->direction = DIRECTIONS::RIGHT;
					this->wVelocity->x = 0.1;
					this->wVelocity->y = 0;
					this->animations->Start(ANIMATIONS::WALKRIGHT);
				}
			}	
		}
		else
		if (keyLeft) {
			if (isFightingWithBoss) {
				if (aniId != ANIMATIONS::WALKUP) {
					this->direction = DIRECTIONS::UP;
					this->animations->Start(ANIMATIONS::WALKUP);
				}
				this->wVelocity->x = -0.1;
				this->wVelocity->y = 0;
			}
			else {
				if (aniId != ANIMATIONS::WALKLEFT) {
					this->direction = DIRECTIONS::LEFT;
					this->wVelocity->x = -0.1;
					this->wVelocity->y = 0;
					this->animations->Start(ANIMATIONS::WALKLEFT);
				}
			}	
		}


		// ============= IDLE ========================
		if (!keyRight && !keyLeft & !keyUp && !keyDown) {
			this->wVelocity->x = 0;
			this->wVelocity->y = 0;
			if (direction == DIRECTIONS::DOWN) {
				this->animations->Start(ANIMATIONS::IDLEDOWN);
			}
			if (direction == DIRECTIONS::UP) {
				this->animations->Start(ANIMATIONS::IDLEUP);
			}
			if (direction == DIRECTIONS::RIGHT) {
				this->animations->Start(ANIMATIONS::IDLERIGHT);
			}
			if (direction == DIRECTIONS::LEFT) {
				this->animations->Start(ANIMATIONS::IDLELEFT);
			}
		}

		//  ============= SHOOT  ========================
		if (keyZ && delaytime  == 0) {
			if (direction == DIRECTIONS::UP) {
				D3DXVECTOR2 pos = this->GetCollisionBoxCenter();
				LPJASON2BULLET bullet = new Jason2Bullet(Jason2Bullet::DIRECTIONS::UP, pos.x - 1, pos.y-20);
				bullet->FlyUp();
				bullets.push_back(bullet);
			}
			else
			if (direction == DIRECTIONS::DOWN) {
				D3DXVECTOR2 pos = this->GetCollisionBoxCenter();
				LPJASON2BULLET bullet = new Jason2Bullet(Jason2Bullet::DIRECTIONS::DOWN, pos.x - 1, pos.y);
				bullet->FlyDown();
				bullets.push_back(bullet);
			}
			else
			if (direction == DIRECTIONS::LEFT) {
				D3DXVECTOR2 pos = this->GetCollisionBoxCenter();
				LPJASON2BULLET bullet = new Jason2Bullet(Jason2Bullet::DIRECTIONS::LEFT, pos.x - 10, pos.y - 10);
				bullet->FlyLeft();
				bullets.push_back(bullet);
			}
			else 
			if (direction == DIRECTIONS::RIGHT) {
				D3DXVECTOR2 pos = this->GetCollisionBoxCenter();
				LPJASON2BULLET bullet = new Jason2Bullet(Jason2Bullet::DIRECTIONS::RIGHT, pos.x + 10, pos.y - 10);
				bullet->FlyRight();
				bullets.push_back(bullet);
			}
		}	
	}
}

void Jason2::DoActionOnCollision(int nx, int ny, Object* obj)
{
}

void Jason2::GoToBoss()
{
	this->wPosition->x = 1700 -10;
	this->wPosition->y = 1150;

	Global::GetInstance()->_Camera->Free();
	Global::GetInstance()->_Camera->SetCenter(D3DXVECTOR2(1730, 1100));

	this->isFightingWithBoss = true;
	this->direction = DIRECTIONS::UP;
	this->animations->Start(ANIMATIONS::IDLEUP);
	
}

void Jason2::HP(int damage)
{
	this->hp -= damage;
}

void Jason2::SetIsHurt(bool isHurt)
{
	this->isHurt = isHurt;
}

void Jason2::SetIsPassMission(bool isPass)
{
	this->isPassMission = isPass;
}

void Jason2::SetIsFightingWithBoss(bool isfighting)
{
	this->isFightingWithBoss = isfighting;
}




bool Jason2::GetIsPassMission()
{
	return isPassMission;
}

bool Jason2::GettIsHurt()
{
	return isHurt;
}

std::vector<LPOBJECT>* Jason2::GetListObjectBullets()
{
	std::vector<LPOBJECT>* objects = new std::vector<LPOBJECT>();
	for (int i = 0; i < bullets.size(); i++)
	{
		if (bullets.at(i)->IsExist()) {
			objects->push_back(bullets.at(i));
		}	
	}
	return objects;
}

bool Jason2::GetIsFightingWithBoss()
{
	return isFightingWithBoss;
}

RECT Jason2::GetCollisionBox()
{
	RECT r;
	r.left = wPosition->x - 0;
	r.right = wPosition->x + 22;
	r.top = wPosition->y + 20;
	r.bottom = wPosition->y + 32;

	return r;
}

D3DXVECTOR2 Jason2::GetCollisionBoxCenter()
{
	RECT r = GetCollisionBox();
	return D3DXVECTOR2((r.left + r.right) / 2, (r.top + r.bottom) / 2);
}

Jason2* Jason2::GetInstance()
{
	if (_instance == NULL) _instance = new Jason2();
	return _instance;
}

