#include "Car.h"


Car* Car::_instance = nullptr;


Car::Car()
{
	

}

void Car::Init()
{
	this->isExist = true;
	this->objType = Object::TYPEOBJECT::CAR;
	this->isControlling = true;
	this->isPhysical = true;
	this->isCollision = true;
	this->isInDoor = false;
	this->isOnBrick = false;
	this->direction = -1;
	this->wPosition = new D3DXVECTOR2(1112, 1135);

	wheelAnchorVelocity = new D3DXVECTOR2(0, 0);
	wheelAnchorPoint = new D3DXVECTOR2(this->wPosition->x, this->wPosition->y);

	this->_body = new CarBody(this->GetPosition());
	this->_gun = new CarGun(this->_body->GetPosition());
	this->_head = new CarHead(this->_body->GetPosition());

	this->_wheelleft = new CarWheelLeft(wheelAnchorPoint);
	this->_wheellright = new CarWheelRight(wheelAnchorPoint);
}



void Car::Update(DWORD dt, vector<LPOBJECT>* objs, vector<LPDOOR>* doors)
{
	//DebugOut(L"x %f | y %f\n", wheelAnchorPoint->x, wheelAnchorPoint->y);
	//DebugOut(L"car  l: %d  t: %d  r: %d b: %d\n", GetCollisionBox().left, GetCollisionBox().top, GetCollisionBox().right, GetCollisionBox().bottom);

	KeyEvents();

	if (isExist) {

		PhysicalCalculate(dt);

		// thoi gia de nhap nhay khi bi tong thunog (moi 100ms)
		this->t += dt;
		// bi ton thuong
		if (isHurt) {
			hurtime += dt;
			if (hurtime > CAR_HURT_TIME) {
				hurtime = 0;
				isHurt = false;
			}
		}


		// khi bắt đầu rơi xuống -> cho bánh xe co lên
		if (this->wVelocity->y > 0) {
			this->Down();
		}

		// khởi tạo trạng thái không di trên đá, sau khi xư lý collision sẽ xét lại có dang đứng trên đá không
		this->isOnBrick = false;

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


		// tính toán co lên, dãn xuống cho bánh xe khi JUMP
		this->wheelAnchorDistance += wheelAnchorVelocity->y * dt;
		if (wheelAnchorDistance > 5) {
			wheelAnchorDistance = 5;
		}
		else
		if (wheelAnchorDistance < 0) {
			wheelAnchorDistance = 0;
		}
		this->wheelAnchorPoint->x = this->wPosition->x;
		this->wheelAnchorPoint->y = this->wPosition->y + wheelAnchorDistance;


		// update các bộ phận
		this->_body->Update(dt);
		this->_gun->Update(dt);
		this->_head->Update(dt);
		this->_wheelleft->Update(dt);
		this->_wheellright->Update(dt);

		// Update Bullets
		if (bullets.size() > 0) {
			for each (LPCARBULLET bullet in bullets)
			{
				bullet->Update(dt, objs);
			}
		}

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
			this->isPhysical = false;
		}
		else {
			this->isCollision = true;
			this->isPhysical = true;
		}
		
	}
}

void Car::KeyEvents()
{
	if (isControlling) {
		LPKEYBOARD keyboard = Global::GetInstance()->_Keyboard;

		bool keyLeft = keyboard->IsKeyDown(DIK_LEFT);
		bool pressLeft = keyboard->IsKeyPress(DIK_LEFT);
		bool keyRight = keyboard->IsKeyDown(DIK_RIGHT);
		bool pressRight = keyboard->IsKeyPress(DIK_RIGHT);
		bool keyUp = keyboard->IsKeyDown(DIK_UP);
		bool keyDown = keyboard->IsKeyDown(DIK_DOWN);
		bool pressC = keyboard->IsKeyPress(DIK_C);
		bool pressZ = keyboard->IsKeyPress(DIK_Z);
		bool keyX = keyboard->IsKeyPress(DIK_X);
		bool keyShift = (keyboard->IsKeyPress(DIK_RSHIFT) || keyboard->IsKeyPress(DIK_LSHIFT));

		int gunId = this->_gun->GetAnimations()->GetCurrentAnimationID();
		int headId = this->_head->GetAnimations()->GetCurrentAnimationID();
		int bodyId = this->_body->GetAnimations()->GetCurrentAnimationID();
		int wheelLeftId = this->_wheelleft->GetAnimations()->GetCurrentAnimationID();
		int wheelRightId = this->_wheellright->GetAnimations()->GetCurrentAnimationID();

		if (status != STATUSES::OPENDOOR) {

			// ============= UP ========================
			if (keyUp) {
				// hướng phải
				if (direction == 1) {
					if (bodyId == CarBody::ANIMATIONS::IDLERIGHT) {
						this->_body->UpRight();
						this->_head->UpRight();
						this->_gun->UpRight();
						this->_wheelleft->SetIsShrinking(true);
						this->_wheellright->SetIsShrinking(true);
					}
				}
				else
					// hướng trái
					if (direction == -1) {
						if (bodyId == CarBody::ANIMATIONS::IDLELEFT) {
							this->_body->UpLeft();
							this->_head->UpLeft();
							this->_gun->UpLeft();
							this->_wheelleft->SetIsShrinking(true);
							this->_wheellright->SetIsShrinking(true);
						}
					}
			}
			else
			{
				// hướng phải
				if (direction == 1) {
					if (bodyId == CarBody::ANIMATIONS::UPRIGHT) {
						this->_body->DownRight();
						this->_head->DownRight();
						this->_gun->DownRight();
						this->_wheelleft->SetIsShrinking(false);
						this->_wheellright->SetIsShrinking(false);
					}
				}
				else
					// hướng trái
					if (direction == -1) {
						if (bodyId == CarBody::ANIMATIONS::UPLEFT) {
							this->_body->DownLeft();
							this->_head->DownLeft();
							this->_gun->DownLeft();
							this->_wheelleft->SetIsShrinking(false);
							this->_wheellright->SetIsShrinking(false);
						}
					}
			}


			// ============= RIGHT - LEFT ========================

			if (keyRight && keyLeft) {
				this->_body->SetIsUndulating(false);
				this->_wheelleft->Idle();
				this->_wheellright->Idle();

				this->wVelocity->x = 0.0;
			}
			else
			if (!keyRight && !keyLeft) {
				this->_body->SetIsUndulating(false);
				this->_wheelleft->Idle();
				this->_wheellright->Idle();

				this->wVelocity->x = 0.0;
			}
			else
			if (keyRight) {
				if (direction == -1) { // quay từ trái sang phải
					if (bodyId == CarBody::ANIMATIONS::IDLELEFT) {
						this->_head->RotateRight();
						this->_gun->RotateRight();
						this->_body->RotateRight();
						direction = 1;
					}
					else
						if (bodyId == CarBody::ANIMATIONS::UPLEFT && this->_body->GetAnimations()->IsLastFrame()) {
							this->_body->GetAnimations()->Start(CarHead::ANIMATIONS::UPRIGHT, 2);
							this->_head->GetAnimations()->Start(CarHead::ANIMATIONS::UPRIGHT, 2);
							this->_gun->GetAnimations()->Start(CarGun::ANIMATIONS::UPRIGHT, 2);
							direction = 1;

						}
				}

				this->_body->SetIsUndulating(true);
				this->_wheelleft->WalkRight();
				this->_wheellright->WalkRight();

				this->wVelocity->x = 0.1;
			}
			else
			if (keyLeft) {
				// body
				if (direction == 1) { // quay từ phải sang trái
					if (bodyId == CarBody::ANIMATIONS::IDLERIGHT) {
						this->_head->RotateLeft();
						this->_gun->RotateLeft();
						this->_body->RotateLeft();
						direction = -1;
					}
					else
						if (bodyId == CarBody::ANIMATIONS::UPRIGHT && this->_body->GetAnimations()->IsLastFrame()) {
							this->_body->GetAnimations()->Start(CarHead::ANIMATIONS::UPLEFT, 2);
							this->_head->GetAnimations()->Start(CarHead::ANIMATIONS::UPLEFT, 2);
							this->_gun->GetAnimations()->Start(CarGun::ANIMATIONS::UPLEFT, 2);
							direction = -1;
						}
				}

				// wheel
				this->_body->SetIsUndulating(true);
				this->_wheelleft->WalkLeft();
				this->_wheellright->WalkLeft();

				this->wVelocity->x = -0.1;
			}



			// ============= JUMP  ========================
			if (keyX) {
				if (this->isOnBrick == true && status != STATUSES::JUMP && status != STATUSES::OPENDOOR) {
					Jump();
				}
			}


			//  ============= SHOOT  ========================
			if (pressZ) {
				if ((_head->GetAnimations()->GetCurrentAnimationID() == CarHead::ANIMATIONS::UPLEFT || _head->GetAnimations()->GetCurrentAnimationID() == CarHead::ANIMATIONS::UPRIGHT) && _head->GetAnimations()->GetCurrentAnimation()->IsDone()) {
					if (direction == 1) {
						D3DXVECTOR2 pos = this->GetCollisionBoxCenter();
						LPCARBULLET bullet = new CarBullet(pos.x + -8, pos.y -15 );
						bullet->FlyUp();
						bullets.push_back(bullet);
					}
					else
					if (direction == -1) {
						D3DXVECTOR2 pos = this->GetCollisionBoxCenter();
						LPCARBULLET bullet = new CarBullet(pos.x + 2, pos.y - 15 );
						bullet->FlyUp();
						bullets.push_back(bullet);
					}
				}
				else {
					if (direction == 1) {	
						D3DXVECTOR2 pos = this->GetCollisionBoxCenter();
						LPCARBULLET bullet = new CarBullet(pos.x + 5 , pos.y - 7);
						bullet->FlyRight();
						bullets.push_back(bullet);
					}
					else
					if (direction == -1) {
						D3DXVECTOR2 pos = this->GetCollisionBoxCenter();
						LPCARBULLET bullet = new CarBullet(pos.x - 5, pos.y - 7);
						bullet->FlyLeft();
						bullets.push_back(bullet);
					}
				}
				
			}
		}
	}	
}

void Car::PhysicalCalculate(DWORD dt)
{
	if (isPhysical) {
		this->wVelocity->y += (Global::_G) * dt;
	}
}

void Car::DoActionOnCollision(int nx, int ny, LPOBJECT obj)
{
	if (obj->GetTypeObj() == TYPEOBJECT::BRICK) {
		if (ny == -1) {
			this->isOnBrick = true;
			if (status == STATUSES::JUMP) {	
				Idle();			
			}	
		}
	}
	if (obj->GetTypeObj() == TYPEOBJECT::LAVA) {
		if (Car::GetInstance()->GettIsHurt() == false) {
			Car::GetInstance()->SetIsHurt(true);
			Car::GetInstance()->HP(1);
		}
	}
}

void Car::Render()
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

			this->_body->Render(0.7 * flag + 0.3);
			this->_gun->Render(0.7 * flag + 0.3);
			this->_head->Render(0.7 * flag + 0.3);
			this->_wheelleft->Render(0.7 * flag + 0.3);
			this->_wheellright->Render(0.7 * flag + 0.3);
		}
		else {
			this->_body->Render();
			this->_gun->Render();
			this->_head->Render();
			this->_wheelleft->Render();
			this->_wheellright->Render();
		}
	}


	// Bullets
	if (bullets.size() > 0) {
		for each (LPCARBULLET bullet in bullets)
		{
			bullet->Render();
		}
	}
}

void Car::HP(int damage)
{
	this->hp -= damage;
}

void Car::SetIsHurt(bool isHurt)
{
	this->isHurt = isHurt;
}

bool Car::GettIsHurt()
{
	return isHurt;
}

void Car::Jump()
{
	this->status = STATUSES::JUMP;
	this->wVelocity->y = -0.27;
	this->wheelAnchorVelocity->y = 0.1;
}

void Car::Down()
{
	this->status = STATUSES::DOWN;
	this->wheelAnchorVelocity->y = -0.1;
}


void Car::Idle()
{
	this->status = STATUSES::IDLE;
}

void Car::OpenDoor()
{
	if (status != STATUSES::OPENDOOR && status != STATUSES::CLOSEDOOR) {
		status = STATUSES::OPENDOOR;
		if (direction == 1) {
			this->_head->OpenDoorRight();	
		}
		else
		if (direction == -1) {
			this->_head->OpenDoorLeft();
		}
	}
}

void Car::CloseDoor()
{
	if (status != STATUSES::CLOSEDOOR && status != STATUSES::OPENDOOR) {
		status = STATUSES::CLOSEDOOR;
		if (direction == 1) {
			this->_head->CloseDoorRight();
			this->_body->SetIsUndulating(false);
			this->_wheelleft->Idle();
			this->_wheellright->Idle();
			this->wVelocity->x = 0.0;
		}
		else
		if (direction == -1) {
			this->_head->CloseDoorLeft();
			this->_body->SetIsUndulating(false);
			this->_wheelleft->Idle();
			this->_wheellright->Idle();
			this->wVelocity->x = 0.0;
		}
	}
}

void Car::SetIsControlling(bool isControlling)
{
	this->isControlling = isControlling;
}



bool Car::IsControlling()
{
	return isControlling;
}

RECT Car::GetCollisionBox()
{
	RECT r;
	r.left = wPosition->x + -6;
	r.right = wPosition->x + 14;
	r.top = wPosition->y + -8;
	r.bottom = wPosition->y + 9;
	return r;
}

D3DXVECTOR2 Car::GetCollisionBoxCenter()
{
	RECT r = GetCollisionBox();
	return D3DXVECTOR2((r.left + r.right) / 2, (r.top + r.bottom) / 2);
}

Car* Car::GetInstance()
{
	if (_instance == NULL) _instance = new Car();
	return _instance;
}

Car::~Car()
{
}
