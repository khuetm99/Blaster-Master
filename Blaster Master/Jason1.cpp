#include "Jason1.h"


Jason1::Jason1(float x, float y)
{
	this->isExist = false;
	this->isControlling = false;
	this->isPhysical = false;
	this->isCollision = false;
	this->SetBottomPostion(D3DXVECTOR2(x,y));
	this->direction = -1;

	////texture trái
	//LPTEXTURE tex = new Texture(L"textures/BlasterMaster.png", D3DCOLOR_XRGB(0, 57, 115));
	//LPDIRECT3DTEXTURE9 d3dtex = tex->LPDIRECT3DTEXTURE();
	////texture phải
	//LPTEXTURE texR = new Texture(L"textures/BlasterMaster1.png", D3DCOLOR_XRGB(0, 57, 115));
	//LPDIRECT3DTEXTURE9 d3dtexR = texR->LPDIRECT3DTEXTURE();

	LPDIRECT3DTEXTURE9 d3dtex = Textures::GetInstance()->GetDirect3DTexture(Textures::TEXTURES::CHARACTERLEFT);
	LPDIRECT3DTEXTURE9 d3dtexR = Textures::GetInstance()->GetDirect3DTexture(Textures::TEXTURES::CHARACTERRIGHT);


	for (int i = 0; i < ANIMATIONS::_LENGHT; i++)
	{
		switch (i)
		{
			case ANIMATIONS::IDLERIGHT: {
				//đứng yên phải
				Animation* ani = new Animation();
				ani->Add(new Sprite(399, 30, 407, 46, d3dtexR), 100);
				this->animations->Add(ani);
				ani->Repeat(true);
				break;
			}
			case ANIMATIONS::IDLELEFT: {
				// đứng yên trái
				Animation* ani = new Animation();
				ani->Add(new Sprite(3, 30, 11, 46, d3dtex), 100);
				this->animations->Add(ani);
				ani->Repeat(true);
				break;
			}
			case ANIMATIONS::WALKRIGHT: {
				// Đi phải
				Animation* ani = new Animation();
				ani->Add(new Sprite(390, 31, 398, 46, d3dtexR), 100);
				ani->Add(new Sprite(381, 30, 389, 46, d3dtexR), 100);
				ani->Add(new Sprite(372, 31, 380, 46, d3dtexR), 100);
				ani->Add(new Sprite(381, 30, 389, 46, d3dtexR), 100);
				this->animations->Add(ani);
				ani->Repeat(true);
				break;
			}
			case ANIMATIONS::WALKLEFT: {
				// Đi trái
				Animation* ani = new Animation();
				ani->Add(new Sprite(12, 31, 20, 46, d3dtex), 100);
				ani->Add(new Sprite(21, 30, 29, 46, d3dtex), 100);
				ani->Add(new Sprite(30, 31, 38, 46, d3dtex), 100);
				ani->Add(new Sprite(21, 30, 29, 46, d3dtex), 100);
				this->animations->Add(ani);
				ani->Repeat(true);
				break;
			}
			case ANIMATIONS::CRAWLRIGHT: {
				// Bò phải
				Animation* ani = new Animation();
				ani->Add(new Sprite(374, 47, 389, 55, d3dtexR), D3DXVECTOR2(-4, 8), 200);
				ani->Add(new Sprite(392, 47, 407, 55, d3dtexR), D3DXVECTOR2(-4, 8), 200);
				this->animations->Add(ani);
				ani->Repeat(true);
				break;
			}
			case ANIMATIONS::CRAWLLEFT: {
				// Bò trái
				Animation* ani = new Animation();
				ani->Add(new Sprite(21, 47, 36, 55, d3dtex), D3DXVECTOR2(-3, 8), 200);
				ani->Add(new Sprite(3, 47, 18, 55, d3dtex), D3DXVECTOR2(-3, 8), 200);
				this->animations->Add(ani);
				ani->Repeat(true);
				break;
			}
			case ANIMATIONS::JUMPRIGHT: {
				// Nhảy phải
				Animation* ani = new Animation();
				ani->Add(new Sprite(390, 31, 398, 46, d3dtexR), 50);
				this->animations->Add(ani);
				break;
			}
			case ANIMATIONS::JUMPLEFT: {
				// Nhảy trái
				Animation* ani = new Animation();
				ani->Add(new Sprite(12, 31, 20, 46, d3dtex), 50);
				this->animations->Add(ani);
				break;
			}
			case ANIMATIONS::DIERIGHT: {
				// Chết phải
				Animation* ani = new Animation();
				ani->Add(new Sprite(393, 64, 406, 80, d3dtexR), 100);
				ani->Add(new Sprite(374, 65, 390, 78, d3dtexR), 100);
				ani->Add(new Sprite(358, 64, 371, 80, d3dtexR), 100);
				ani->Add(new Sprite(340, 66, 356, 79, d3dtexR), 100);
				ani->Add(new Sprite(393, 64, 406, 80, d3dtexR), 100);
				ani->Add(new Sprite(374, 65, 390, 78, d3dtexR), 100);
				ani->Add(new Sprite(358, 64, 371, 80, d3dtexR), 100);
				ani->Add(new Sprite(340, 66, 356, 79, d3dtexR), 100);
				ani->Add(new Sprite(393, 64, 406, 80, d3dtexR), 100);
				ani->Add(new Sprite(374, 65, 390, 78, d3dtexR), 100);
				ani->Add(new Sprite(358, 64, 371, 80, d3dtexR), 100);
				ani->Add(new Sprite(340, 66, 356, 79, d3dtexR), 100);
				ani->Add(new Sprite(393, 64, 406, 80, d3dtexR), 1000);
				ani->Add(new Sprite(392, 83, 407, 97, d3dtexR), 300);
				ani->Add(new Sprite(374, 89, 390, 97, d3dtexR), 500);
				this->animations->Add(ani);
				break;
			}
			case ANIMATIONS::DIELEFT: {
				// Chết trái
				Animation* ani = new Animation();
				ani->Add(new Sprite(4, 64, 17, 80, d3dtex), 100);
				ani->Add(new Sprite(20, 65, 36, 78, d3dtex), 100);
				ani->Add(new Sprite(39, 64, 52, 80, d3dtex), 100);
				ani->Add(new Sprite(54, 66, 70, 79, d3dtex), 100);
				ani->Add(new Sprite(4, 64, 17, 80, d3dtex), 100);
				ani->Add(new Sprite(20, 65, 36, 78, d3dtex), 100);
				ani->Add(new Sprite(39, 64, 52, 80, d3dtex), 100);
				ani->Add(new Sprite(54, 66, 70, 79, d3dtex), 100);
				ani->Add(new Sprite(4, 64, 17, 80, d3dtex), 100);
				ani->Add(new Sprite(20, 65, 36, 78, d3dtex), 100);
				ani->Add(new Sprite(39, 64, 52, 80, d3dtex), 100);
				ani->Add(new Sprite(54, 66, 70, 79, d3dtex), 100);
				ani->Add(new Sprite(4, 64, 17, 80, d3dtex), 1000);
				ani->Add(new Sprite(3, 83, 18, 97, d3dtex), 300);
				ani->Add(new Sprite(20, 89, 36, 97, d3dtex), 500);
				this->animations->Add(ani);
				break;
			}
			case ANIMATIONS::JUMPOUTCARRIGHT: {
				// Nhảy khỏi xe bên phải
				Animation* ani = new Animation();
				ani->Add(new Sprite(390, 31, 398, 46, d3dtexR), 400);
				ani->Add(new Sprite(399, 30, 407, 46, d3dtexR), 200);
				this->animations->Add(ani);
				break;
			}
			case ANIMATIONS::JUMPOUTCARLEFT: {
				// Nhảy khỏi xe bên trái
				Animation* ani = new Animation();
				ani->Add(new Sprite(12, 31, 20, 46, d3dtex), 400);
				ani->Add(new Sprite(3, 30, 11, 46, d3dtex), 200);
				this->animations->Add(ani);
				break;
			}
			case ANIMATIONS::JUMPINCARRIGHT: {
				// Nhảy vào xe bên phải
				Animation* ani = new Animation();
				ani->Add(new Sprite(399, 30, 407, 46, d3dtexR), 200);
				ani->Add(new Sprite(390, 31, 398, 46, d3dtexR), 400);
				this->animations->Add(ani);
				break;
			}
			case ANIMATIONS::JUMPINCARLEFT: {
				// Nhảy vào xe bên trái
				Animation* ani = new Animation();
				ani->Add(new Sprite(3, 30, 11, 46, d3dtex), 200);
				ani->Add(new Sprite(12, 31, 20, 46, d3dtex), 400);
				this->animations->Add(ani);
				break;
			}
		}
	}

	this->animations->Start(ANIMATIONS::IDLELEFT);
}

void Jason1::Update(DWORD dt, vector<LPOBJECT>* objs, vector<LPDOOR>* doors)
{
	//DebugOut(L"w: %f | h: %f\n", width, height);
	//DebugOut(L"bottom: %f  %f\n", GetBottomPostion().x, GetBottomPostion().y);
	//DebugOut(L"ani: %d \n", animations->GetCurrentAnimationID());
	//DebugOut(L"vx: %f \n",this->wVelocity->x);
	//DebugOut(L"l: %d  t: %d  r: %d b: %d\n", GetCollisionBox().left, GetCollisionBox().top, GetCollisionBox().right, GetCollisionBox().bottom);

	KeyEvents();
	
	if (isExist) {
		
		PhysicalCalculate(dt);

		
		// khi đã vào xe
		if (this->status == STATUSES::INTOCAR && this->wVelocity->y >= 0.1) {
			this->isExist = false;
			this->isCollision = false;
			this->isPhysical = false;
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
							this->wVelocity->x = 0.0f;
							this->wAcceleration->x = 0.0f;
							this->isImpacted_X = true;
						}

						if (coEventsResult.at(i)->ny != 0) {
							wPosition->y = this->wPosition->y + this->wVelocity->y * dt * min_ty;
							this->wVelocity->y = 0.0f;
							this->wAcceleration->y = 0.0f;
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
	
	// Bullets
	if (bullets.size() > 0) {
		for each (LPJASON1BULLET bullet in bullets)
		{
			bullet->Update(dt, objs);
		}
	}
}

void Jason1::PhysicalCalculate(DWORD dt)
{
	if (isPhysical) {
		this->wVelocity->y += (Global::_G + wAcceleration->y) * dt;
	}
}

void Jason1::Render()
{
	/*if (tex->LPDIRECT3DTEXTURE() == nullptr) {
		tex = new Texture(L"textures/bbox.png", D3DCOLOR_XRGB(255, 255, 255));
	}
	LPDIRECT3DTEXTURE9 d3dtex = tex->LPDIRECT3DTEXTURE();

	D3DXVECTOR2 pos = D3DXVECTOR2(GetCollisionBox().left, GetCollisionBox().top);
	D3DXVECTOR3 p(Global::GetInstance()->_Camera->Convert(pos).x, Global::GetInstance()->_Camera->Convert(pos).y, 0);
	Global::GetInstance()->_SpriteHandler->Draw(d3dtex, &GetCollisionBox(), NULL, &p, D3DCOLOR_ARGB(255, 255, 255, 255));*/


	// Animations
	if (isExist == true && animations != nullptr) {
		this->animations->Render(*wPosition);
	}

	// Bullets
	if (bullets.size() > 0) {
		for each (LPJASON1BULLET bullet in bullets)
		{
			bullet->Render();
		}
	}
}

void Jason1::KeyEvents()
{
	LPKEYBOARD keyboard = Global::GetInstance()->_Keyboard;

	bool keyLeft = keyboard->IsKeyDown(DIK_LEFT);
	bool pressLeft = keyboard->IsKeyPress(DIK_LEFT);
	bool keyRight = keyboard->IsKeyDown(DIK_RIGHT);
	bool pressRight = keyboard->IsKeyPress(DIK_RIGHT);
	bool keyUp = keyboard->IsKeyDown(DIK_UP);
	bool keyDown = keyboard->IsKeyDown(DIK_DOWN);
	bool keyC = keyboard->IsKeyPress(DIK_C);
	bool pressZ = keyboard->IsKeyPress(DIK_Z);
	bool keyX = keyboard->IsKeyPress(DIK_X);
	bool keyShift = (keyboard->IsKeyPress(DIK_RSHIFT) || keyboard->IsKeyPress(DIK_LSHIFT));

	int aniId = this->animations->GetCurrentAnimationID();

	if (isControlling) {
		if (status != STATUSES::INTOCAR) {

			// ============= UP ========================
			if (keyUp && keyDown){}
			else
			if (!keyUp && !keyDown) {}
			else
			if (keyUp) {
				if ( aniId == ANIMATIONS::CRAWLLEFT || aniId == ANIMATIONS::CRAWLRIGHT) {
					if (direction == 1) {
						this->status = STATUSES::STAND;
						this->animations->Start(ANIMATIONS::IDLERIGHT);
					}
					else
					if (direction == -1) {
						this->status = STATUSES::STAND;
						this->animations->Start(ANIMATIONS::IDLELEFT);
					}
				}
			}
			else
			if (keyDown){
				if (aniId == ANIMATIONS::IDLELEFT || aniId == ANIMATIONS::IDLERIGHT || aniId == ANIMATIONS::WALKLEFT || aniId == ANIMATIONS::WALKRIGHT) {
					if (direction == 1) {
						this->status = STATUSES::CRAWL;
						this->animations->Start(ANIMATIONS::CRAWLRIGHT);
						this->animations->Pause();
					}
					else
					if (direction == -1) {
						this->status = STATUSES::CRAWL;
						this->animations->Start(ANIMATIONS::CRAWLLEFT);
						this->animations->Pause();
					}
				}
			}


			// ============= RIGHT - LEFT ========================
			if ((!keyRight && !keyLeft) || (keyRight && keyLeft)) {
				this->wVelocity->x = 0;
				if (aniId == ANIMATIONS::WALKLEFT || aniId == ANIMATIONS::WALKRIGHT) {
					if (direction == 1) {
						this->status = STATUSES::STAND;
						this->animations->Start(ANIMATIONS::IDLERIGHT);
					}
					else
					if (direction == -1) {
						this->wVelocity->x = 0;
						this->status = STATUSES::STAND;
						this->animations->Start(ANIMATIONS::IDLELEFT);
					}
				}
				else
				if (aniId == ANIMATIONS::CRAWLLEFT || aniId == ANIMATIONS::CRAWLRIGHT) {
					this->animations->Pause();
				}
			}
			else
			if (keyRight) {
				if (aniId == ANIMATIONS::IDLELEFT || aniId == ANIMATIONS::IDLERIGHT) {
					this->direction = 1;			
					this->wVelocity->x = 0.06;
					this->status = STATUSES::STAND;
					this->animations->Start(ANIMATIONS::WALKRIGHT);
				}
				else
				if (aniId == ANIMATIONS::CRAWLLEFT || aniId == ANIMATIONS::CRAWLRIGHT) {
					this->status = STATUSES::CRAWL;
					this->wVelocity->x = 0.03;
					if (direction == -1) {	
						this->animations->Restart(ANIMATIONS::CRAWLRIGHT);
					}
					else
					if (direction == 1) {
						this->animations->Resume(1);
					}
					this->direction = 1;
				}
				else
				if (aniId == ANIMATIONS::JUMPLEFT || aniId == ANIMATIONS::JUMPRIGHT) {
					this->direction = 1;			
					this->wVelocity->x = 0.08;
					this->animations->Start(ANIMATIONS::JUMPRIGHT);
				}
			}
			else
			if (keyLeft) {
				if (aniId == ANIMATIONS::IDLELEFT || aniId == ANIMATIONS::IDLERIGHT) {
					this->direction = -1;
					this->wVelocity->x = -0.06;
					this->status = STATUSES::STAND;
					this->animations->Start(ANIMATIONS::WALKLEFT);
				}	
				else
				if (aniId == ANIMATIONS::CRAWLLEFT || aniId == ANIMATIONS::CRAWLRIGHT) {
					this->status = STATUSES::CRAWL;
					this->wVelocity->x = -0.03;
					if (direction == 1) {
						this->animations->Restart(ANIMATIONS::CRAWLLEFT);
					}
					else
					if (direction == -1) {
						this->animations->Resume(1);
					}
					this->direction = -1;
				}
				else
				if (aniId == ANIMATIONS::JUMPLEFT || aniId == ANIMATIONS::JUMPRIGHT) {
					this->direction = -1;			
					this->wVelocity->x = -0.08;
					this->animations->Start(ANIMATIONS::JUMPLEFT);
				}
			}



			// ============= JUMP  ========================
			if (keyX) {
				if (aniId != ANIMATIONS::JUMPLEFT && aniId != ANIMATIONS::JUMPRIGHT && aniId != ANIMATIONS::CRAWLLEFT && aniId != ANIMATIONS::CRAWLRIGHT) {
					this->wVelocity->y = -0.15;
					this->status = STATUSES::JUMP;
					if (direction == 1) {
						this->animations->Start(ANIMATIONS::JUMPRIGHT);
					}
					else
					if (direction == -1) {
						this->animations->Start(ANIMATIONS::JUMPLEFT);
					}
				}
			}


			//  ============= SHOOT  ========================
			if (pressZ) {
				if (direction == 1) {
					D3DXVECTOR2 pos = this->GetCollisionBoxCenter();
					LPJASON1BULLET bullet = new Jason1Bullet(pos.x - 1 , pos.y);
					bullet->FlyRight();
					bullets.push_back(bullet);
				}
				else
				if (direction == -1) {
					D3DXVECTOR2 pos = this->GetCollisionBoxCenter();
					LPJASON1BULLET bullet = new Jason1Bullet(pos.x + 1, pos.y);
					bullet->FlyLeft();
					bullets.push_back(bullet);
				}
			}
		}	
	}
}

void Jason1::IntoCar(D3DXVECTOR2 center)
{
	if (direction == 1) {
		this->animations->Restart(ANIMATIONS::JUMPRIGHT);
		this->status = STATUSES::INTOCAR;
		this->wPosition->x = center.x - 5;
		this->wVelocity->y = -0.11;
	}
	else
	if (direction == -1) {
		this->animations->Restart(ANIMATIONS::JUMPLEFT);
		this->status = STATUSES::INTOCAR;
		this->wPosition->x = center.x - 5;
		this->wVelocity->y = -0.11;
	}

	//this->isCollision = false;
	//this->isPhysical = false;
}

void Jason1::OutCar(D3DXVECTOR2 center, int direction)
{
	this->status = STATUSES::JUMP;
	this->direction = direction;
	this->isExist = true;
	this->isPhysical = true;
	this->isCollision = true;
	this->wVelocity->y = -0.07;

	if (direction == 1) {
		this->animations->Restart(ANIMATIONS::JUMPRIGHT);
		this->wPosition->x = center.x - 5;
		this->wPosition->y = center.y - 13;
	}
	else
	if (direction == -1) {
		this->animations->Restart(ANIMATIONS::JUMPLEFT);
		this->wPosition->x = center.x - 5;
		this->wPosition->y = center.y - 13;
	}

	
}

void Jason1::DoActionOnCollision(int nx, int ny, Object* obj)
{
	if (obj->GetTypeObj() == TYPEOBJECT::BRICK) {
		if (ny == -1) {
			if (this->status == STATUSES::JUMP) {
				this->wVelocity->y = 0;
				this->status = STATUSES::STAND;
				if (direction == 1) {
					this->animations->Start(ANIMATIONS::IDLERIGHT);
				}
				else
				if (direction == -1) {
					this->animations->Start(ANIMATIONS::IDLELEFT);
				}
			}	
		}
	}
}

bool Jason1::GetIsPassMission()
{
	return this->isPassMission;
}

RECT Jason1::GetCollisionBox()
{
	RECT r;
	if (animations->GetCurrentAnimationID() == ANIMATIONS::CRAWLLEFT || animations->GetCurrentAnimationID() == ANIMATIONS::CRAWLRIGHT) {
		r.left = wPosition->x - 1;
		r.right = wPosition->x + 10;
		r.top = wPosition->y + 7;
		r.bottom = wPosition->y + 16;
	}
	else {
		r.left = wPosition->x - 1;
		r.right = wPosition->x + 10;
		r.top = wPosition->y;
		r.bottom = wPosition->y + 16;
	}

	return r;
}

D3DXVECTOR2 Jason1::GetCollisionBoxCenter()
{
	RECT r = GetCollisionBox();
	return D3DXVECTOR2((r.left + r.right)/2 , (r.top + r.bottom) / 2);
}

bool Jason1::IsControlling()
{
	return isControlling;
}

void Jason1::SetIsControlling(bool isControlling)
{
	this->isControlling = isControlling;
}

void Jason1::SetIsPassMission(bool isPass)
{
	this->isPassMission = isPass;
}


