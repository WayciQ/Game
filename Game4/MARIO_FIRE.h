#pragma once
#include "MARIO_FIRE.h"
#include "Textures.h"
#include "Game.h"
#include "Goomba.h"
#include "debug.h"

#define FIRE_SPEED 0.05f
#define FIRE_GRAVITY 0.001f
#define MARIO_FIRE_STATE_FIRE_RIGHT		100
#define MARIO_FIRE_STATE_FIRE_LEFT		200
#define MARIO_FIRE_STATE_HIT			300

#define MARIO_FIRE_ANI_FIRE_RIGHT		0
#define MARIO_FIRE_ANI_FIRE_LEFT		1


class MARIO_FIRE : public GameObject
{
public:
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	//void RenderBoundingBox();
	void SetState(int state);

};

