#include "GameObject.h"
#include <d3dx9.h>
#include "Game.h"

GameObject::GameObject(LPCWSTR texturePath) {
	x = y = 0;
	texture = Game::GETINSTANCE()->LOADTEXTURE(texturePath);
}
void GameObject::UPDATE(DWORD dt) {

}

void GameObject::RENDER() {
	Game::GETINSTANCE()->DRAW(x, y, texture);
}

GameObject:: ~GameObject() {
	if (texture != NULL) {
		texture->Release();
	}
}
void Superman::UPDATE(DWORD dt) {
	x += 0.1f * dt;
	if (x > 320) {
		x = 0;
	}
}