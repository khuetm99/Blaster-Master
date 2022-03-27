#include "Collision.h"

void Colision::SweppAABB(float ml, float mt, float mr, float mb, float dx, float dy, float sl, float st, float sr, float sb, float& t, float& nx, float& ny, LPOBJECT& obj)
{
	float dx_entry, dx_exit, tx_entry, tx_exit;
	float dy_entry, dy_exit, ty_entry, ty_exit;

	float t_entry;
	float t_exit;

	t = -1.0f;                   //no collision
	nx = ny = 0;

	float bl = dx > 0 ? ml : ml + dx;
	float bt = dy > 0 ? mt : mt + dy;
	float br = dx > 0 ? mr + dx : mr;
	float bb = dy > 0 ? mb + dy : mb;



	if (br < sl || bl > sr || bb < st || bt > sb) return;
	if (dx == 0 && dy == 0) return;

	if (dx > 0)
	{
		dx_entry = sl - mr;
		dx_exit = sr - ml;
	}
	else if (dx < 0)
	{
		dx_entry = sr - ml;
		dx_exit = sl - mr;
	}


	if (dy > 0)
	{
		dy_entry = st - mb;
		dy_exit = sb - mt;
	}
	else if (dy < 0)
	{
		dy_entry = sb - mt;
		dy_exit = st - mb;
	}

	if (dx == 0)
	{
		tx_entry = -99999999999;
		tx_exit = 99999999999;
	}
	else
	{
		tx_entry = dx_entry / dx;
		tx_exit = dx_exit / dx;
	}

	if (dy == 0)
	{
		ty_entry = -99999999999;
		ty_exit = 99999999999;
	}
	else
	{
		ty_entry = dy_entry / dy;
		ty_exit = dy_exit / dy;
	}


	if ((tx_entry < 0.0f && ty_entry < 0.0f) || tx_entry > 1.0f || ty_entry > 1.0f) return;

	t_entry = max(tx_entry, ty_entry);
	t_exit = min(tx_exit, ty_exit);

	if (t_entry > t_exit) return;

	//t = t_entry;

	if (tx_entry > ty_entry)
	{
		ny = 0.0f;
		dx > 0 ? nx = -1.0f : nx = 1.0f;
	}
	else
	{
		nx = 0.0f;
		dy > 0 ? ny = -1.0f : ny = 1.0f;
	}

	/*if (obj->GetDirection_l() == false && obj->GetDirection_t() == true && obj->GetDirection_r() == false && obj->GetDirection_b() == false)
	{
		if (ny != -1)
			return;
	}
	if (obj->GetDirection_l() == false && obj->GetDirection_t() == false && obj->GetDirection_r() == false && obj->GetDirection_b() == false)
	{
		if (nx != 0 || ny != 0)
			return;
	}*/

	t = t_entry;
}

LPCOEVENT Colision::SweptAABBEx(LPOBJECT obj, DWORD dt)
{
	float objL, objT, objR, objB;
	float chaL, chaT, chaR, chaB;
	float time, nx, ny;
	float objvx, objvy;
	objL = obj->GetCollisionBox().left;
	objT = obj->GetCollisionBox().top;
	objR = obj->GetCollisionBox().right;
	objB = obj->GetCollisionBox().bottom;
	objvx = obj->GetVelocity().x;
	objvy = obj->GetVelocity().y;
	float objdx = objvx * dt;
	float objdy = objvy * dt;
	float dx = character->GetVelocity().x * dt - objdx;
	float dy = character->GetVelocity().y * dt - objdy;
	chaL = character->GetCollisionBox().left;
	chaT = character->GetCollisionBox().top;
	chaR = character->GetCollisionBox().right;
	chaB = character->GetCollisionBox().bottom;
	this->SweppAABB(chaL, chaT, chaR, chaB, dx, dy, objL, objT, objR, objB, time, nx, ny, obj);
	LPCOEVENT e = new CCollisionEvent(time, nx, ny, obj);
	return e;
}

void Colision::init(LPOBJECT obj, vector<LPOBJECT> ListObj)
{
	this->character = obj;
	this->objects = ListObj;
}

void Colision::CalcPotentialCollisions(vector<LPOBJECT>* coObjects, vector<LPCOEVENT>& coEvents, DWORD dt)
{
	for (UINT i = 0; i < coObjects->size(); i++)
	{
		LPCOEVENT e = SweptAABBEx(coObjects->at(i), dt);

		if (e->t >= 0 && e->t <= 1.0f)
			coEvents.push_back(e);
		else
			delete e;
	}
}

void Colision::FilterCollision(vector<LPCOEVENT>& coEvents, vector<LPCOEVENT>& coEventsResult, float& min_tx, float& min_ty, float& nx, float& ny)
{
	min_tx = 1.0f;
	min_ty = 1.0f;
	int min_ix = -1;
	int min_iy = -1;

	nx = 0.0f;
	ny = 0.0f;

	coEventsResult.clear();

	for (UINT i = 0; i < coEvents.size(); i++)
	{
		LPCOEVENT c = coEvents[i];

		if (c->t < min_tx && c->nx != 0) {
			min_tx = c->t; nx = c->nx; min_ix = i;
		}

		if (c->t < min_ty && c->ny != 0) {
			min_ty = c->t; ny = c->ny; min_iy = i;
		}
	}

	if (min_ix >= 0) coEventsResult.push_back(coEvents[min_ix]);
	if (min_iy >= 0) coEventsResult.push_back(coEvents[min_iy]);
}