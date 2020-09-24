#pragma once
#include "GameObject.h"
#define MARIO_RACCOON_FIGHT_WIDTH 23
#define MARIO_RACCOON_FIGHT_HEIGHT 14

#define MARIO_RACCOON_STATE_FIGHT_RIGHT 100
#define MARIO_RACCOON_STATE_FIGHT_LEFT 200
#define MARIO_RACCOON_STATE_OUT			300
class MARIO_RACCOON : public GameObject
{
public:
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	void RenderBoundingBox();
	void SetState(int state);
};

