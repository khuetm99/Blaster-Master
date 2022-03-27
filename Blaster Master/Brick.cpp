#include "Brick.h"

Brick::Brick(int x, int y, int width, int height):Object(x, y, width, height)
{ 
	this->SetTypeObj(TYPEOBJECT::BRICK);
	this->SetDirection(true, true, true, false);
	this->animations = nullptr;
}

void Brick::Render()
{
	/*if (tex->LPDIRECT3DTEXTURE() == nullptr) {
		tex = new Texture(L"textures/bbox.png", D3DCOLOR_XRGB(255, 255, 255));
	}
	LPDIRECT3DTEXTURE9 d3dtex = tex->LPDIRECT3DTEXTURE();

	D3DXVECTOR3 p(Global::GetInstance()->_Camera->Convert(*wPosition).x, Global::GetInstance()->_Camera->Convert(*wPosition).y, 0);
	Global::GetInstance()->_SpriteHandler->Draw(d3dtex, &GetCollisionBox(), NULL, &p, D3DCOLOR_ARGB(255, 255, 255, 255));*/

}

