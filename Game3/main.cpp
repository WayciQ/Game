#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>

#include "debug.h"
#include "Game.h"
#include "GameObject.h"
#include "Textures.h"
#include "Brick.h"
#include "Mario.h"
#define WINDOW_CLASS_NAME L"SampleWindow"
#define MAIN_WINDOW_TITLE L"02 - Sprite animation"

#define BACKGROUND_COLOR D3DCOLOR_XRGB(200, 200, 255)
#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240

#define MAX_FRAME_RATE 90

#define ID_TEX_MARIO 0
#define ID_TEX_ENEMY 10
#define ID_TEX_MISC 20

Game* game;
Brick* brick;
Mario* mario;


class SampleKeyHander : public KeyEventHandler
{
	virtual void KeyState(BYTE* states);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);
};

SampleKeyHander* keyHandler;

void SampleKeyHander::OnKeyDown(int KeyCode)
{
	DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);
	switch (KeyCode)
	{
	case DIK_SPACE:
		mario->SetState(MARIO_STATE_JUMP);
		DebugOut(L"[INFO] SPACEDOWN: %d\n", KeyCode);
		break;
	
	}

}

void SampleKeyHander::OnKeyUp(int KeyCode)
{
	//switch (KeyCode)
	//{
	//case DIK_RIGHT:
	//	if (mario->GetY() < 100.0f) {
	//		/*DebugOut(L"[a] Y : %f\n", mario->GetY());
	//		DebugOut(L"[a] RIGHTUp: %d\n", mario->GetState());*/
	//		mario->SetState(MARIO_STATE_WALKING_RIGHT);
	//	}else
	//		mario->SetState(MARIO_STATE_IDLE);
	//	break;
	//case DIK_LEFT:
	//	if (mario->GetY() < 100.0f) {
	//		/*DebugOut(L"[a] Y : %f\n", mario->GetY());
	//		DebugOut(L"[b] LEFTUp: %d\n", mario->GetState());*/
	//		mario->SetState(MARIO_STATE_WALKING_LEFT);
	//	}
	//	else
	//		mario->SetState(MARIO_STATE_IDLE); 
	//	break;
	//}
	DebugOut(L"[INFO] KeyUp: %d\n", KeyCode);
}

void SampleKeyHander::KeyState(BYTE* states)
{
	if (game->IsKeyDown(DIK_RIGHT))
		mario->SetState(MARIO_STATE_WALKING_RIGHT);
	else if (game->IsKeyDown(DIK_LEFT))
		mario->SetState(MARIO_STATE_WALKING_LEFT);
	else if (game->IsKeyDown(DIK_RIGHT) && game->IsKeyDown(DIK_SPACE))
		mario->SetState(MARIO_STATE_JUMP_RIGHT);
	else if (game->IsKeyDown(DIK_LEFT) && game->IsKeyDown(DIK_SPACE))
		mario->SetState(MARIO_STATE_JUMP_LEFT);
	else if(mario->GetNy() == 0)
	 mario->SetState(MARIO_STATE_IDLE);
	
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

void LoadResources() {
	Textures* textures = Textures::GetInstance();

	textures->Add(ID_TEX_MARIO, L"mario.png", D3DCOLOR_XRGB(255, 255, 255));
	textures->Add(ID_TEX_MISC, L"misc.png", D3DCOLOR_XRGB(255, 255, 255));
	Sprites* sprites = Sprites::GetInstance();
	Animations* animations = Animations::GetInstance();

	LPDIRECT3DTEXTURE9 texMario = textures->Get(ID_TEX_MARIO);
	LPDIRECT3DTEXTURE9 texMisc = textures->Get(ID_TEX_MISC);
	

	sprites->Add(10001, 245, 153, 260, 181, texMario);

	sprites->Add(10002, 274, 153, 291, 181, texMario);
	sprites->Add(10003, 304, 153, 321, 181, texMario);

	sprites->Add(10004, 364, 314, 383, 341, texMario);

	sprites->Add(10011, 185, 153, 200, 181, texMario);

	sprites->Add(10012, 153, 153, 171, 181, texMario);
	sprites->Add(10013, 123, 153, 142, 181, texMario);

	sprites->Add(10014, 34, 274, 51, 300, texMario);

	
	//sprites->Add(20001, 408, 225, 424, 241, texMisc);
	sprites->Add(20001, 299, 116, 316, 133, texMisc);
	sprites->Add(20002, 317, 225, 334, 241, texMisc);
	sprites->Add(20003, 335, 225, 352, 241, texMisc);
	sprites->Add(20004, 353, 225, 370, 241, texMisc);
	sprites->Add(20005, 371, 225, 388, 241, texMisc);
	LPANIMATION ani;

	ani = new Animation(100);
	ani->Add(10001);
	animations->Add(400, ani);

	ani = new Animation(100);
	ani->Add(10011);
	animations->Add(401, ani);


	ani = new Animation(100);
	ani->Add(10001);
	ani->Add(10002);
	ani->Add(10003);
	animations->Add(500, ani);

	ani = new Animation(100);
	ani->Add(10011);
	ani->Add(10012);
	ani->Add(10013);
	animations->Add(501, ani);

	ani = new Animation(100);
	ani->Add(10004);
	animations->Add(600, ani);

	ani = new Animation(100);
	ani->Add(10014);
	animations->Add(601, ani);

	ani = new Animation(100);
	ani->Add(20001);
	ani->Add(20002);
	ani->Add(20003);
	ani->Add(20004);
	ani->Add(20005);
	animations->Add(801, ani);

	mario = new Mario();
	mario->AddAnimation(400);		// idle right
	mario->AddAnimation(401);		// idle left
	mario->AddAnimation(500);		// walk right
	mario->AddAnimation(501);		// walk left
	mario->AddAnimation(600);		//jump right
	mario->AddAnimation(601);		//jupm left

	mario->SetPosition(0.0f, 100.0f);

	brick = new Brick();
	brick->AddAnimation(801);
	brick->SetPosition(0.0f, 100.0f);
	
}

/*
	Update world status for this frame
	dt: time period between beginning of last frame and beginning of this frame
*/
void Update(DWORD dt)
{
	mario->Update(dt);
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

		mario->Render();
		brick->Render();

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

	keyHandler = new SampleKeyHander();
	game->InitKeyboard(keyHandler);


	LoadResources();
	Run();

	return 0;
}
