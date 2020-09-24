#pragma once

#include <d3dx9.h>
#include <unordered_map>
using namespace std;
class Textures
{
	static Textures* __instance;

	unordered_map<int, LPDIRECT3DTEXTURE9> textures;
public:
	Textures();
	void Add(int id, LPCWSTR filePath, D3DCOLOR stransparentColer);
	LPDIRECT3DTEXTURE9 Get(unsigned int i);
	static Textures* GetInstance();
};