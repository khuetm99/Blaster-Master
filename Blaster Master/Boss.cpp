#include "Boss.h"


#pragma region ============== BossHandNode ====================
BossHandNode::BossHandNode()
{
	this->width = 16;
	this->height = 16;

	LPDIRECT3DTEXTURE9 d3dtex = Textures::GetInstance()->GetDirect3DTexture(Textures::TEXTURES::BOSS);
	for (int i = 0; i < ANIMATIONS::_LENGHT; i++)
	{
		switch (i)
		{
		case ANIMATIONS::NORMAL: // xanh la
		{
			Animation* ani = new Animation();
			ani->Add(new Sprite(142, 1129, 158, 1146, d3dtex), 100);
			ani->Add(new Sprite(165, 1129, 181, 1146, d3dtex), 100);
			ani->Add(new Sprite(188, 1129, 204, 1146, d3dtex), 100);
			this->animations->Add(ani);
			ani->Repeat(true);
			break;
		}
		case ANIMATIONS::LOWHP: // cam
		{
			Animation* ani = new Animation();
			ani->Add(new Sprite(142, 1129, 158, 1146, d3dtex), 300);
			ani->Add(new Sprite(94, 1129, 110, 1146, d3dtex), 300);
			ani->Add(new Sprite(69, 1129, 85, 1146, d3dtex), 300);
			this->animations->Add(ani);
			ani->Repeat(true);
			break;
		}
		}
	}

	this->animations->Start(ANIMATIONS::NORMAL);
}

void BossHandNode::Update(DWORD dt, vector<LPOBJECT>* objs)
{
	// het nhap nhay
	if (this->animations->GetCurrentAnimationID() == BossHandNode::ANIMATIONS::LOWHP && this->animations->GetCurrentAnimation()->IsDone()) {
		this->animations->Start(BossHandNode::ANIMATIONS::NORMAL);
	}

	this->animations->Update(dt);

}

void BossHandNode::KeyEvents()
{
}

void BossHandNode::DoActionOnCollision(int nx, int ny, LPOBJECT obj)
{
}

void BossHandNode::Render()
{/*
	if (tex->LPDIRECT3DTEXTURE() == nullptr) {
		tex = new Texture(L"textures/bbox.png", D3DCOLOR_XRGB(255, 255, 255));
	}
	LPDIRECT3DTEXTURE9 d3dtex = tex->LPDIRECT3DTEXTURE();

	D3DXVECTOR3 p(Global::GetInstance()->_Camera->Convert(*wPosition).x, Global::GetInstance()->_Camera->Convert(*wPosition).y, 0);
	Global::GetInstance()->_SpriteHandler->Draw(d3dtex, &GetCollisionBox(), NULL, &p, D3DCOLOR_ARGB(255, 255, 255, 255));*/

	this->animations->Render(*wPosition);
}

void BossHandNode::SetCenterPosstion(D3DXVECTOR2 center)
{
	this->wPosition->x = center.x - width / 2;
	this->wPosition->y = center.y - height / 2;
}

RECT BossHandNode::GetCollisionBox()
{
	RECT r;
	r.left = wPosition->x;
	r.right = wPosition->x + width;
	r.top = wPosition->y;
	r.bottom = wPosition->y + height;
	return r;
}

D3DXVECTOR2 BossHandNode::GetCollisionBoxCenter()
{
	RECT r = GetCollisionBox();
	return D3DXVECTOR2((r.left + r.right) / 2, (r.top + r.bottom) / 2);
}

BossHandNode::~BossHandNode()
{
}

#pragma endregion


#pragma region ============== BossPincerLeft ====================
BossPincerLeft::BossPincerLeft()
{
	this->zone.left = 1575;
	this->zone.top = 800;
	this->zone.right = 1895;
	this->zone.bottom = 1150;

	this->isCollision = true;
	this->wPosition->x = Boss::GetInstance()->GetPosition()->x + 100;
	this->wPosition->y = Boss::GetInstance()->GetPosition()->y;
	this->wVelocity->y = BOSS_PINCER_MOVE_SPEED;
	this->isMoving = true;


	LPDIRECT3DTEXTURE9 d3dtex = Textures::GetInstance()->GetDirect3DTexture(Textures::TEXTURES::BOSS);
	for (int i = 0; i < ANIMATIONS::_LENGHT; i++)
	{
		switch (i)
		{
		case ANIMATIONS::NORMAL: // xanh la
		{
			Animation* ani = new Animation();
			ani->Add(new Sprite(144, 1147, 162, 1179, d3dtex), 100);
			ani->Add(new Sprite(167, 1147, 185, 1179, d3dtex), 100);
			ani->Add(new Sprite(190, 1147, 208, 1179, d3dtex), 100);
			this->animations->Add(ani);
			ani->Repeat(true);
			break;
		}
		case ANIMATIONS::LOWHP: // cam
		{
			Animation* ani = new Animation();
			ani->Add(new Sprite(144, 1147, 162, 1179, d3dtex), 300);
			ani->Add(new Sprite(96, 1147, 114, 1179, d3dtex), 300);
			ani->Add(new Sprite(71, 1147, 89, 1179, d3dtex), 300);
			this->animations->Add(ani);
			//ani->Repeat(true);
			break;
		}
		}
	}
	
	this->animations->Start(ANIMATIONS::NORMAL);

	
}

BossPincerLeft::BossPincerLeft(BossPincerLeft* pincer1st)
{
	this->zone.left = 1575;
	this->zone.top = 800;
	this->zone.right = 1895;
	this->zone.bottom = 1150;
	this->pincer1st = pincer1st;
	this->isCollision = true;
	this->wPosition->x = Boss::GetInstance()->GetPosition()->x + 100 + BOSS_DISTANCE_BETWEEN_PINCERS;
	this->wPosition->y = Boss::GetInstance()->GetPosition()->y;
	this->wVelocity->y = BOSS_PINCER_MOVE_SPEED;
	this->isMoving = true;


	LPDIRECT3DTEXTURE9 d3dtex = Textures::GetInstance()->GetDirect3DTexture(Textures::TEXTURES::BOSS);
	for (int i = 0; i < ANIMATIONS::_LENGHT; i++)
	{
		switch (i)
		{
		case ANIMATIONS::NORMAL: // xanh la
		{
			Animation* ani = new Animation();
			ani->Add(new Sprite(144, 1147, 162, 1179, d3dtex), 100);
			ani->Add(new Sprite(167, 1147, 185, 1179, d3dtex), 100);
			ani->Add(new Sprite(190, 1147, 208, 1179, d3dtex), 100);
			this->animations->Add(ani);
			ani->Repeat(true);
			break;
		}
		case ANIMATIONS::LOWHP: // cam
		{
			Animation* ani = new Animation();
			ani->Add(new Sprite(96, 1147, 114, 1179, d3dtex), 100);
			ani->Add(new Sprite(121, 1147, 139, 1179, d3dtex), 100);
			this->animations->Add(ani);
			ani->Repeat(true);
			break;
		}
		}
	}

	this->animations->Start(ANIMATIONS::NORMAL);

	
}

void BossPincerLeft::Update(DWORD dt, vector<LPOBJECT>* objs)
{
	if (pincer1st == nullptr) { // la cang thu 1
		// gioi han vung di chuyen
		if (this->GetCollisionBox().left < zone.left) {
			this->wVelocity->x = BOSS_PINCER_MOVE_SPEED;
		}
		if (this->GetCollisionBox().right > zone.right) {
			this->wVelocity->x = -BOSS_PINCER_MOVE_SPEED;
		}
		if (this->GetCollisionBox().top < zone.top) {
			this->wVelocity->y = BOSS_PINCER_MOVE_SPEED;
		}
		if (this->GetCollisionBox().bottom > zone.bottom) {
			this->wVelocity->y = -BOSS_PINCER_MOVE_SPEED;
		}


		// them jason vao list object de xet collision
	

		// di chuyen trong thoi gian nhat dinh roi dung lai
		if (this->isMoving) {
			this->move_time += dt;
			if (this->move_time >= BOSS_PINCER_MOVE_TIME) {
				this->move_time = 0;
				this->isMoving = false;
				this->wVelocity->x = 0;
				this->wVelocity->y = 0;
			}
		}
		else {
			// dổi hướng di chuyển
			this->change_direction_time += dt;
			if (this->change_direction_time > BOSS_PINCER_CHANGE_DIRECTION_TIME) {
				srand(dt);
				this->wVelocity->x = (rand() % 3 - 1) * BOSS_PINCER_MOVE_SPEED; // ramdom (-1 -> 1)
				this->wVelocity->y = (rand() % 3 - 1) * BOSS_PINCER_MOVE_SPEED; // ramdom (-1 -> 1)
				if (this->wVelocity->x != 0 || this->wVelocity->y != 0) {
					this->isMoving = true;
					this->change_direction_time = 0;
				}
			}
		}

	}
	else {  // truong hop la tay thu 2 -> di chuyen giong tay thu nhat
		this->wVelocity->x = pincer1st->GetVelocity().x;
		this->wVelocity->y = pincer1st->GetVelocity().y;

		wPosition->x += (int)(this->wVelocity->x * dt);
		wPosition->y += (int)(this->wVelocity->y * dt);
	}

	// het nhap nhay
	if (this->animations->GetCurrentAnimationID() == BossPincerLeft::ANIMATIONS::LOWHP && this->animations->GetCurrentAnimation()->IsDone()) {
		this->animations->Start(BossPincerLeft::ANIMATIONS::NORMAL);
	}


	// xu ly va cham
	if (isCollision) {
		// them jason2 vao list object de xet va cham
		objs->push_back(Jason2::GetInstance());

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
				/*if (coEventsResult.at(i)->obj->GetTypeObj() == TYPEOBJECT::BRICK) {
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

				}*/

				DoActionOnCollision(nx, ny, coEventsResult.at(i)->obj);
			}

			for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
		}
	}
	else {
		wPosition->x += (int)(this->wVelocity->x * dt);
		wPosition->y += (int)(this->wVelocity->y * dt);
	}
	
}

void BossPincerLeft::KeyEvents()
{
}

void BossPincerLeft::DoActionOnCollision(int nx, int ny, LPOBJECT obj)
{
	if (obj->GetTypeObj() == TYPEOBJECT::BRICK) {
		if (nx != 0) {
			if (nx == 1) {
				this->wVelocity->x = BOSS_PINCER_MOVE_SPEED;
			}
			else
			if (nx == -1) {
				this->wVelocity->x = -BOSS_PINCER_MOVE_SPEED;
			}
		}

		if (ny != 0) {
			if (ny == 1) {
				this->wVelocity->y = BOSS_PINCER_MOVE_SPEED;
			}
			else
			if (ny == -1) {
				this->wVelocity->y = -BOSS_PINCER_MOVE_SPEED;
			}
		}
	}

	if (obj->GetTypeObj() == TYPEOBJECT::JASON2) {
		if (Jason2::GetInstance()->GettIsHurt() == false) {
			Jason2::GetInstance()->SetIsHurt(true);
			Jason2::GetInstance()->HP(1);
		}	
	}
}

void BossPincerLeft::Render()
{
	/*if (tex->LPDIRECT3DTEXTURE() == nullptr) {
		tex = new Texture(L"textures/bbox.png", D3DCOLOR_XRGB(255, 255, 255));
	}
	LPDIRECT3DTEXTURE9 d3dtex = tex->LPDIRECT3DTEXTURE();

	D3DXVECTOR3 p(Global::GetInstance()->_Camera->Convert(*wPosition).x, Global::GetInstance()->_Camera->Convert(*wPosition).y, 0);
	Global::GetInstance()->_SpriteHandler->Draw(d3dtex, &GetCollisionBox(), NULL, &p, D3DCOLOR_ARGB(255, 255, 255, 255));*/


	this->animations->Render(*wPosition);
}

RECT BossPincerLeft::GetCollisionBox()
{
	RECT r;
	r.left = this->wPosition->x;
	r.right = this->wPosition->x + 18;
	r.top = this->wPosition->y;
	r.bottom = this->wPosition->y + 30;
	return r;
}

D3DXVECTOR2 BossPincerLeft::GetCollisionBoxCenter()
{
	RECT r = GetCollisionBox();
	return D3DXVECTOR2((r.left + r.right) / 2, (r.top + r.bottom) / 2);
}

BossPincerLeft::~BossPincerLeft()
{

}

#pragma endregion


#pragma region ============== BossPincerRight ====================
BossPincerRight::BossPincerRight()
{
	this->zone.left = 1575;
	this->zone.top = 800;
	this->zone.right = 1895;
	this->zone.bottom = 1150;

	this->isCollision = true;
	this->wPosition->x = Boss::GetInstance()->GetPosition()->x - 50;
	this->wPosition->y = Boss::GetInstance()->GetPosition()->y;
	this->wVelocity->y = BOSS_PINCER_MOVE_SPEED;
	this->isMoving = true;


	LPDIRECT3DTEXTURE9 d3dtex = Textures::GetInstance()->GetDirect3DTexture(Textures::TEXTURES::BOSS);
	for (int i = 0; i < ANIMATIONS::_LENGHT; i++)
	{
		switch (i)
		{
		case ANIMATIONS::NORMAL: // xanh la
		{
			Animation* ani = new Animation();
			ani->Add(new Sprite(264, 1147, 282, 1179, d3dtex), 100);
			ani->Add(new Sprite(241, 1147, 259, 1179, d3dtex), 100);
			ani->Add(new Sprite(218, 1147, 236, 1179, d3dtex), 100);
			this->animations->Add(ani);
			ani->Repeat(true);
			break;
		}
		case ANIMATIONS::LOWHP: // cam
		{
			Animation* ani = new Animation();
			ani->Add(new Sprite(264, 1147, 282, 1179, d3dtex), 300);
			ani->Add(new Sprite(312, 1147, 330, 1179, d3dtex), 300);
			ani->Add(new Sprite(337, 1147, 355, 1179, d3dtex), 300);
			this->animations->Add(ani);
			//ani->Repeat(true);
			break;
		}
		}
	}

	this->animations->Start(ANIMATIONS::NORMAL);

}

BossPincerRight::BossPincerRight(BossPincerRight* pincer1st)
{
	this->zone.left = 1575;
	this->zone.top = 800;
	this->zone.right = 1895;
	this->zone.bottom = 1150;
	this->isCollision = true;
	this->pincer1st = pincer1st;
	this->wPosition->x = Boss::GetInstance()->GetPosition()->x - 50 - BOSS_DISTANCE_BETWEEN_PINCERS;
	this->wPosition->y = Boss::GetInstance()->GetPosition()->y;
	this->wVelocity->y = BOSS_PINCER_MOVE_SPEED;
	this->isMoving = true;


	LPDIRECT3DTEXTURE9 d3dtex = Textures::GetInstance()->GetDirect3DTexture(Textures::TEXTURES::BOSS);
	for (int i = 0; i < ANIMATIONS::_LENGHT; i++)
	{
		switch (i)
		{
		case ANIMATIONS::NORMAL: // xanh la
		{
			Animation* ani = new Animation();
			ani->Add(new Sprite(264, 1147, 282, 1179, d3dtex), 100);
			ani->Add(new Sprite(241, 1147, 259, 1179, d3dtex), 100);
			ani->Add(new Sprite(218, 1147, 236, 1179, d3dtex), 100);
			this->animations->Add(ani);
			ani->Repeat(true);
			break;
		}
		case ANIMATIONS::LOWHP: // cam
		{
			Animation* ani = new Animation();
			ani->Add(new Sprite(312, 1147, 330, 1179, d3dtex), 100);
			ani->Add(new Sprite(287, 1147, 305, 1179, d3dtex), 100);
			this->animations->Add(ani);
			ani->Repeat(true);
			break;
		}
		}
	}

	this->animations->Start(ANIMATIONS::NORMAL);

	
}

void BossPincerRight::Update(DWORD dt, vector<LPOBJECT>* objs)
{
	if (this->pincer1st == nullptr) {  // truong hop la tay thu nhat
		// gioi han vung di chuyen
		if (this->GetCollisionBox().left < zone.left) {
			this->wVelocity->x = BOSS_PINCER_MOVE_SPEED;
		}
		if (this->GetCollisionBox().right > zone.right) {
			this->wVelocity->x = -BOSS_PINCER_MOVE_SPEED;
		}
		if (this->GetCollisionBox().top < zone.top) {
			this->wVelocity->y = BOSS_PINCER_MOVE_SPEED;
		}
		if (this->GetCollisionBox().bottom > zone.bottom) {
			this->wVelocity->y = -BOSS_PINCER_MOVE_SPEED;
		}

		// di chuyen trong thoi gian nhat dinh roi dung lai
		if (this->isMoving) {
			this->move_time += dt;
			if (this->move_time >= BOSS_PINCER_MOVE_TIME) {
				this->move_time = 0;
				this->isMoving = false;
				this->wVelocity->x = 0;
				this->wVelocity->y = 0;
			}
		}
		else {
			// dổi hướng di chuyển
			this->change_direction_time += dt;
			if (this->change_direction_time > BOSS_PINCER_CHANGE_DIRECTION_TIME) {
				this->wVelocity->x = (rand() % 3 - 1) * BOSS_PINCER_MOVE_SPEED; // ramdom (-1 -> 1)
				this->wVelocity->y = (rand() % 3 - 1) * BOSS_PINCER_MOVE_SPEED; // ramdom (-1 -> 1)
				if (this->wVelocity->x != 0 || this->wVelocity->y != 0) {
					this->isMoving = true;
					this->change_direction_time = 0;
				}
			}
		}
	}
	else {  // truong hop la tay thu 2 -> di chuyen giong tay thu nhat
		this->wVelocity->x = pincer1st->GetVelocity().x;
		this->wVelocity->y = pincer1st->GetVelocity().y;

		wPosition->x += (int)(this->wVelocity->x * dt);
		wPosition->y += (int)(this->wVelocity->y * dt);
	}
	

	// het nhap nhay
	if (this->animations->GetCurrentAnimationID() == BossPincerRight::ANIMATIONS::LOWHP && this->animations->GetCurrentAnimation()->IsDone()) {
		this->animations->Start(BossPincerRight::ANIMATIONS::NORMAL);
	}

	// xu ly va cham
	if (isCollision) {
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
				if (coEventsResult.at(i)->obj->GetTypeObj() == TYPEOBJECT::BRICK) {
					/*float x = this->wPosition->x + this->wVelocity->x * dt * min_tx;
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
					}*/

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
}

void BossPincerRight::KeyEvents()
{
}

void BossPincerRight::DoActionOnCollision(int nx, int ny, LPOBJECT obj)
{
	if (obj->GetTypeObj() == TYPEOBJECT::BRICK) {
		if (nx != 0) {
			if (nx == 1) {
				this->wVelocity->x = BOSS_PINCER_MOVE_SPEED;
			}
			else
			if (nx == -1) {
				this->wVelocity->x = -BOSS_PINCER_MOVE_SPEED;
			}
		}

		if (ny != 0) {
			if (ny == 1) {
				this->wVelocity->y = BOSS_PINCER_MOVE_SPEED;
			}
			else
			if (ny == -1) {
				this->wVelocity->y = -BOSS_PINCER_MOVE_SPEED;
			}
		}
	}
	else
	if (obj->GetTypeObj() == TYPEOBJECT::JASON2) {
		if (Jason2::GetInstance()->GettIsHurt() == false) {
			Jason2::GetInstance()->SetIsHurt(true);
			Jason2::GetInstance()->HP(1);
		}
	}
}

void BossPincerRight::Render()
{
	/*if (tex->LPDIRECT3DTEXTURE() == nullptr) {
		tex = new Texture(L"textures/bbox.png", D3DCOLOR_XRGB(255, 255, 255));
	}
	LPDIRECT3DTEXTURE9 d3dtex = tex->LPDIRECT3DTEXTURE();

	D3DXVECTOR3 p(Global::GetInstance()->_Camera->Convert(*wPosition).x, Global::GetInstance()->_Camera->Convert(*wPosition).y, 0);
	Global::GetInstance()->_SpriteHandler->Draw(d3dtex, &GetCollisionBox(), NULL, &p, D3DCOLOR_ARGB(255, 255, 255, 255));*/


	this->animations->Render(*wPosition);
}

RECT BossPincerRight::GetCollisionBox()
{
	RECT r;
	r.left = this->wPosition->x;
	r.right = this->wPosition->x + 18;
	r.top = this->wPosition->y;
	r.bottom = this->wPosition->y + 30;
	return r;
}

D3DXVECTOR2 BossPincerRight::GetCollisionBoxCenter()
{
	RECT r = GetCollisionBox();
	return D3DXVECTOR2((r.left + r.right) / 2, (r.top + r.bottom) / 2);
}

BossPincerRight::~BossPincerRight()
{
}

#pragma endregion


#pragma region ============== BossHandLeft ====================
BossHandLeft::BossHandLeft()
{
	this->isCollision = true;
	this->isExist = true;
	_node1 = new BossHandNode();
	_node2 = new BossHandNode();
	_node3 = new BossHandNode();
	_node4 = new BossHandNode();
	_pincer = new BossPincerLeft();
}

BossHandLeft::BossHandLeft(BossHandLeft* hand1st)
{
	this->hand1st = hand1st;
	this->isCollision = true;
	this->isExist = true;
	_node1 = new BossHandNode();
	_node2 = new BossHandNode();
	_node3 = new BossHandNode();
	_node4 = new BossHandNode();
	_pincer = new BossPincerLeft(hand1st->_pincer);
}

void BossHandLeft::Update(DWORD dt, vector<LPOBJECT>* objs)
{
	if (isExist) {

		_pincer->Update(dt, objs);

		// di chuyen cac node theo pincer;
		D3DXVECTOR2 lefthandposition;
		if (hand1st == nullptr) { // truong hop la canh tay thu nhat
			lefthandposition = *(Boss::GetInstance()->GetPosition()) + D3DXVECTOR2(60, 20);
		}
		else { // truong hop la canh tay thu hai 
			lefthandposition = *(Boss::GetInstance()->GetPosition()) + D3DXVECTOR2(60 + BOSS_DISTANCE_BETWEEN_PINCERS, 20);
		}

		D3DXVECTOR2 pincer = _pincer->GetCollisionBoxCenter();
		float dx = pincer.x - lefthandposition.x;
		float dy = pincer.y - lefthandposition.y;

		_node1->SetCenterPosstion(D3DXVECTOR2(lefthandposition.x, lefthandposition.y));
		_node2->SetCenterPosstion(D3DXVECTOR2(lefthandposition.x + dx * 0.25f, lefthandposition.y + dy * 0.25f));
		_node3->SetCenterPosstion(D3DXVECTOR2(lefthandposition.x + dx * 0.5f, lefthandposition.y + dy * 0.5f));
		_node4->SetCenterPosstion(D3DXVECTOR2(lefthandposition.x + dx * 0.75f, lefthandposition.y + dy * 0.75f));

		_node1->Update(dt, objs);
		_node2->Update(dt, objs);
		_node3->Update(dt, objs);
		_node4->Update(dt, objs);
	}
	
}

void BossHandLeft::KeyEvents()
{
}

void BossHandLeft::DoActionOnCollision(int nx, int ny, LPOBJECT obj)
{
}

void BossHandLeft::Render()
{
	if (isExist) {
		_node1->Render();
		_node2->Render();
		_node3->Render();
		_node4->Render();
		_pincer->Render();
	}
	
}


BossHandLeft::~BossHandLeft()
{
}

#pragma endregion


#pragma region ============== BossHandRight ====================
BossHandRight::BossHandRight()
{
	this->isExist = true;
	this->isCollision = true;
	_node1 = new BossHandNode();
	_node2 = new BossHandNode();
	_node3 = new BossHandNode();
	_node4 = new BossHandNode();
	_pincer = new BossPincerRight();
}

BossHandRight::BossHandRight(BossHandRight* hand1st)
{
	this->hand1st = hand1st;
	this->isExist = true;
	this->isCollision = true;
	_node1 = new BossHandNode();
	_node2 = new BossHandNode();
	_node3 = new BossHandNode();
	_node4 = new BossHandNode();
	_pincer = new BossPincerRight(hand1st->_pincer);
}

void BossHandRight::Update(DWORD dt, vector<LPOBJECT>* objs)
{
	if (isExist) {
		_pincer->Update(dt, objs);

		// di chuyen cac node theo pincer;
		D3DXVECTOR2 lefthandposition;
		if (hand1st == nullptr) { // truong hop la canh tay thu nhat
			lefthandposition = *(Boss::GetInstance()->GetPosition()) + D3DXVECTOR2(-10, 20);
		}
		else { // truong hop la canh tay thu hai 
			lefthandposition = *(Boss::GetInstance()->GetPosition()) + D3DXVECTOR2(-10 - BOSS_DISTANCE_BETWEEN_PINCERS, 20);
		}

		D3DXVECTOR2 pincer = _pincer->GetCollisionBoxCenter();
		float dx = pincer.x - lefthandposition.x;
		float dy = pincer.y - lefthandposition.y;

		_node1->SetCenterPosstion(D3DXVECTOR2(lefthandposition.x, lefthandposition.y));
		_node2->SetCenterPosstion(D3DXVECTOR2(lefthandposition.x + dx * 0.25f, lefthandposition.y + dy * 0.25f));
		_node3->SetCenterPosstion(D3DXVECTOR2(lefthandposition.x + dx * 0.5f, lefthandposition.y + dy * 0.5f));
		_node4->SetCenterPosstion(D3DXVECTOR2(lefthandposition.x + dx * 0.75f, lefthandposition.y + dy * 0.75f));

		_node1->Update(dt, objs);
		_node2->Update(dt, objs);
		_node3->Update(dt, objs);
		_node4->Update(dt, objs);
	}
	
}

void BossHandRight::KeyEvents()
{
}

void BossHandRight::DoActionOnCollision(int nx, int ny, LPOBJECT obj)
{

}

void BossHandRight::Render()
{
	if (isExist) {
		_node1->Render();
		_node2->Render();
		_node3->Render();
		_node4->Render();
		_pincer->Render();
	}
}


BossHandRight::~BossHandRight()
{
}

#pragma endregion


#pragma region ============== BossHead ====================

BossHead::BossHead()
{
	this->isExist = true;
	this->isCollision = true;
	this->width = 60;
	this->height = 64;

	this->wPosition->x = Boss::GetInstance()->GetPosition()->x;
	this->wPosition->y = Boss::GetInstance()->GetPosition()->y;

	LPDIRECT3DTEXTURE9 d3dtex = Textures::GetInstance()->GetDirect3DTexture(Textures::TEXTURES::BOSS);

	for (int i = 0; i < ANIMATIONS::_LENGHT; i++)
	{
		switch (i)
		{
		case ANIMATIONS::IDLE:
		{
			Animation* ani = new Animation();
			ani->Add(new Sprite(80, 303, 140, 367, d3dtex), 100);
			ani->Add(new Sprite(146, 302, 206, 367, d3dtex), 100);
			ani->Add(new Sprite(213, 303, 273, 367, d3dtex), 100);
			ani->Add(new Sprite(280, 302, 340, 367, d3dtex), 100);
			this->animations->Add(ani);
			ani->Repeat(true);
			break;
		}
		case ANIMATIONS::LITLELOWHP:
		{
			Animation* ani = new Animation();
			ani->Add(new Sprite(80, 303, 140, 367, d3dtex), 300);
			ani->Add(new Sprite(84, 440, 144, 504, d3dtex), 300);
			ani->Add(new Sprite(85, 578, 145, 642, d3dtex), 300);
			ani->Add(new Sprite(84, 715, 144, 779, d3dtex), 300);
			ani->Add(new Sprite(85, 992, 145, 1056, d3dtex), 300);
			this->animations->Add(ani);
			//ani->Repeat(true);
			break;
		}
		case ANIMATIONS::LOWHP:
		{
			Animation* ani = new Animation();
			ani->Add(new Sprite(80, 303, 140, 367, d3dtex), 100);
			ani->Add(new Sprite(84, 440, 144, 504, d3dtex), 100);
			ani->Add(new Sprite(85, 578, 145, 642, d3dtex), 100);
			ani->Add(new Sprite(84, 715, 144, 779, d3dtex), 100);
			ani->Add(new Sprite(85, 992, 145, 1056, d3dtex), 100);
			this->animations->Add(ani);
			//ani->Repeat(true);
			break;
		}
		case ANIMATIONS::VERYLOWHP:
		{
			Animation* ani = new Animation();
			ani->Add(new Sprite(80, 303, 140, 367, d3dtex), 100);
			ani->Add(new Sprite(84, 440, 144, 504, d3dtex), 100);
			ani->Add(new Sprite(85, 578, 145, 642, d3dtex), 100);
			ani->Add(new Sprite(84, 715, 144, 779, d3dtex), 100);
			ani->Add(new Sprite(85, 992, 145, 1056, d3dtex), 100);
			this->animations->Add(ani);
			break;
		}
		}
	}

	this->animations->Start(ANIMATIONS::IDLE);
}

void BossHead::Update(DWORD dt, vector<LPOBJECT>* objs)
{
	if (isExist) {
		
		// het nhap nhay
		if (this->animations->GetCurrentAnimationID() == BossHead::ANIMATIONS::LITLELOWHP && this->animations->GetCurrentAnimation()->IsDone()) {
			this->animations->Start(BossHead::ANIMATIONS::IDLE);
		}

		this->wVelocity->x = Boss::GetInstance()->GetVelocity().x;
		this->wVelocity->y = Boss::GetInstance()->GetVelocity().y;

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
					if (coEventsResult.at(i)->obj->IsExist()) {
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

void BossHead::KeyEvents()
{

}

void BossHead::DoActionOnCollision(int nx, int ny, LPOBJECT obj)
{
	LPJASON2BULLET bullet = dynamic_cast<LPJASON2BULLET>(obj);
	Boss::GetInstance()->HP(bullet->GetDamage());
	bullet->SetDamage(0);
	bullet->Destroy();
}

void BossHead::Render()
{
	/*if (tex->LPDIRECT3DTEXTURE() == nullptr) {
		tex = new Texture(L"textures/bbox.png", D3DCOLOR_XRGB(255, 255, 255));
	}
	LPDIRECT3DTEXTURE9 d3dtex = tex->LPDIRECT3DTEXTURE();

	D3DXVECTOR3 p(Global::GetInstance()->_Camera->Convert(*wPosition).x, Global::GetInstance()->_Camera->Convert(*wPosition).y, 0);
	Global::GetInstance()->_SpriteHandler->Draw(d3dtex, &GetCollisionBox(), NULL, &p, D3DCOLOR_ARGB(255, 255, 255, 255));*/

	if (this->isExist) {
		this->animations->Render(*wPosition);
	}
}

RECT BossHead::GetCollisionBox()
{
	RECT r;
	r.left = wPosition->x;
	r.right = wPosition->x + width;
	r.top = wPosition->y;
	r.bottom = wPosition->y + height;
	return r;
}

D3DXVECTOR2 BossHead::GetCollisionBoxCenter()
{
	RECT r = GetCollisionBox();
	return D3DXVECTOR2((r.left + r.right) / 2, (r.top + r.bottom) / 2);
}

BossHead::~BossHead()
{
}
#pragma endregion


#pragma region ============== Boss ====================
Boss * Boss::_instance = nullptr;

Boss::Boss()
{
	
}

void Boss::Init()
{
	this->zone.left = 1575;
	this->zone.top = 800;
	this->zone.right = 1895;
	this->zone.bottom = 1150;
	this->wPosition = new D3DXVECTOR2(1700, 1000);
	this->wVelocity->x = BOSS_MOVE_SPEED;
	this->bullets = new vector<LPBOSSBULLET>();
	this->_head = new BossHead();;
	this->_handleft1 = new BossHandLeft();
	this->_handleft2 = new BossHandLeft(_handleft1);
	this->_handleft2->SetExist(false);
	this->_handright1 = new BossHandRight();
	this->_handright2 = new BossHandRight(_handright1);
	this->_handright2->SetExist(false);
}

void Boss::Update(DWORD dt, vector<LPOBJECT>* objs)
{
	DebugOut(L"HP: %d\n", this->hp);

	// them 2 tay khi duoi 1/2 mau
	if (this->hp < BOSS_HP/2) {
		this->_handleft2->SetExist(true);
		this->_handright2->SetExist(true);
		
		this->_head->GetAnimations()->Start(BossHead::ANIMATIONS::LITLELOWHP);

		this->_handleft1->_pincer->GetAnimations()->Start(BossPincerLeft::ANIMATIONS::LOWHP);
		this->_handleft1->_node1->GetAnimations()->Start(BossHandNode::ANIMATIONS::LOWHP);
		this->_handleft1->_node2->GetAnimations()->Start(BossHandNode::ANIMATIONS::LOWHP);
		this->_handleft1->_node3->GetAnimations()->Start(BossHandNode::ANIMATIONS::LOWHP);
		this->_handleft1->_node4->GetAnimations()->Start(BossHandNode::ANIMATIONS::LOWHP);

		this->_handleft2->_pincer->GetAnimations()->Start(BossPincerLeft::ANIMATIONS::LOWHP);
		this->_handleft2->_node1->GetAnimations()->Start(BossHandNode::ANIMATIONS::LOWHP);
		this->_handleft2->_node2->GetAnimations()->Start(BossHandNode::ANIMATIONS::LOWHP);
		this->_handleft2->_node3->GetAnimations()->Start(BossHandNode::ANIMATIONS::LOWHP);
		this->_handleft2->_node4->GetAnimations()->Start(BossHandNode::ANIMATIONS::LOWHP);

		this->_handright1->_pincer-> GetAnimations()->Start(BossPincerRight::ANIMATIONS::LOWHP);
		this->_handright1->_node1->GetAnimations()->Start(BossHandNode::ANIMATIONS::LOWHP);
		this->_handright1->_node2->GetAnimations()->Start(BossHandNode::ANIMATIONS::LOWHP);
		this->_handright1->_node3->GetAnimations()->Start(BossHandNode::ANIMATIONS::LOWHP);
		this->_handright1->_node4->GetAnimations()->Start(BossHandNode::ANIMATIONS::LOWHP);

		this->_handright2->_pincer->GetAnimations()->Start(BossPincerRight::ANIMATIONS::LOWHP);
		this->_handright2->_node1->GetAnimations()->Start(BossHandNode::ANIMATIONS::LOWHP);
		this->_handright2->_node2->GetAnimations()->Start(BossHandNode::ANIMATIONS::LOWHP);
		this->_handright2->_node3->GetAnimations()->Start(BossHandNode::ANIMATIONS::LOWHP);
		this->_handright2->_node4->GetAnimations()->Start(BossHandNode::ANIMATIONS::LOWHP);
	}
	// khi chet
	if(this->hp < 0) {
		this->isDieing = true;
		
	}
	

	// mat dan bo phan khi chet
	if (this->isDieing) {
		died_time -= dt;
		if (died_time < 2000) {
			this->_handleft2->SetExist(false);
			this->_handright2->SetExist(false);
		}

		if (died_time < 1000) {
			this->_handleft1->SetExist(false);
			this->_handright1->SetExist(false);
		}

		if (died_time < 0) {
			this->_head->SetExist(false);
		}

		if (died_time < -1000) {
			Jason2::GetInstance()->SetPostion(150, 1900);
			Jason2::GetInstance()->SetIsFightingWithBoss(false);
			Jason2::GetInstance()->GetAnimations()->Start(Jason2::ANIMATIONS::IDLELEFT);
			Global::GetInstance()->_Camera->AnchorTo(Jason2::GetInstance()->GetPosition());
			
		}

	}

	// ban dan
	if (Jason2::GetInstance()->GetIsFightingWithBoss() && isDieing == false) {
		this->shoot_delay_time += dt;
		if (this->shoot_delay_time > BOSS_SHOOT_DELAY_TIME) {
			this->shoot_delay_time = 0;
			this->bullets->push_back(new BossBullet(Jason2::GetInstance()->GetCollisionBoxCenter(), _head->GetCollisionBoxCenter().x, _head->GetCollisionBoxCenter().y + 20));
		}
	}

	// bullets
	for each (LPBOSSBULLET bullet in *bullets)
	{
		bullet->Update(dt);
	}


	// gioi han vung di chuyen
	if (this->GetCollisionBox().left < zone.left) {
		this->wVelocity->x = BOSS_MOVE_SPEED;
	}
	if (this->GetCollisionBox().right > zone.right) {
		this->wVelocity->x = -BOSS_MOVE_SPEED;
	}

	wPosition->x += (this->wVelocity->x * dt);
	wPosition->y += (this->wVelocity->y * dt);

	this->_head->Update(dt, objs);
	this->_handleft1->Update(dt, objs);
	this->_handleft2->Update(dt, objs);
	this->_handright1->Update(dt, objs);
	this->_handright2->Update(dt, objs);
}

void Boss::KeyEvents()
{
}

void Boss::DoActionOnCollision(int nx, int ny, LPOBJECT obj)
{
}

void Boss::Render()
{
	this->_head->Render();

	for each (LPBOSSBULLET bullet in *bullets)
	{
		bullet->Render();
	}

	this->_handleft1->Render();
	this->_handleft2->Render();
	this->_handright1->Render();
	this->_handright2->Render();

}

void Boss::HP(int damage)
{
	this->hp -= damage;
}


RECT Boss::GetCollisionBox()
{
	return _head->GetCollisionBox();
}

D3DXVECTOR2 Boss::GetCollisionBoxCenter()
{
	RECT r = GetCollisionBox();
	return D3DXVECTOR2((r.left + r.right) / 2, (r.top + r.bottom) / 2);
}

Boss* Boss::GetInstance()
{
	if (_instance == NULL) _instance = new Boss();
	return _instance;
}

Boss::~Boss()
{
}

#pragma endregion


