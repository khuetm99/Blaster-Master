#include "BaseCollision.h"


BaseCollisionEvent::BaseCollisionEvent(LPOBJECT &objA, LPOBJECT &objB, int objA_nx, int objA_ny, double dtime)
{
	this->dtime = dtime;
	this->objA = objA;
	this->objB = objB;
	this->objA_nx = objA_nx;
	this->objA_ny = objA_ny;
}


void BaseCollision::SweppAABB(float ml, float mt, float mr, float mb, float dx, float dy, float sl, float st, float sr, float sb, float& t, float& nx, float& ny, LPOBJECT& objA)
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
	if (objA->GetDirection_l() == false && objA->GetDirection_t() == true && objA->GetDirection_r() == false && objA->GetDirection_b() == false)
	{
		if (ny != -1)
			return;
	}
	if (objA->GetDirection_l() == false && objA->GetDirection_t() == false && objA->GetDirection_r() == false && objA->GetDirection_b() == false)
	{
		if (nx != 0 || ny != 0)
			return;
	}
	t = t_entry;
}

LPBASECOLLISIONEVENT BaseCollision::Calculate(LPOBJECT &objA, LPOBJECT &objB, double dt)
{

	float time, nx, ny;

	float objA_L = objA->GetCollisionBox().left;
	float objA_T = objA->GetCollisionBox().top;
	float objA_R = objA->GetCollisionBox().right;
	float objA_B = objA->GetCollisionBox().bottom;
	float objA_vx = objA->GetVelocity().x;
	float objA_vy = objA->GetVelocity().y;
	float objA_dx = objA_vx * dt;
	float objA_dy = objA_vy * dt;

	float objB_L = objB->GetCollisionBox().left;
	float objB_T = objB->GetCollisionBox().top;
	float objB_R = objB->GetCollisionBox().right;
	float objB_B = objB->GetCollisionBox().bottom;
	float objB_vx = objB->GetVelocity().x;
	float objB_vy = objB->GetVelocity().y;
	float objB_dx = objB_vx * dt;
	float objB_dy = objB_vy * dt;

	float dx = objA_dx - objB_dx;
	float dy = objA_dy - objB_dy;
	
	this->SweppAABB(objA_L, objA_T, objA_R, objA_B, dx, dy, objB_L, objB_T, objB_R, objB_B, time, nx, ny, objA);
	return new BaseCollisionEvent(objA, objB, nx, ny, time);
}


