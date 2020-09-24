#include <d3dx9.h>

#include "debug.h"
#include "Game.h"
#include "GameObject.h"
#include "Sprites.h"

vector<LPANIMATION> GameObject::animations;

GameObject::GameObject() {
	x = y = 0;
	vx = vy = 0;
	nx = 1;
	ny = 0;
}

void GameObject::Update(DWORD dt) {
	x += vx * dt;
	y += vy * dt;
}
void GameObject::Render()
{
}

void GameObject::AddAnimation(int aniId)
{
	LPANIMATION ani = Animations::GetInstance()->Get(aniId);
	animations.push_back(ani);
}


GameObject::~GameObject()
{
}