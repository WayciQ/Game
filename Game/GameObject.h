#pragma once
#include <Windows.h>
#include <d3dx9.h>
class GameObject
{
protected :
	float x;
	float y;
	LPDIRECT3DTEXTURE9 texture;
public:
	void SET_POSITION(float x, float y) {
		this->x = x;
		this->y = y;
	}
	GameObject(LPCWSTR texturePath);
	void UPDATE(DWORD);
	void RENDER();
	~GameObject();
	
};
typedef GameObject* LPGAMEOBJECT;

class Superman : public GameObject {
public:
	Superman(LPCWSTR texturePath) : GameObject(texturePath) {};
	void UPDATE(DWORD dt);
};

