#include "Mission2.h"

Mission2::Mission2()
{
	this->map = new Map2();

	this->jason = Jason2::GetInstance();
	//Boss* Boss::_instance = new Boss();
	this->boss = Boss::GetInstance();

	//Global::GetInstance()->_Camera->AnchorTo(jason->GetPosition());
	//Global::GetInstance()->_Camera->SetLimitedZone(map->Border());

	// load doors from doors-map2.txt
	fstream file;
	file.open("textures/doors-map2.txt", ios::in);
	if (file.is_open()) {
		string line;
		while (getline(file, line)) {
			stringstream ssin(line);
			int id, map, left, top, right, bottom;
			ssin >> id;
			ssin >> map;
			ssin >> left;
			ssin >> top;
			ssin >> right;
			ssin >> bottom;
			this->doors.push_back(new Door(map, left, top, right, bottom));
		}
		file.close();
	}
}

Mission2::~Mission2()
{

}


void Mission2::Update(DWORD dt)
{
	KeyEvents();

	if (jason->GetIsFightingWithBoss() == false) {
		SetCameraAnchoToCharacter();
	}	

	// toi boss
	if (jason->GetIsPassMission() == false && jason->GetCollisionBoxCenter().x < 910 && jason->GetCollisionBoxCenter().x > 880 && jason->GetCollisionBoxCenter().y < 798 && jason->GetCollisionBoxCenter().y > 700) {
		jason->GoToBoss();
	}



	vector<LPOBJECT> objects = map->GetObjectsInCamera();
	
	this->jason->Update(dt, &objects, &doors);
	this->boss->Update(dt, jason->GetListObjectBullets());
	

	for each (LPDOOR door in this->doors)
	{
		door->Update(dt, &objects);
	}

	for each (LPOBJECT object in objects)
	{
		object->Update(dt);
	}

}

void Mission2::Render()
{
	vector<LPTILE2> tiles = map->GetTilesInCamera();
	for each (LPTILE2 tile in tiles)
	{
		tile->Render();
	}

	vector<LPOBJECT> objects = map->GetObjectsInCamera();
	for each (LPOBJECT object in objects)
	{
		object->Render();
	}

	this->jason->Render();
	this->boss->Render();

	for each (LPDOOR door in this->doors)
	{
		door->Render();
	}
}

void Mission2::KeyEvents()
{
	LPKEYBOARD keyboard = Global::GetInstance()->_Keyboard;

	bool pressB = keyboard->IsKeyPress(DIK_B);
	if (pressB) {
		jason->GoToBoss();
	}
	
}

void Mission2::SetCameraAnchoToCharacter()
{
	Global::GetInstance()->_Camera->AnchorTo(jason->GetPosition());
	Global::GetInstance()->_Camera->SetLimitedZone(map->Border());
}

void Mission2::SetInRuning(bool isRuning)
{
	this->isRuning = isRuning;
}

LPMAP2 Mission2::GetMap()
{
	return this->map;
}

bool Mission2::IsRuning()
{
	return isRuning;
}
