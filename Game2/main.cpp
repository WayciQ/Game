#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>

#include "Game.h"
#include "GameObject.h"
#include "Textures.h"

#define WINDOW_CLASS_NAME L"SampleWindow"
#define MAIN_WINDOW_TITLE L"02 - Sprite animation"
#define BACKGROUND_COLOR D3DCOLOR_XRGB(200, 200, 255)
#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240

#define MAX_FRAME_RATE 60
#define ID_TEX_AT 0
#define ID_TEX_CC 0
Game* game;

GameObject* AT;
GameObject* CC;

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
	textures->Add(ID_TEX_AT, L"mario.png", D3DCOLOR_XRGB(176, 224, 248));

	Sprites* Sprites = Sprites::GetInstance();
	LPDIRECT3DTEXTURE9 texAT = textures->Get(ID_TEX_AT);

	Sprites->Add(1, 246, 394, 260, 421, texAT);
	Sprites->Add(2, 276, 394, 291, 421, texAT);
	Sprites->Add(3, 306, 394, 322, 421, texAT);

	Sprites->Add(4, 186, 394, 201, 421, texAT); 
	Sprites->Add(5, 156, 394, 171, 421, texAT);
	Sprites->Add(6, 125, 394, 141, 421, texAT);

	Sprites->Add(7, 243, 634, 264, 662, texAT);
	Sprites->Add(8, 272, 634, 295, 662, texAT);
	Sprites->Add(9, 302, 634, 324, 662, texAT);

	Sprites->Add(10, 181, 634, 204, 662, texAT);
	Sprites->Add(11, 151, 634, 174, 662, texAT);
	Sprites->Add(12, 121, 634, 143, 662, texAT);
	Animations* animations = Animations::GetInstance();
	LPANIMATION ani;
	ani = new Animation(100);
	ani->Add(1);
	ani->Add(2);
	ani->Add(3);
	animations->Add(500, ani);
	ani = new Animation(100);
	ani->Add(4);
	ani->Add(5);
	ani->Add(6);
	animations->Add(501, ani);
	ani = new Animation(100);
	ani->Add(7);
	ani->Add(8);
	ani->Add(9);
	animations->Add(502, ani);
	ani = new Animation(100);
	ani->Add(10);
	ani->Add(11);
	ani->Add(12);
	animations->Add(503, ani);


	AT = new GameObject();
	AT->SetPosition(75.0f, 100.0f);
	AT->SetState(1);
	CC = new GameObject();
	CC->SetPosition(75.0f, 100.0f);
	CC->SetState(-1);
}
void Update(DWORD dt) {
	AT->Update(dt);
	CC->Update(dt);
}
void Render() {
	LPDIRECT3DDEVICE9 d3ddv = game->GETDIRECT3DDEVICE();
	LPDIRECT3DSURFACE9 bb = game->GETBACKBUFFER();
	LPD3DXSPRITE spriteHandler = game->GETSPRITEHANDLER();
	if (d3ddv->BeginScene())
	{
		// Clear back buffer with a color
		d3ddv->ColorFill(bb, NULL, BACKGROUND_COLOR);

		spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);
		AT->Render(500,501);
		CC->Render(502,503);
		spriteHandler->End();
		d3ddv->EndScene();
	}
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

	game = Game::GETINSTANCE();
	game->INIT(hWnd);

	LoadResources();
	Run();

	return 0;
}