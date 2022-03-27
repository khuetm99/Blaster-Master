#include "CarBody.h"

CarBody::CarBody(LPD3DXVECTOR2 anchor)
{
	relativePosition = new D3DXVECTOR2();
	anchorPoint = anchor;

	LPDIRECT3DTEXTURE9 d3dtexL = Textures::GetInstance()->GetDirect3DTexture(Textures::TEXTURES::CHARACTERLEFT);
	LPDIRECT3DTEXTURE9 d3dtexR = Textures::GetInstance()->GetDirect3DTexture(Textures::TEXTURES::CHARACTERRIGHT);


	for (int i = 0; i < ANIMATIONS::_LENGHT; i++)
	{
		switch (i)
		{
			case ANIMATIONS::IDLERIGHT: {
				Animation* ani = new Animation();
				ani->Add(new Sprite(400, 12, 406, 19, d3dtexR), 100);
				this->animations->Add(ani);
				break;
			}
			case ANIMATIONS::IDLELEFT: {
				Animation* ani = new Animation();
				ani->Add(new Sprite(4, 12, 10, 19, d3dtexL), 100);
				this->animations->Add(ani);
				break;
			}
			case ANIMATIONS::UPRIGHT: {
				Animation* ani = new Animation();
				ani->Add(new Sprite(400, 12, 406, 19, d3dtexR), 70);
				ani->Add(new Sprite(400, 12, 406, 19, d3dtexR), D3DXVECTOR2(0, -2), 70);
				ani->Add(new Sprite(400, 12, 406, 19, d3dtexR), D3DXVECTOR2(0, -5), 70);
				this->animations->Add(ani);
				break;
			}
			case ANIMATIONS::UPLEFT: {
				Animation* ani = new Animation();
				ani->Add(new Sprite(4, 12, 10, 19, d3dtexL), 70);
				ani->Add(new Sprite(4, 12, 10, 19, d3dtexL), D3DXVECTOR2(0, -2),  70);
				ani->Add(new Sprite(4, 12, 10, 19, d3dtexL), D3DXVECTOR2(0, -5), 70);
				this->animations->Add(ani);
				break;
			}
			case ANIMATIONS::DOWNRIGHT: {
				Animation* ani = new Animation();
				ani->Add(new Sprite(400, 12, 406, 19, d3dtexR), D3DXVECTOR2(0, -5), 70);
				ani->Add(new Sprite(400, 12, 406, 19, d3dtexR), D3DXVECTOR2(0, -2), 70);
				ani->Add(new Sprite(400, 12, 406, 19, d3dtexR), 70);
				ani->SetNextAnimationID(ANIMATIONS::IDLERIGHT);
				this->animations->Add(ani);
				break;
			}
			case ANIMATIONS::DOWNLEFT: {
				Animation* ani = new Animation();
				ani->Add(new Sprite(4, 12, 10, 19, d3dtexL), D3DXVECTOR2(0, -5), 70);
				ani->Add(new Sprite(4, 12, 10, 19, d3dtexL), D3DXVECTOR2(0, -2), 70);
				ani->Add(new Sprite(4, 12, 10, 19, d3dtexL), 70);
				ani->SetNextAnimationID(ANIMATIONS::IDLELEFT);
				this->animations->Add(ani);
				break;
			}
			case ANIMATIONS::ROTATERIGHT: {
				Animation* ani = new Animation();
				ani->Add(new Sprite(4, 12, 10, 19, d3dtexL), 50);
				ani->Add(new Sprite(4, 12, 10, 19, d3dtexL), 50);
				ani->Add(new Sprite(400, 12, 406, 19, d3dtexR), 50);
				ani->SetNextAnimationID(ANIMATIONS::IDLERIGHT);
				this->animations->Add(ani);
				break;
			}
			case ANIMATIONS::ROTATELEFT: {
				Animation* ani = new Animation();
				ani->Add(new Sprite(400, 12, 406, 19, d3dtexR), 50);
				ani->Add(new Sprite(400, 12, 406, 19, d3dtexR), 50);
				ani->Add(new Sprite(4, 12, 10, 19, d3dtexL), 50);	
				ani->SetNextAnimationID(ANIMATIONS::IDLELEFT);
				this->animations->Add(ani);
				break;
			}
		}
	}

	this->animations->Start(ANIMATIONS::IDLELEFT);
	
	this->SetRelativePosition(0, 0);
}

void CarBody::Update(DWORD dt)
{
	//DebugOut(L"ani %d\n", animations->GetCurrentAnimationID());

	Physical(dt);

	this->wPosition->x = this->anchorPoint->x + this->relativePosition->x;
	this->wPosition->y = this->anchorPoint->y + this->relativePosition->y;


	this->animations->Update(dt);
}

void CarBody::Render(float opacity)
{
	this->animations->Render(*this->GetPosition(), opacity);
}

void CarBody::Physical(DWORD dt)
{
	t += dt * 3.14 / 100;

	if (isUndulating) {
		relativePosition->y =  (sin(t) * 0.75);
	}
	else
	{
		relativePosition->y = 0;
	}
}

void CarBody::SetRelativePosition(float x, float y)
{
	this->relativePosition->x = x;
	this->relativePosition->y = y;
}

void CarBody::SetIsUndulating(bool isUndulating)
{
	this->isUndulating = isUndulating;
}


void CarBody::RightToLeft()
{
	int frameID = this->animations->GetCurrentAnimation()->GetCurrentFrameID();

	if (this->animations->GetCurrentAnimationID() == ANIMATIONS::IDLERIGHT) {
		this->animations->Start(ANIMATIONS::IDLELEFT, frameID);
	}
	else
	if (this->animations->GetCurrentAnimationID() == ANIMATIONS::UPRIGHT) {
		this->animations->Start(ANIMATIONS::UPLEFT, frameID);
	}
}

void CarBody::LeftToRight()
{
	int frameID = this->animations->GetCurrentAnimation()->GetCurrentFrameID();

	if (this->animations->GetCurrentAnimationID() == ANIMATIONS::IDLELEFT) {
		this->animations->Start(ANIMATIONS::IDLERIGHT, frameID);
	}
	else
	if (this->animations->GetCurrentAnimationID() == ANIMATIONS::UPLEFT) {
		this->animations->Start(ANIMATIONS::UPRIGHT, frameID);
	}
}


D3DXVECTOR2 CarBody::GetRelativePosition()
{
	return *relativePosition;
}

void CarBody::UpRight()
{
	this->animations->Restart(ANIMATIONS::UPRIGHT);
}

void CarBody::UpLeft()
{
	this->animations->Restart(ANIMATIONS::UPLEFT);
}

void CarBody::IdleRight()
{
	this->animations->Restart(ANIMATIONS::IDLERIGHT);
}

void CarBody::IdleLeft()
{
	this->animations->Restart(ANIMATIONS::IDLELEFT);
}

void CarBody::DownRight() {
	this->animations->Restart(ANIMATIONS::DOWNRIGHT);
}

void CarBody::DownLeft() {
	this->animations->Restart(ANIMATIONS::DOWNLEFT);
}

void CarBody::RotateRight()
{
	this->animations->Restart(ANIMATIONS::ROTATERIGHT);
}

void CarBody::RotateLeft()
{
	this->animations->Restart(ANIMATIONS::ROTATELEFT);
}

CarBody::~CarBody()
{
}
