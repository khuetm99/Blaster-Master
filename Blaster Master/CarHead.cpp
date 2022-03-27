#include "CarHead.h"

CarHead::CarHead(LPD3DXVECTOR2 anchor)
{
	this->relativePosition = new D3DXVECTOR2(0,0);
	this->anchorPoint = anchor;

	////texture trái
	//LPTEXTURE tex = new Texture(L"textures/BlasterMaster.png", D3DCOLOR_XRGB(0, 57, 115));
	//LPDIRECT3DTEXTURE9 d3dtex = tex->LPDIRECT3DTEXTURE();

	////texture phải
	//LPTEXTURE texR = new Texture(L"textures/BlasterMaster1.png", D3DCOLOR_XRGB(0, 57, 115));
	//LPDIRECT3DTEXTURE9 d3dtexR = texR->LPDIRECT3DTEXTURE();

	LPDIRECT3DTEXTURE9 d3dtex = Textures::GetInstance()->GetDirect3DTexture(Textures::TEXTURES::CHARACTERLEFT);
	LPDIRECT3DTEXTURE9 d3dtexR = Textures::GetInstance()->GetDirect3DTexture(Textures::TEXTURES::CHARACTERRIGHT);



	for (int i = 0; i < ANIMATIONS::_LENGHT ; i++)
	{
		switch (i)
		{
			case ANIMATIONS::IDLERIGHT: {
				//Ngang phải
				Animation* ani = new Animation();
				ani->Add(new Sprite(355, 3, 371, 11, d3dtexR), D3DXVECTOR2(-8, -8), 100);
				this->animations->Add(ani);
				break;
			}
			case ANIMATIONS::IDLELEFT: {
				// Ngang trái
				Animation* ani = new Animation();
				ani->Add(new Sprite(39, 3, 55, 11, d3dtex), D3DXVECTOR2(-1, -8), 100);
				this->animations->Add(ani);		
				break;
			}
			case ANIMATIONS::UPRIGHT: {
				// Up phải
				Animation* ani = new Animation();
				ani->Add(new Sprite(355, 3, 371, 11, d3dtexR), D3DXVECTOR2(-8, -8), 70);
				ani->Add(new Sprite(355, 3, 371, 11, d3dtexR), D3DXVECTOR2(-8, -10), 70);
				ani->Add(new Sprite(321, 4, 337, 19, d3dtexR), D3DXVECTOR2(-13, -12), 70);
				this->animations->Add(ani);
				break;
			}
			case ANIMATIONS::UPLEFT: {
				// Up trái
				Animation* ani = new Animation();
				ani->Add(new Sprite(39, 3, 55, 11, d3dtex), D3DXVECTOR2(-1, -8), 70);
				ani->Add(new Sprite(39, 3, 55, 11, d3dtex), D3DXVECTOR2(-1, -10), 70);
				ani->Add(new Sprite(73, 4, 89, 19, d3dtex), D3DXVECTOR2(4, -12), 70);
				this->animations->Add(ani);
				break;
			}
			case ANIMATIONS::DOWNRIGHT: {
				// Down phải
				Animation* ani = new Animation();
				ani->Add(new Sprite(321, 4, 337, 19, d3dtexR), D3DXVECTOR2(-13, -12), 70);
				ani->Add(new Sprite(355, 3, 371, 11, d3dtexR), D3DXVECTOR2(-8, -10), 70);
				ani->Add(new Sprite(355, 3, 371, 11, d3dtexR), D3DXVECTOR2(-8, -8), 70);
				ani->SetNextAnimationID(ANIMATIONS::IDLERIGHT);
				this->animations->Add(ani);
				break;
			}
			case ANIMATIONS::DOWNLEFT: {
				// Down trái
				Animation* ani = new Animation();
				ani->Add(new Sprite(73, 4, 89, 19, d3dtex), D3DXVECTOR2(4, -12), 70);
				ani->Add(new Sprite(39, 3, 55, 11, d3dtex), D3DXVECTOR2(-1, -10), 70);
				ani->Add(new Sprite(39, 3, 55, 11, d3dtex), D3DXVECTOR2(-1, -8), 70);
				ani->SetNextAnimationID(ANIMATIONS::IDLELEFT);
				this->animations->Add(ani);
				break;
			}
			case ANIMATIONS::ROTATERIGHT: {
				// Xoay từ trái sang phải
				Animation* ani = new Animation();
				ani->Add(new Sprite(39, 3, 55, 11, d3dtex), D3DXVECTOR2(-1, -8), 50);
				ani->Add(new Sprite(56, 3, 72, 11, d3dtex), D3DXVECTOR2(-5, -8), 58);
				ani->Add(new Sprite(355, 3, 371, 11, d3dtexR), D3DXVECTOR2(-8, -8), 50);
				ani->SetNextAnimationID(ANIMATIONS::IDLERIGHT);
				this->animations->Add(ani);
				break;
			}
			case ANIMATIONS::ROTATELEFT: {
				// Xoay từ phải sang trái
				Animation* ani = new Animation();
				ani->Add(new Sprite(355, 3, 371, 11, d3dtexR), D3DXVECTOR2(-8, -8), 50);
				ani->Add(new Sprite(338, 3, 354, 11, d3dtexR), D3DXVECTOR2(-5, -8), 50);
				ani->Add(new Sprite(39, 3, 55, 11, d3dtex), D3DXVECTOR2(-1, -8), 50);
				ani->SetNextAnimationID(ANIMATIONS::IDLELEFT);
				this->animations->Add(ani);
				break;
			}
			case ANIMATIONS::OPENDOORRIGHT: {
				// Mở cửa bên phải
				Animation* ani = new Animation();
				ani->Add(new Sprite(252, 3, 268, 19, d3dtexR), D3DXVECTOR2(-8, -16), 500);
				ani->Add(new Sprite(269, 3, 285, 19, d3dtexR), D3DXVECTOR2(-8, -16), 100);
				ani->Add(new Sprite(355, 3, 371, 11, d3dtexR), D3DXVECTOR2(-8, -8), 100);
				this->animations->Add(ani);
				break;
			}
			case ANIMATIONS::OPENDOORLEFT: {
				// Mở cửa bên phải
				Animation* ani = new Animation();
				ani->Add(new Sprite(142, 3, 158, 19, d3dtex), D3DXVECTOR2(-1, -16), 500);
				ani->Add(new Sprite(125, 3, 141, 19, d3dtex), D3DXVECTOR2(-1, -16), 100);
				ani->Add(new Sprite(39, 3, 55, 11, d3dtex), D3DXVECTOR2(-1, -8), 100);
				this->animations->Add(ani);
				break;
			}
			case ANIMATIONS::CLOSERIGHT: {
				// Mở cửa bên phải
				Animation* ani = new Animation();
				ani->Add(new Sprite(252, 3, 268, 19, d3dtexR), D3DXVECTOR2(-8, -16), 200);
				ani->Add(new Sprite(269, 3, 285, 19, d3dtexR), D3DXVECTOR2(-8, -16), 100);
				ani->Add(new Sprite(355, 3, 371, 11, d3dtexR), D3DXVECTOR2(-8, -8), 300);
				this->animations->Add(ani);
				break;
			}
			case ANIMATIONS::CLOSELEFT: {
				// Mở cửa bên phải
				Animation* ani = new Animation();
				ani->Add(new Sprite(142, 3, 158, 19, d3dtex), D3DXVECTOR2(-1, -16), 200);
				ani->Add(new Sprite(125, 3, 141, 19, d3dtex), D3DXVECTOR2(-1, -16), 100);
				ani->Add(new Sprite(39, 3, 55, 11, d3dtex), D3DXVECTOR2(-1, -8), 300);
				this->animations->Add(ani);
				break;
			}
		}
	}
	
	this->animations->Start(ANIMATIONS::IDLELEFT);
}

void CarHead::Update(DWORD dt)
{
	//DebugOut(L"ani %d\n", animations->GetCurrentAnimationID());

	this->wPosition->x = this->anchorPoint->x + this->relativePosition->x;
	this->wPosition->y = this->anchorPoint->y + this->relativePosition->y;

	this->animations->Update(dt);
}

void CarHead::Render(float opacity)
{
	this->animations->Render(*this->GetPosition(),  opacity);
}

void CarHead::SetRelativePosition(float x, float y)
{
	this->relativePosition->x = x;
	this->relativePosition->y = y;
}

void CarHead::RightToLeft()
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

void CarHead::LeftToRight()
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

void CarHead::UpRight()
{
	this->animations->Restart(ANIMATIONS::UPRIGHT);
}

void CarHead::UpLeft()
{
	this->animations->Restart(ANIMATIONS::UPLEFT);
}

void CarHead::DownRight() {
	this->animations->Restart(ANIMATIONS::DOWNRIGHT);
}

void CarHead::DownLeft() {
	this->animations->Restart(ANIMATIONS::DOWNLEFT);
}

void CarHead::RotateRight()
{
	this->animations->Restart(ANIMATIONS::ROTATERIGHT);
}

void CarHead::RotateLeft()
{
	this->animations->Restart(ANIMATIONS::ROTATELEFT);
}

void CarHead::OpenDoorRight()
{
	this->animations->Restart(ANIMATIONS::OPENDOORRIGHT);
}

void CarHead::OpenDoorLeft()
{
	this->animations->Restart(ANIMATIONS::OPENDOORLEFT);
}

void CarHead::CloseDoorRight()
{
	this->animations->Restart(ANIMATIONS::CLOSERIGHT);
}

void CarHead::CloseDoorLeft()
{
	this->animations->Restart(ANIMATIONS::CLOSELEFT);
}


CarHead::~CarHead()
{
}
