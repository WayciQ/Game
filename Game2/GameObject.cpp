#include <d3dx9.h>
#include "Game.h"
#include "GameObject.h"
#include "Sprites.h"

GameObject::GameObject() {
	x = y = 0;
	vx = 0.07f;
}

void GameObject::Update(DWORD dt) {
	if (currentState > 0) {
		vx = 0.07f;
	}
	else {
		vx = -0.07f;
	}
	x += vx * dt;
	if ((vx > 0 && x > 290) || (x < 0 && vx < 0)) {
		vx = -vx;
		currentState = -currentState;
	} 
}
void GameObject::Render(int a, int b) {
	LPANIMATION ani;
	if (vx > 0) ani = Animations::GetInstance()->Get(a);
	else ani = Animations::GetInstance()->Get(b);
	ani->Render(x, y);
}

GameObject::~GameObject()
{
}