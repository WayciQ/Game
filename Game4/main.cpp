/* =============================================================
	INTRODUCTION TO GAME PROGRAMMING SE102

	SAMPLE 04 - COLLISION

	This sample illustrates how to:

		1/ Implement SweptAABB algorithm between moving objects
		2/ Implement a simple (yet effective) collision frame work

	Key functions:
		CGame::SweptAABB
		CGameObject::SweptAABBEx
		CGameObject::CalcPotentialCollisions
		CGameObject::FilterCollision

		CGameObject::GetBoundingBox

================================================================ */

#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>

#include "debug.h"
#include "Game.h"
#include "GameObject.h"
#include "Textures.h"

#include "Mario.h"
#include "Brick.h"
#include "Goomba.h"

#define WINDOW_CLASS_NAME L"SampleWindow"
#define MAIN_WINDOW_TITLE L"04 - Collision"

#define BACKGROUND_COLOR D3DCOLOR_XRGB(255, 255, 200)
#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240

#define MAX_FRAME_RATE 120

#define ID_TEX_MARIO 0
#define ID_TEX_MARIO 1

#define ID_TEX_ENEMY 10
#define ID_TEX_MISC 20


Game* game;
Mario* mario;
Goomba* goomba;

vector<LPGAMEOBJECT> objects;

class CSampleKeyHander : public KeyEventHandler
{
	virtual void KeyState(BYTE* states);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);
};

CSampleKeyHander* keyHandler;

void CSampleKeyHander::OnKeyDown(int KeyCode)
{
	DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);
	switch (KeyCode)
	{
	case DIK_S:
		mario->SetState(MARIO_STATE_JUMP);
		break;
	case DIK_DOWN:
		mario->SetState(MARIO_STATE_SIT);
		break;
	case DIK_D:
		if (mario->IsFighting()) {
			mario->SetState(MARIO_STATE_FIGHT);
		}
		break;
	case DIK_A: // reset
		mario->SetState(MARIO_STATE_IDLE);
		mario->SetLevel(MARIO_LEVEL_RACCOON);
		mario->SetPosition(50.0f, 100.0f);
		mario->SetSpeed(0, 0);
		break;
	}
}

void CSampleKeyHander::OnKeyUp(int KeyCode)
{
	switch (KeyCode)
	{
	case DIK_DOWN:
		mario->SetState(MARIO_STATE_STAND);
		mario->SetState(MARIO_STATE_IDLE);
		break;
	case DIK_D:
		mario->SetState(MARIO_STATE_NOT_FIGHT);
		mario->SetState(MARIO_STATE_IDLE);
		break;
	}

	DebugOut(L"[INFO] KeyUp: %d\n", KeyCode);
}

void CSampleKeyHander::KeyState(BYTE* states)
{
	
	 
	if (game->IsKeyDown(DIK_RIGHT))
	{
		if (game->IsKeyDown(DIK_S)) {
			if(!mario->IsJumping())
				mario->SetState(MARIO_STATE_JUMP_RIGHT);
			DebugOut(L"[INFO]jump: %d\n", mario->GetState());
		}
		else if (game->IsKeyDown(DIK_DOWN)) {
			mario->SetState(MARIO_STATE_SIT_PRESS);
		}
		else {
			mario->SetState(MARIO_STATE_WALKING_RIGHT);
			DebugOut(L"[INFO] right %d\n", mario->GetState());
		}
			
	}
	else if (game->IsKeyDown(DIK_LEFT))
	{
		if (game->IsKeyDown(DIK_S)) {
			if (!mario->IsJumping())
				mario->SetState(MARIO_STATE_JUMP_LEFT);
			DebugOut(L"[INFO]jump: %d\n", mario->GetState());
		}
		else if (game->IsKeyDown(DIK_DOWN)) {
			mario->SetState(MARIO_STATE_SIT_PRESS);
		}
		else{
			mario->SetState(MARIO_STATE_WALKING_LEFT);
			DebugOut(L"[INFO] right %d\n", mario->GetState());
		}
			
	}
	else if (game->IsKeyDown(DIK_D)) {
		if (!mario->IsFighting())
			mario->SetState(MARIO_STATE_FIGHT);
	}
	else if (game->IsKeyDown(DIK_DOWN)) {
			mario->SetState(MARIO_STATE_SIT_PRESS);
	}
	else if (! mario->IsJumping()) {
		mario->SetState(MARIO_STATE_IDLE);
		//DebugOut(L"[INFO] ide %d\n", mario->GetState());
	}
		else if (mario->GetState() == MARIO_STATE_DIE) return;
	
}

LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message) {
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

/*
	Load all game resources
	In this example: load textures, sprites, animations and mario object

	TO-DO: Improve this function by loading texture,sprite,animation,object from file
*/
void LoadResources()
{
	Textures* textures = Textures::GetInstance();
	textures->Add(ID_TEX_MISC, L"textures\\misc.png", D3DCOLOR_XRGB(176, 224, 248));
	textures->Add(ID_TEX_ENEMY, L"textures\\enemies.png", D3DCOLOR_XRGB(3, 26, 110));
	textures->Add(ID_TEX_BBOX, L"textures\\bbox.png", D3DCOLOR_XRGB(255, 255, 255));
	textures->Add(ID_TEX_MARIO, L"textures\\mario2.png", D3DCOLOR_XRGB(255, 255, 255));

	Sprites* sprites = Sprites::GetInstance();
	Animations* animations = Animations::GetInstance();

	LPDIRECT3DTEXTURE9 texMario = textures->Get(ID_TEX_MARIO);

	// raccoon 


	sprites->Add(13101, 211, 442, 233, 471, texMario); // IDLE RIGHT
	sprites->Add(13102, 285, 442, 308, 471, texMario); // walk
	sprites->Add(13103, 313, 442, 337, 471, texMario);
	sprites->Add(13104, 343, 442, 367, 471, texMario); // jump right
	sprites->Add(13105, 210, 602, 234, 630, texMario);	// fall right
	sprites->Add(13106, 371, 447, 394, 466, texMario); // sit

	sprites->Add(13201, 184, 442, 206, 471, texMario); //idle left
	sprites->Add(13202, 101, 442, 124, 471, texMario); //walk
	sprites->Add(13203, 69, 442, 93, 471, texMario);
	sprites->Add(13204, 44, 442, 68, 471, texMario);	//jump left
	sprites->Add(13205, 171, 602, 195, 630, texMario); // fall left
	sprites->Add(13206, 11, 447, 34, 466, texMario);	//sit

	sprites->Add(13301, 209, 442, 233, 471, texMario); // fight idle right
	sprites->Add(13302, 235, 442, 259, 471, texMario); // fight 
	sprites->Add(13303, 347, 482, 371, 511, texMario);	// face
	sprites->Add(13304, 137, 442, 170, 471, texMario);	// fight left
	sprites->Add(13305, 382, 482, 406, 511, texMario);	// back

	sprites->Add(13401, 176, 442, 206, 471, texMario);
	sprites->Add(13402, 138, 442, 170, 471, texMario);
	sprites->Add(13403, 348, 482, 371, 511, texMario);
	sprites->Add(13404, 235, 442, 259, 471, texMario);
	sprites->Add(13405, 380, 482, 406, 511, texMario);

	LPDIRECT3DTEXTURE9 texMisc = textures->Get(ID_TEX_MISC);
	sprites->Add(20001, 408, 225, 424, 241, texMisc);

	LPDIRECT3DTEXTURE9 texEnemy = textures->Get(ID_TEX_ENEMY);
	sprites->Add(30001, 5, 14, 21, 29, texEnemy);
	sprites->Add(30002, 25, 14, 41, 29, texEnemy);

	sprites->Add(30003, 45, 21, 61, 29, texEnemy); // die sprite

	LPANIMATION ani;
	

	ani = new Animation(100);	// idle right
	ani->Add(13101);
	animations->Add(101, ani);

	ani = new Animation(100);	// idle left
	ani->Add(13201);
	animations->Add(102, ani);

	ani = new Animation(100);	// walk right
	ani->Add(13101);
	ani->Add(13102);
	ani->Add(13103);
	ani->Add(13102);
	animations->Add(201, ani);

	ani = new Animation(100);	// walk left
	ani->Add(13201);
	ani->Add(13202);
	ani->Add(13203);
	ani->Add(13202);
	animations->Add(202, ani);
	
	ani = new Animation(100);	// jump right
	ani->Add(13104);
	animations->Add(310, ani);

	ani = new Animation(100);	// fall right
	ani->Add(13205);
	animations->Add(311, ani); 
	
	ani = new Animation(100);	// jump Left
	ani->Add(13204);
	animations->Add(320, ani);

	ani = new Animation(100);	// fall Left
	ani->Add(13205);
	animations->Add(321, ani);
	
	ani = new Animation(100);	// sit right
	ani->Add(13106);
	animations->Add(330, ani);
	
	ani = new Animation(100);	// sit left
	ani->Add(13206);
	animations->Add(340, ani);

	ani = new Animation(100);	// fight right
	ani->Add(13301);
	ani->Add(13302);
	ani->Add(13303);
	ani->Add(13304);
	ani->Add(13305);
	ani->Add(13302);
	animations->Add(401, ani);

	ani = new Animation(100);	// fight left
	ani->Add(13401);
	ani->Add(13402);
	ani->Add(13403);
	ani->Add(13404);
	ani->Add(13405);
	ani->Add(13402);
	animations->Add(402, ani);


	ani = new Animation(100);		// brick
	ani->Add(20001);
	animations->Add(801, ani);

	ani = new Animation(300);		// Goomba walk
	ani->Add(30001);
	ani->Add(30002);
	animations->Add(701, ani);

	ani = new Animation(1000);		// Goomba dead
	ani->Add(30003);
	animations->Add(702, ani);

	ani = new Animation(100);	// Mario die
	ani->Add(10099);
	animations->Add(599, ani);

	mario = new Mario();

	mario->AddAnimation(101);		// idle right
	mario->AddAnimation(102);		// idle left

	mario->AddAnimation(201);		// walk right
	mario->AddAnimation(202);		// walk left
	
	mario->AddAnimation(310);		// jump right
	mario->AddAnimation(311);		// fall right

	mario->AddAnimation(320);		// jump left
	mario->AddAnimation(321);		// fall left

	mario->AddAnimation(330);		// sit right
	mario->AddAnimation(340);		// sit left

	mario->AddAnimation(401); 		// fight right
	mario->AddAnimation(402);		// fight lefty
	mario->AddAnimation(599);
	mario->SetPosition(50.0f, 100);
	objects.push_back(mario);

	/*for (int i = 0; i < 5; i++)
	{
		Brick* brick = new Brick();
		brick->AddAnimation(801);
		brick->SetPosition(100.0f + i * 60.0f, 74.0f);
		objects.push_back(brick);

		brick = new Brick();
		brick->AddAnimation(801);
		brick->SetPosition(100.0f + i * 60.0f, 90.0f);
		objects.push_back(brick);

		brick = new Brick();
		brick->AddAnimation(801);
		brick->SetPosition(84.0f + i * 60.0f, 90.0f);
		objects.push_back(brick);
	}*/


	for (int i = 0; i < 30; i++)
	{
		Brick* brick = new Brick();
		brick->AddAnimation(801);
		brick->SetPosition(0 + i * 16.0f, 150);
		objects.push_back(brick);
	}

	// and Goombas 
	for (int i = 0; i < 4; i++)
	{
		goomba = new Goomba();
		goomba->AddAnimation(701);
		goomba->AddAnimation(702);
		goomba->SetPosition(200 + i * 60, 135);
		goomba->SetState(GOOMBA_STATE_WALKING);
		objects.push_back(goomba);
	}

}

/*
	Update world status for this frame
	dt: time period between beginning of last frame and beginning of this frame
*/
void Update(DWORD dt)
{
	// We know that Mario is the first object in the list hence we won't add him into the colliable object list
	// TO-DO: This is a "dirty" way, need a more organized way 

	vector<LPGAMEOBJECT> coObjects;
	for (int i = 1; i < objects.size(); i++)
	{
		coObjects.push_back(objects[i]);
		if (objects[i]->GetState() == GOOMBA_STATE_DIE) {
			objects.erase(objects.begin()+i);
		}
	}

	for (int i = 0; i < objects.size(); i++)
	{
		objects[i]->Update(dt, &coObjects);
	}


	// Update camera to follow mario
	float cx, cy;
	mario->GetPosition(cx, cy);

	cx -= SCREEN_WIDTH / 2;
	cy -= SCREEN_HEIGHT / 2;

	Game::GetInstance()->SetCamPos(cx, 0.0f /*cy*/);
}

/*
	Render a frame
*/
void Render()
{
	LPDIRECT3DDEVICE9 d3ddv = game->GetDirect3DDevice();
	LPDIRECT3DSURFACE9 bb = game->GetBackBuffer();
	LPD3DXSPRITE spriteHandler = game->GetSpriteHandler();

	if (d3ddv->BeginScene())
	{
		// Clear back buffer with a color
		d3ddv->ColorFill(bb, NULL, BACKGROUND_COLOR);

		spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);

		for (int i = 0; i < objects.size(); i++)
			objects[i]->Render();

		spriteHandler->End();
		d3ddv->EndScene();
	}

	// Display back buffer content to the screen
	d3ddv->Present(NULL, NULL, NULL, NULL);
}

HWND CreateGameWindow(HINSTANCE hInstance, int nCmdShow, int ScreenWidth, int ScreenHeight)
{
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);

	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.hInstance = hInstance;

	wc.lpfnWndProc = (WNDPROC)WinProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hIcon = NULL;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = WINDOW_CLASS_NAME;
	wc.hIconSm = NULL;

	RegisterClassEx(&wc);

	HWND hWnd =
		CreateWindow(
			WINDOW_CLASS_NAME,
			MAIN_WINDOW_TITLE,
			WS_OVERLAPPEDWINDOW, // WS_EX_TOPMOST | WS_VISIBLE | WS_POPUP,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			ScreenWidth,
			ScreenHeight,
			NULL,
			NULL,
			hInstance,
			NULL);

	if (!hWnd)
	{
		OutputDebugString(L"[ERROR] CreateWindow failed");
		DWORD ErrCode = GetLastError();
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return hWnd;
}

int Run()
{
	MSG msg;
	int done = 0;
	DWORD frameStart = GetTickCount();
	DWORD tickPerFrame = 1000 / MAX_FRAME_RATE;

	while (!done)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) done = 1;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		DWORD now = GetTickCount();

		// dt: the time between (beginning of last frame) and now
		// this frame: the frame we are about to render
		DWORD dt = now - frameStart;

		if (dt >= tickPerFrame)
		{
			frameStart = now;

			game->ProcessKeyboard();

			Update(dt);
			Render();
		}
		else
			Sleep(tickPerFrame - dt);
	}

	return 1;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	HWND hWnd = CreateGameWindow(hInstance, nCmdShow, SCREEN_WIDTH, SCREEN_HEIGHT);

	game = Game::GetInstance();
	game->Init(hWnd);

	keyHandler = new CSampleKeyHander();
	game->InitKeyboard(keyHandler);


	LoadResources();

	SetWindowPos(hWnd, 0, 0, 0, SCREEN_WIDTH * 2, SCREEN_HEIGHT * 2, SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOZORDER);

	Run();

	return 0;
}