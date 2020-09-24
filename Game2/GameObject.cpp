#include <d3dx9.h>
#include "Game.h"
#include "GameObject.h"
#include "Sprites.h"

#define SPEED 0.07f
GameObject::GameObject() {
	x = y = 0;
	vx = SPEED;
	vy = SPEED;
}

void GameObject::Update(DWORD dt) {
	
	
	if (currentState == 0) {
		x += vx * dt;
		y += vy * dt;
		if (y < 0 ) {
			vy = SPEED;
		}
		else if (y > 170 ) {
			vy = -SPEED;
		}
		else if (x < 0) {
			vx = -vx;
		}else if (x > 290) {
			vx = -vx;
		}
	}
	else {
		if (currentState > 0) {
			vx = SPEED;
		}
		else {
			vx = -SPEED;
		}
		x += vx * dt;

		if ((vx > 0 && x > 290) || (x < 0 && vx < 0)) {
			currentState = -currentState;
		}
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