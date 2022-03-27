#include "Game.h"


Game* Game::_instance = NULL;

void Game::Init(HWND hWnd)
{

	LPDIRECT3D9 d3d = Direct3DCreate9(D3D_SDK_VERSION);

	D3DPRESENT_PARAMETERS d3dpp;

	ZeroMemory(&d3dpp, sizeof(d3dpp));

	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
	d3dpp.BackBufferCount = 1;

	RECT r;
	GetClientRect(hWnd, &r);	// retrieve Window width & height 

	d3dpp.BackBufferHeight = r.bottom + 1;
	d3dpp.BackBufferWidth = r.right + 1;

	d3d->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp,
		&Global::GetInstance()->_D3DDV);

	if (Global::GetInstance()->_D3DDV == NULL)
	{
		OutputDebugString(L"[ERROR] CreateDevice failed\n");
		return;
	}
	Global::GetInstance()->_D3DDV->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &Global::GetInstance()->_BackBuffer);
	
	Global::GetInstance()->_FPS = 120;
	Global::GetInstance()->_HWND = hWnd;
	Global::GetInstance()->_Keyboard = new Keyboard(hWnd);
	Global::GetInstance()->_Camera = new Camera(0, 0, 300, 280);

	// Initialize sprite helper from Direct3DX helper library
	D3DXCreateSprite(Global::GetInstance()->_D3DDV, &Global::GetInstance()->_SpriteHandler);

	Textures::GetInstance()->Init();

	Boss::GetInstance()->Init();

	mission1 = new Mission1();
	mission2 = new Mission2();

	mission1->SetInRuning(true);
	mission2->SetInRuning(false);

}



void Game::LoadResource()
{
	
}

void Game::KeyEvents()
{

	LPKEYBOARD keyboard = Global::GetInstance()->_Keyboard;

	bool keyShift = keyboard->IsKeyPress(DIK_RSHIFT);

	if (keyShift) {
		if (mission1->IsRuning()) {
			mission1->SetInRuning(false);
			mission2->SetInRuning(true);
			mission2->SetCameraAnchoToCharacter();
		}
		else
		if (mission2->IsRuning()) {
			mission1->SetInRuning(true);
			mission2->SetInRuning(false);
			mission1->SetCameraAnchoToCharacter();
		}
	}
}

void Game::Run()
{
	MSG msg;
	int done = 0;
	DWORD frameStart = GetTickCount64();
	DWORD tickPerFrame = 1000 / 120;

	while (!done)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) done = 1;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		DWORD now = GetTickCount64();

		// dt: the time between (beginning of last frame) and now
		// this frame: the frame we are about to render
		DWORD dt = now - frameStart;

		if (dt >= tickPerFrame)
		{
			frameStart = now;
			Update(dt);
			Render();
		}
		else
			Sleep(tickPerFrame - dt);
	}
}

void Game::Update(DWORD dt)
{
	Global::GetInstance()->_Keyboard->RecordKeyStates(dt);
	Global::GetInstance()->_Camera->Update(dt);

	KeyEvents();

	// chuyen man
	// qua man 2
	if (mission1->jason->GetIsPassMission() == false && mission1->jason->GetCollisionBoxCenter().x < 1110 && mission1->jason->GetCollisionBoxCenter().x > 1090 && mission1->jason->GetCollisionBoxCenter().y < 705 && mission1->jason->GetCollisionBoxCenter().y > 688) {
		mission1->jason->SetIsPassMission(true);
		mission1->SetInRuning(false);
		mission2->SetInRuning(true);
		mission2->SetCameraAnchoToCharacter();
		mission1->jason->SetPostion(mission1->jason->GetPosition()->x + 20, mission1->jason->GetPosition()->y - 5);
	}
	else {
		mission1->jason->SetIsPassMission(false);
	}

	// ve man 1
	if (mission2->jason->GetIsPassMission() == false && mission2->jason->GetCollisionBoxCenter().x < 128 && mission2->jason->GetCollisionBoxCenter().x > 110 && mission2->jason->GetCollisionBoxCenter().y < 1920 && mission2->jason->GetCollisionBoxCenter().y > 1903) {
		mission2->jason->SetIsPassMission(true);
		mission2->SetInRuning(false);
		mission1->SetInRuning(true);
		mission1->SetCameraAnchoToCharacter();
		mission2->jason->SetPostion(mission2->jason->GetPosition()->x + 20, mission2->jason->GetPosition()->y);
	}
	else {
		mission2->jason->SetIsPassMission(false);
	}



	if (mission1->IsRuning()) {
		Global::GetInstance()->_Camera->SetLimitedZone(mission1->GetMap()->Border());
		mission1->Update(dt);
		return;
	}
	else
	if (mission2->IsRuning()) {
		Global::GetInstance()->_Camera->SetLimitedZone(mission2->GetMap()->Border());
		mission2->Update(dt);
		return;
	}

}


void Game::Render()
{
	if (Global::GetInstance()->_D3DDV->BeginScene())
	{
		Global::GetInstance()->_D3DDV->ColorFill((Global::GetInstance()->_BackBuffer), NULL, BACKGROUND_COLOR);
		Global::GetInstance()->_SpriteHandler->Begin(D3DXSPRITE_ALPHABLEND);

		if (mission1->IsRuning()) {
			mission1->Render();
		}
		else
		if (mission2->IsRuning()) {
			mission2->Render();
		}

		Global::GetInstance()->_SpriteHandler->End();
		Global::GetInstance()->_D3DDV->EndScene();
	}
	(Global::GetInstance()->_D3DDV)->Present(NULL, NULL, NULL, NULL);
}

void Game::End()
{
}


Game* Game::GetInstance()
{
	if (_instance == NULL) _instance = new Game();
	return _instance;
}

Game::~Game()
{
	if (Global::GetInstance()->_SpriteHandler != NULL) Global::GetInstance()->_SpriteHandler->Release();
	if (Global::GetInstance()->_BackBuffer != NULL) Global::GetInstance()->_BackBuffer->Release();
	if (Global::GetInstance()->_D3DDV != NULL) Global::GetInstance()->_D3DDV->Release();
}
