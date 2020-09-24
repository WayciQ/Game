#pragma once
#include <Windows.h>
#include <d3dx9.h>
#include <vector>

#include "Sprites.h"

using namespace std;
class GameObject
{
	float x;
	float y;
	float vx;
	float vy;
	int currentState;

	vector<LPANIMATION> animations;
public:
	void SetPosition(float x, float y) { 
		this->x = x;
		this->y = y;
	}
	void SetState(int state) { this->currentState = state; }

	GameObject();
	void Update(DWORD dt);
	void Render(int a, int b);
	~GameObject();
};



