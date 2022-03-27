#include "CarGun.h"

CarGun::CarGun(LPD3DXVECTOR2 anchor)
{
	this->relativePosition = new D3DXVECTOR2(0,0);
	this->anchorPoint = anchor;

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
			case ANIMATIONS::IDLERIGHT: { //0
				//Ngang phải
				Animation* ani = new Animation();
				ani->Add(new Sprite(391, 5, 398, 9, d3dtexR), D3DXVECTOR2(10, -5), 100);
				this->animations->Add(ani);
				break;
			}
			case ANIMATIONS::IDLELEFT: { //1
				// Ngang trái
				Animation* ani = new Animation();
				ani->Add(new Sprite(12, 5, 19, 9, d3dtex), D3DXVECTOR2(-9, -5), 100);
				this->animations->Add(ani);
				break;
			}
			case ANIMATIONS::UPRIGHT: { //2
				Animation* ani = new Animation();
				ani->Add(new Sprite(391, 5, 398, 9, d3dtexR), D3DXVECTOR2(10, -5), 70);
				ani->Add(new Sprite(381, 3, 389, 11, d3dtexR), D3DXVECTOR2(8, -16), 70);
				ani->Add(new Sprite(374, 3, 378, 10, d3dtexR), D3DXVECTOR2(-2, -19), 70);
				this->animations->Add(ani);
				break;
			}
			case ANIMATIONS::UPLEFT: { //3
				Animation* ani = new Animation();
				ani->Add(new Sprite(12, 5, 19, 9, d3dtex), D3DXVECTOR2(-9, -5), 70);
				ani->Add(new Sprite(21, 3, 29, 11, d3dtex), D3DXVECTOR2(-7, -16), 70);
				ani->Add(new Sprite(32, 3, 36, 10, d3dtex), D3DXVECTOR2(5, -19), 70);
				this->animations->Add(ani);
				break;
			}
			case ANIMATIONS::DOWNRIGHT: { //4
				Animation* ani = new Animation();
				ani->Add(new Sprite(374, 3, 378, 10, d3dtexR), D3DXVECTOR2(-2, -19), 70);
				ani->Add(new Sprite(381, 3, 389, 11, d3dtexR), D3DXVECTOR2(8, -16), 70);
				ani->Add(new Sprite(391, 5, 398, 9, d3dtexR), D3DXVECTOR2(10, -5), 70);
				ani->SetNextAnimationID(ANIMATIONS::IDLERIGHT);
				this->animations->Add(ani);
				break;
			}
			case ANIMATIONS::DOWNLEFT: { //5
				Animation* ani = new Animation();
				ani->Add(new Sprite(32, 3, 36, 10, d3dtex), D3DXVECTOR2(5, -19), 70);
				ani->Add(new Sprite(21, 3, 29, 11, d3dtex), D3DXVECTOR2(-7, -16), 70);
				ani->Add(new Sprite(12, 5, 19, 9, d3dtex), D3DXVECTOR2(-9, -5), 70);
				ani->SetNextAnimationID(ANIMATIONS::IDLELEFT);
				this->animations->Add(ani);
				break;
			}
			case ANIMATIONS::ROTATERIGHT: { //6
				//Ngang phải
				Animation* ani = new Animation();
				ani->Add(new Sprite(12, 5, 19, 9, d3dtex), D3DXVECTOR2(-9, -5), 50);
				ani->Add(new Sprite(0, 0, 0, 0, d3dtexR), D3DXVECTOR2(0, 0), 50);
				ani->Add(new Sprite(391, 5, 398, 9, d3dtexR), D3DXVECTOR2(10, -5), 50);
				ani->SetNextAnimationID(ANIMATIONS::IDLERIGHT);
				this->animations->Add(ani);
				break;
			}
			case ANIMATIONS::ROTATELEFT: { //7
				// Ngang trái
				Animation* ani = new Animation();
				ani->Add(new Sprite(391, 5, 398, 9, d3dtexR), D3DXVECTOR2(10, -5), 50);
				ani->Add(new Sprite(0, 0, 0, 0, d3dtex), D3DXVECTOR2(0, 0), 50);
				ani->Add(new Sprite(12, 5, 19, 9, d3dtex), D3DXVECTOR2(-9, -5), 50);
				ani->SetNextAnimationID(ANIMATIONS::IDLELEFT);
				this->animations->Add(ani);
				break;
			}
		}
	}

	this->animations->Start(ANIMATIONS::IDLELEFT);

}

void CarGun::Update(DWORD dt)
{
	this->wPosition->x = this->anchorPoint->x + this->relativePosition->x;
	this->wPosition->y = this->anchorPoint->y + this->relativePosition->y;

	this->animations->Update(dt);
}

void CarGun::Render(float opacity)
{
	this->animations->Render(*this->GetPosition(),  opacity);
}

void CarGun::SetRelativePosition(float x, float y)
{
	this->relativePosition->x = x;
	this->relativePosition->y = y;
}

void CarGun::RightToLeft()
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

void CarGun::LeftToRight()
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


void CarGun::UpRight()
{
	this->animations->Restart(ANIMATIONS::UPRIGHT);
}

void CarGun::UpLeft()
{
	this->animations->Restart(ANIMATIONS::UPLEFT);
}

void CarGun::DownRight() {
	this->animations->Restart(ANIMATIONS::DOWNRIGHT);
}

void CarGun::DownLeft() {
	this->animations->Restart(ANIMATIONS::DOWNLEFT);
}

void CarGun::RotateRight()
{
	this->animations->Restart(ANIMATIONS::ROTATERIGHT);
}

void CarGun::RotateLeft()
{
	this->animations->Restart(ANIMATIONS::ROTATELEFT);
}

CarGun::~CarGun()
{
}
