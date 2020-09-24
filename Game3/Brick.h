#pragma once
#include "GameObject.h"

#define BRICK_BBOX_WIDTH  16
#define BRICK_BBOX_HEIGHT 16
#define BRICK_ANI_POWER 0
class Brick : public GameObject
{
public:
	virtual void Render();
	//virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
};