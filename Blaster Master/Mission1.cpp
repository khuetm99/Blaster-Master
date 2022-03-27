#include "Mission1.h"

Mission1::Mission1()
{
	this->map = new Map1();

	this->car = Car::GetInstance();
	car->Init();

	this->jason = new Jason1(106, 1168);

	this->car->SetIsControlling(true);
	this->jason->SetIsControlling(false);
	//Global::GetInstance()->_Camera->AnchorTo(jason->GetPosition());
	//Global::GetInstance()->_Camera->SetLimitedZone(map->Border());

	// load doors from doors-map1.txt
	fstream file;
	file.open("textures/doors-map1.txt", ios::in);
	if (file.is_open()) {
		string line;
		while (getline(file, line)) {
			stringstream ssin(line);
			int id, type, left, top, right, bottom;
			ssin >> id;
			ssin >> type;
			ssin >> left;
			ssin >> top;
			ssin >> right;
			ssin >> bottom;
			this->doors.push_back(new Door(type, left, top, right, bottom));
		}
		file.close(); 
	}
}

Mission1::~Mission1()
{

}


void Mission1::Update(DWORD dt)
{
	KeyEvents();

	SetCameraAnchoToCharacter();

	vector<LPOBJECT> objects = map->GetObjectsInCamera();

	this->car->Update(dt, &objects, &doors);
	this->jason->Update(dt, &objects, &doors);

	for each (LPDOOR door in this->doors)
	{
		door->Update(dt, &objects);
	}

	for each (LPOBJECT object in objects)
	{
		object->Update(dt, &objects);
	}



	// chuyen canh
	// car
	if (car->GetCollisionBoxCenter().x < map->Border().left ) {
		this->car->SetCenterPostion(D3DXVECTOR2(map->Border().right-10, car->GetCenterPostion().y));
	}
	if (car->GetCollisionBoxCenter().x > map->Border().right) {
		this->car->SetCenterPostion(D3DXVECTOR2(map->Border().left + 10, car->GetCenterPostion().y));
	}
	if (car->GetCollisionBoxCenter().y < map->Border().top) {
		this->car->SetCenterPostion(D3DXVECTOR2(car->GetCenterPostion().x, map->Border().bottom - 5));
	}
	if (car->GetCollisionBoxCenter().y > map->Border().bottom) {
		this->car->SetCenterPostion(D3DXVECTOR2(car->GetCenterPostion().x, map->Border().top + 5));
	}
	// jason
	if (jason->GetCollisionBoxCenter().x < map->Border().left) {
		this->jason->SetCenterPostion(D3DXVECTOR2(map->Border().right - 10, jason->GetCenterPostion().y));
	}
	if (jason->GetCollisionBoxCenter().x > map->Border().right) {
		this->jason->SetCenterPostion(D3DXVECTOR2(map->Border().left + 10, jason->GetCenterPostion().y));
	}
	if (jason->GetCollisionBoxCenter().y < map->Border().top) {
		this->jason->SetCenterPostion(D3DXVECTOR2(jason->GetCenterPostion().x, map->Border().bottom - 5));
	}
	if (jason->GetCollisionBoxCenter().y > map->Border().bottom) {
		this->jason->SetCenterPostion(D3DXVECTOR2(jason->GetCenterPostion().x, map->Border().top + 5));
	}
}

void Mission1::Render()
{
	vector<LPTILE> tiles = map->GetTilesInCamera();
	for each (LPTILE tile in tiles)
	{
		tile->Render();
	}

	vector<LPOBJECT> objects = map->GetObjectsInCamera();
	for each (LPOBJECT object in objects)
	{
		object->Render();
	}

	this->car->Render();
	this->jason->Render();

	for each (LPDOOR door in this->doors)
	{
		door->Render();
	}
}

void Mission1::KeyEvents()
{
	LPKEYBOARD keyboard = Global::GetInstance()->_Keyboard;

	bool keyShift = (keyboard->IsKeyPress(DIK_LSHIFT));

	float dx, dy;
	dx = abs(jason->GetCollisionBoxCenter().x - car->GetCollisionBoxCenter().x);
	dy = abs(jason->GetCollisionBoxCenter().y - car->GetCollisionBoxCenter().y);

	if (keyShift) {
		if (this->jason->IsControlling() && dx < 10 && dy < 5) {
			jason->SetIsControlling(false);
			car->SetIsControlling(true);

			car->OpenDoor();
			jason->IntoCar(car->GetCollisionBoxCenter());
			Global::GetInstance()->_Camera->AnchorTo(car->GetPosition());
		}
		else
		if(this->car->IsControlling()){
			car->SetIsControlling(false);
			jason->SetIsControlling(true);

			car->CloseDoor();
			jason->OutCar(car->GetCollisionBoxCenter(), car->GetDirection());
			Global::GetInstance()->_Camera->AnchorTo(jason->GetPosition());
		}
	}
}

void Mission1::SetCameraAnchoToCharacter()
{
	if (this->jason->IsControlling()) {
		Global::GetInstance()->_Camera->AnchorTo(jason->GetPosition());
	}
	else
	if (this->car->IsControlling()) {
		Global::GetInstance()->_Camera->AnchorTo(car->GetPosition());
	}
	
	Global::GetInstance()->_Camera->SetLimitedZone(map->Border());
}

void Mission1::SetInRuning(bool isRuning)
{
	this->isRuning = isRuning;
}

LPMAP1 Mission1::GetMap()
{
	return this->map;
}

bool Mission1::IsRuning()
{
	return isRuning;
}
