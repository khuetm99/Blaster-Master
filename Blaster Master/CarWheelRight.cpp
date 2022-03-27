#include "CarWheelRight.h"

CarWheelRight::CarWheelRight(LPD3DXVECTOR2 anchor)
{
	this->relativePosition = new D3DXVECTOR2();
	this->anchorPoint = anchor;
	this->isShrinking = false;

	//LPDIRECT3DTEXTURE9 d3dtex = (new Texture(L"textures/BlasterMaster.png", D3DCOLOR_XRGB(0, 57, 115)))->LPDIRECT3DTEXTURE();

	LPDIRECT3DTEXTURE9 d3dtex = Textures::GetInstance()->GetDirect3DTexture(Textures::TEXTURES::CHARACTERLEFT);
	

	LPANIMATION ani_spin = new Animation();	
	ani_spin->Add(new Sprite(21, 21, 29, 29, d3dtex), 100);
	ani_spin->Add(new Sprite(30, 21, 38, 29, d3dtex), 100);
	ani_spin->Add(new Sprite(3, 21, 11, 29, d3dtex), 100);
	ani_spin->Add(new Sprite(12, 21, 20, 29, d3dtex), 100);
	ani_spin->Repeat(true);

	this->animations->Add(ani_spin);
	this->animations->Start(0);
	ani_spin->Pause();

	this->SetRelativePosition(8, 1);
}

void CarWheelRight::Update(DWORD dt)
{
	this->wPosition->x = this->anchorPoint->x + this->relativePosition->x;
	this->wPosition->y = this->anchorPoint->y + this->relativePosition->y;

	this->animations->Update(dt);
}

void CarWheelRight::Render(float opacity)
{
	if (this->isShrinking) {
		this->animations->Render(*this->GetPosition() + D3DXVECTOR2(-4, 0), opacity);
	}
	else
	{
		this->animations->Render(*this->GetPosition(), opacity);
	}
}

void CarWheelRight::SetRelativePosition(float x, float y)
{
	this->relativePosition->x = x;
	this->relativePosition->y = y;
}

void CarWheelRight::Idle()
{
	this->animations->Pause();
}

void CarWheelRight::WalkRight()
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

void CarWheelRight::WalkLeft()
{
	if (this->animations->GetCurrentAnimation()->IsPausing()) {
		this->animations->Resume(-1);
	}
	else
	if (this->animations->GetCurrentAnimation()->GetMode() == 1){
		this->animations->Pause();
		this->animations->Resume(-1);
	}
}

void CarWheelRight::SetIsShrinking(bool shrinking)
{
	this->isShrinking = shrinking;
}

bool CarWheelRight::IsShrinking()
{
	return isShrinking;
}

CarWheelRight::~CarWheelRight()
{

}
