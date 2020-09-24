#include "Sprites.h"
#include "Game.h"

Sprites* Sprites::__instance = NULL;

Sprites* Sprites::GetInstance() {
	if (__instance == NULL) __instance = new Sprites();
	return __instance;
}

void Sprite::Draw(float x, float y) {
	Game* game = Game::GetInstance();
	game->Draw(x, y, texture, left, top, right, bottom);
}

void Sprites::Add(int id, int left, int top, int right, int bottom, LPDIRECT3DTEXTURE9 texture)
{
	LPSPRITE s = new Sprite(id, left, top, right, bottom, texture);
	sprites[id] = s;
}

LPSPRITE Sprites::Get(int id) {
	return sprites[id];
}

void Animation::Add(int spriteId, DWORD time) {
	int t = time;
	if (time == 0) t = this->defaultTime;

	LPSPRITE sprite = Sprites::GetInstance()->Get(spriteId);
	LPANIMATION_FRAME frame = new AnimationFrame(sprite, t);
	frames.push_back(frame);
}

void Animation::Render(float x, float y) {
	DWORD now = GetTickCount();
	if (currentFrame == -1) {
		currentFrame = 0;
		lastFrameTime = now;
	}
	else
	{
		DWORD t = frames[currentFrame]->GetTime();
		if (now - lastFrameTime > t) {
			currentFrame++;
			lastFrameTime = now;
			if (currentFrame == frames.size()) currentFrame = 0;
		}
	}

	frames[currentFrame]->GetSprite()->Draw(x, y);
}

Animations* Animations::__instance = NULL;

Animations* Animations::GetInstance() {
	if (__instance == NULL) __instance = new Animations();
	return __instance;
}

void Animations::Add(int id, LPANIMATION ani) {
	animations[id] = ani;
}

LPANIMATION Animations::Get(int id) {
	return animations[id];
}