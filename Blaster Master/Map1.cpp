#include "Map1.h"

Map1::Map1()
{
	cells = nullptr;
	tiles = nullptr;
	tileset = nullptr;

	LoadMap();
}


void Map1::LoadMap()
{
	this->tileset = new TileSet1();
	FILE* file = NULL;

	fopen_s(&file, "textures/area2.txt", "r");
	tiles = new LPTILE * [128];
	for (int i = 0; i < 128; i++)
	{
		tiles[i] = new LPTILE[128];
	}

	fscanf_s(file, "%f", &size.x);
	fscanf_s(file, "%f", &size.y);

	int r = 0;
	while (!feof(file))
	{
		for (int c = 0; c < 128; c++)
		{
			int tilesetID;
			fscanf_s(file, "%d", &tilesetID);
			D3DXVECTOR2 pos(c * tile_size, r * tile_size);
			tiles[c][r] = new Tile(tileset->GetTile(tilesetID), pos, D3DXVECTOR2(16,16));
		}
		r++;
	}

	// init cells
	cells = new LPCELL * [Cell_Count_X];
	for (int c = 0; c < Cell_Count_X; c++) {
		cells[c] = new LPCELL[Cell_Count_Y];
		for (int r = 0; r < Cell_Count_Y; r++) {
			cells[c][r] = new Cell();
		}
	}


	// load objects from file to cell
	// id type pos.x pos.y width height cell1.col cell1.row cell2.col cell2.row 
	FILE* fileObjects = NULL;
	fopen_s(&fileObjects, "textures/object-brick.txt", "r");

	while (!feof(fileObjects))
	{
		int id, posX, posY, width, height;
		int typeObj = NULL;
		fscanf_s(fileObjects, "%d", &id);
		fscanf_s(fileObjects, "%d", &typeObj);
		fscanf_s(fileObjects, "%d", &posX);
		fscanf_s(fileObjects, "%d", &posY);
		fscanf_s(fileObjects, "%d", &width);
		fscanf_s(fileObjects, "%d", &height);

		LPOBJECT obj = nullptr;

		if (typeObj == Object::TYPEOBJECT::BRICK) {
			obj = new Brick(posX, posY, width, height);
		}
		else
		if (typeObj == Object::TYPEOBJECT::WORM) {
			obj = new Worm(posX, posY, width, height);
		}
		else
		if (typeObj == Object::TYPEOBJECT::LAVA) {
			obj = new Lava(posX, posY, width, height);
		}
		else
		if (typeObj == Object::TYPEOBJECT::JUMPER) {
			obj = new Jumper(posX, posY, width, height);
		}
		else
		if (typeObj == Object::TYPEOBJECT::SKULL) {
			obj = new Skull(posX, posY, width, height);
		}
		else
			if (typeObj == Object::TYPEOBJECT::INSECT) {
				obj = new Insect(posX, posY, width, height);
			}


		if (obj != nullptr) {
			char c = fgetc(fileObjects);
			for (; c != '\n' && c != EOF; c = fgetc(fileObjects))
			{
				int c, r;
				fscanf_s(fileObjects, "%d", &c);
				fscanf_s(fileObjects, "%d", &r);
				DebugOut(L"c: %d d: %d\n", c, r);
				cells[c][r]->AddObject(obj);
			}
		}	
	}
}

D3DXVECTOR2 Map1::Size()
{
	return size;
}

RECT Map1::Border()
{
	RECT b;
	b.left = 0;
	b.top = 0;
	b.right = size.x;
	b.bottom = size.y;
	return b;
}



vector<LPOBJECT> Map1::GetObjectsInCamera()
{
	vector<LPOBJECT> objectsincamera;
	vector<LPCELL> cellsincamera;

	LPCAMERA camera = Global::GetInstance()->_Camera;
	int left = camera->Border().left;
	int top = camera->Border().top;
	int right = camera->Border().right;
	int botton = camera->Border().bottom;


	for (int r = top / Cell_Size; r < ((botton % Cell_Size) == 0 ? (botton / Cell_Size) : ((botton / Cell_Size) + 1)); r++)
	{
		for (int c = left / Cell_Size; c < ((right % Cell_Size) == 0 ? (right / Cell_Size) : ((right / Cell_Size) + 1)); c++)
		{
			cellsincamera.push_back(this->cells[c][r]);
		}
	}

	for (int i = 0; i < cellsincamera.size(); i++) {
		for each (LPOBJECT obj in cellsincamera[i]->GetObjects())
		{
			objectsincamera.push_back(obj);
		};
	}

	// remove duplicate object
	for (int i = 0; i < objectsincamera.size() - 1; i++) {
		for (int j = i + 1; j < objectsincamera.size(); j++) {
			if (objectsincamera.at(i) == objectsincamera.at(j))
			{
				objectsincamera.erase(objectsincamera.begin() + j);
				j--;
			}

		}
	}

	return objectsincamera;
}

vector<LPTILE> Map1::GetTilesInCamera() {

	LPCAMERA camera = Global::GetInstance()->_Camera;
	int left = camera->Border().left;
	int top = camera->Border().top;
	int right = camera->Border().right;
	int botton = camera->Border().bottom;

	vector<LPTILE> tilesincamera;

	for (int c = top / tile_size; c < ((botton % tile_size) == 0 ? (botton / tile_size) : ((botton / tile_size) + 1)); c++)
	{
		for (int r = left / tile_size; r < ((right % tile_size) == 0 ? (right / tile_size) : ((right / tile_size) + 1)); r++)
		{
			tilesincamera.push_back(tiles[r][c]);
		}
	}

	return tilesincamera;
}

void Cell::AddObject(LPOBJECT obj)
{
	objects.push_back(obj);
}
