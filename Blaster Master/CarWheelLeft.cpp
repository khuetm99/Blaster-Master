#include "CarWheelLeft.h"

CarWheelLeft::CarWheelLeft(LPD3DXVECTOR2 anchor)
{

	this->relativePosition = new D3DXVECTOR2();
	this->anchorPoint = anchor;
	this->isShrinking = false;


	//LPDIRECT3DTEXTURE9 d3dtex = (new Texture(L"textures/BlasterMaster.png", D3DCOLOR_XRGB(0, 57, 115)))->LPDIRECT3DTEXTURE();

	LPDIRECT3DTEXTURE9 d3dtex = Textures::GetInstance()->GetDirect3DTexture(Textures::TEXTURES::CHARACTERLEFT);
	

	LPANIMATION ani_spin = new Animation();
	ani_spin->Add(new Sprite(12, 21, 20, 29, d3dtex), 100);
	ani_spin->Add(new Sprite(21, 21, 29, 29, d3dtex), 100);
	ani_spin->Add(new Sprite(30, 21, 38, 29, d3dtex), 100);
	ani_spin->Add(new Sprite(3, 21, 11, 29, d3dtex), 100);
	ani_spin->Repeat(true);
	this->animations->Add(ani_spin);

	this->animations->Start(ANIMATIONS::WALK);
	this->animations->Pause();

	this->SetRelativePosition(-10, 1);
}

void CarWheelLeft::Update(DWORD dt)
{
	this->wPosition->x = this->anchorPoint->x + this->relativePosition->x;
	this->wPosition->y = this->anchorPoint->y + this->relativePosition->y;

	this->animations->Update(dt);
}

void CarWheelLeft::Render(float opacity)
{
	if (this->isShrinking) {
		this->animations->Render(*this->GetPosition() + D3DXVECTOR2(4, 0), opacity);
	}
	else
	{
		this->animations->Render(*this->GetPosition(), opacity);
	}
}

void CarWheelLeft::SetRelativePosition(float x, float y)
{
	this->relativePosition->x = x;
	this->relativePosition->y = y;
}

void CarWheelLeft::Idle()
{
	if (this->animations->GetCurrentAnimation()->IsRunning()) {
		this->animations->Pause();
	}
}

void CarWheelLeft::WalkRight()
{
	if (this->animations->GetCurrentAnimation()->IsPausing()) {
		this->animations->Resume(1);
	}
	else
	if (this->animations->GetCurrentAnimation()->GetMode() == -1) {
		this->animations->Pause();
		this->animations->Resume(1);
	}
}

void CarWheelLeft::WalkLeft()
{
	if (this->animations->GetCurrentAnimation()->IsPausing()) {
		this->animations->Resume(-1);
	}
	else 
	if (this->animations->GetCurrentAnimation()->GetMode() == 1) {
		this->animations->Pause();
		this->animations->Resume(-1);
	}
}

void CarWheelLeft::SetIsShrinking(bool shrinking)
{
	this->isShrinking = shrinking;
}

bool CarWheelLeft::IsShrinking()
{
	return isShrinking;
}

CarWheelLeft::~CarWheelLeft()
{
}
