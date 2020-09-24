#pragma once
#include "GameObject.h"
#define MARIO_RACCOON_FIGHT_WIDTH 23
#define MARIO_RACCOON_FIGHT_HEIGHT 14
class MARIO_RACCOON : public GameObject
{
public:
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
};

