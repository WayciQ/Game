#include "Game.h"

Game* Game::__instance = NULL;
void Game::INIT(HWND hWnd) {
	LPDIRECT3D9 d3d = Direct3DCreate9(D3D_SDK_VERSION);

	this->hWnd - hWnd;

	D3DPRESENT_PARAMETERS d3dpp;

	ZeroMemory(&d3dpp, sizeof(d3dpp));

	d3dpp.Windowed = true;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
	d3dpp.BackBufferCount = 1;

	RECT r;

	GetClientRect(hWnd, &r);

	d3dpp.BackBufferHeight = r.bottom + 1;
	d3dpp.BackBufferWidth = r.right + 1;

	d3d->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp,
		&d3ddv);
	if (d3ddv == NULL) {
		return;
	}

	d3ddv->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &backBuffer);

	D3DXCreateSprite(d3ddv, &spriteHandler);
}
void Game::DRAW(float x, float y, LPDIRECT3DTEXTURE9 texture) {
	D3DXVECTOR3 p(x, y, 0);
	spriteHandler->Draw(texture, NULL, NULL, &p, D3DCOLOR_XRGB(255, 255, 255));
}

void Game::DRAW(float x, float y, LPDIRECT3DTEXTURE9 texture, int left, int top, int right, int bottom) {
	D3DXVECTOR3 p(x, y, 0);
	RECT r;
	r.left = left;
	r.right = right;
	r.top = top;
	r.bottom = bottom;
	spriteHandler->Draw(texture, &r, NULL, &p, D3DCOLOR_XRGB(255, 255, 255));
}
LPDIRECT3DTEXTURE9 Game::LOADTEXTURE(LPCWSTR texturePath) {
	D3DXIMAGE_INFO info;
	LPDIRECT3DTEXTURE9 texture;
	HRESULT result = D3DXGetImageInfoFromFile(texturePath, &info);
	if (result != D3D_OK) {
		return NULL;
	}
	LPDIRECT3DDEVICE9 d3ddv = Game::GETINSTANCE()->GETDIRECT3DDEVICE();
	result = D3DXCreateTextureFromFileEx(
		d3ddv,								// Pointer to Direct3D device object
		texturePath,						// Path to the image to load
		info.Width,							// Texture width
		info.Height,						// Texture height
		1,
		D3DUSAGE_DYNAMIC,
		D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		D3DCOLOR_XRGB(255, 255, 255),			// Transparent color
		&info,
		NULL,
		&texture);								// Created texture pointer

	if (result != D3D_OK)
	{
		
		return NULL;
	}
	return texture;
}

Game::~Game() {
	if (spriteHandler != NULL) spriteHandler->Release();
	if (backBuffer != NULL) backBuffer->Release();
	if (d3ddv != NULL) d3ddv->Release();
	if (d3d != NULL) d3d->Release();
}

Game* Game::GETINSTANCE() {
	if (__instance == NULL) __instance = new Game();
	return __instance;
}