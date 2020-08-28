#include "Textures.h"
#include <Windows.h>

#include <d3d9.h>
#include <d3dx9.h>

#include "Game.h"

Textures* Textures::__instance = NULL;

Textures::Textures() {

}

Textures* Textures::GetInstance() {
	if (__instance == NULL)  __instance = new Textures();
	return __instance;
}
void Textures::Add(int id, LPCWSTR filePath, D3DCOLOR transparentColor) {
	textures[id] = Game::GETINSTANCE()->LOADTEXTURE(filePath);
}

LPDIRECT3DTEXTURE9 Textures::Get(unsigned int i) {
	return textures[i];
}