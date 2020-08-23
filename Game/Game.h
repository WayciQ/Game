#pragma once
#include <Windows.h>
#include <d3d9.h>
#include <d3dx9.h>

class Game
{
	static Game* __instance;
	HWND hWnd;
	LPDIRECT3D9 d3d = NULL;
	LPDIRECT3DDEVICE9 d3ddv = NULL;

	LPDIRECT3DSURFACE9 backBuffer = NULL;
	LPD3DXSPRITE spriteHandler = NULL;
public: 
	void INIT(HWND hWnd);
	void DRAW(float x, float y, LPDIRECT3DTEXTURE9 texture);
	void DRAW(float x, float y, LPDIRECT3DTEXTURE9 texture, int left, int top, int right, int bottom);
	LPDIRECT3DTEXTURE9 LOADTEXTURE(LPCWSTR texturePath);
	~Game();
	LPDIRECT3DDEVICE9 GETDIRECT3DDEVICE() { return this->d3ddv; }
	LPDIRECT3DSURFACE9 GETBACKBUFFER() { return backBuffer; }
	LPD3DXSPRITE GETSPRITEHANDLER() { return this->spriteHandler; }

	static Game* GETINSTANCE();
};

