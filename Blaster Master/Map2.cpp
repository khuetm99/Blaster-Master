#include "Map2.h"


Map2::Map2()
{
	tiles = nullptr;
	cells = nullptr;
	tileset = nullptr;

	LoadMap();
}


void Map2::LoadMap()
{
	this->tileset = new TileSet2();
	FILE* file = NULL;

	fopen_s(&file, "textures/area2over.txt", "r");
	tiles = new LPTILE2 * [128];
	for (int i = 0; i < 128; i++)
	{
		tiles[i] = new LPTILE2[128];
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
			tiles[c][r] = new Tile2(tileset->GetTile(tilesetID), pos, D3DXVECTOR2(16, 16));
		}
		r++;
	}

	cells = new LPCELL2 * [Cell_Count_X];
	for (int c = 0; c < Cell_Count_X; c++) {
		cells[c] = new LPCELL2[Cell_Count_Y];
		for (int r = 0; r < Cell_Count_Y; r++) {
			cells[c][r] = new Cell2();
		}
	}


	// load objects from file to cell
	// id type pos.x pos.y width height cell1.col cell1.row cell2.col cell2.row 
	FILE* fileObjects = NULL;
	fopen_s(&fileObjects, "textures/object-map2.txt", "r");

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
		if (typeObj == Object::TYPEOBJECT::TELEPORTER) {
			obj = new Teleporter(posX, posY, width, height);
		}
		else
		if (typeObj == Object::TYPEOBJECT::EYEBALL) {
			obj = new EyeBall(posX, posY, width, height);
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

D3DXVECTOR2 Map2::Size()
{
	return size;
}

RECT Map2::Border()
{
	RECT b;
	b.left = 0;
	b.top = 0;
	b.right = size.x;
	b.bottom = size.y;
	return b;
}



vector<LPOBJECT> Map2::GetObjectsInCamera()
{
	vector<LPOBJECT> objectsincamera;
	vector<LPCELL2> cellsincamera;

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
	if (objectsincamera.size() > 1) {
		for (int i = 0; i < (objectsincamera.size() - 1); i++) {
			for (int j = i + 1; j < objectsincamera.size(); j++) {
				if (objectsincamera.at(i) == objectsincamera.at(j))
				{
					objectsincamera.erase(objectsincamera.begin() + j);
					j--;
				}

			}
		}
	}
	
	return objectsincamera;
}

vector<LPTILE2> Map2::GetTilesInCamera() {

	LPCAMERA camera = Global::GetInstance()->_Camera;
	int left = camera->Border().left;
	int top = camera->Border().top;
	int right = camera->Border().right;
	int botton = camera->Border().bottom;

	vector<LPTILE2> tilesincamera;

	for (int c = top / tile_size; c < ((botton % tile_size) == 0 ? (botton / tile_size) : ((botton / tile_size) + 1)); c++)
	{
		for (int r = left / tile_size; r < ((right % tile_size) == 0 ? (right / tile_size) : ((right / tile_size) + 1)); r++)
		{
			tilesincamera.push_back(tiles[r][c]);
		}
	}

	return tilesincamera;
}

void Cell2::AddObject(LPOBJECT obj)
{
	objects.push_back(obj);
}

