#pragma once
#include "GameObject.h"

#define MARIO_WALKING_SPEED		0.1f
#define MARIO_JUMP_SPEED_Y		0.3f
#define MARIO_GRAVITY			0.001f

#define MARIO_STATE_IDLE			0
#define MARIO_STATE_WALKING_RIGHT	100
#define MARIO_STATE_WALKING_LEFT	200
#define MARIO_STATE_JUMP			300
#define MARIO_STATE_JUMP_RIGHT		400
#define MARIO_STATE_JUMP_LEFT		500

#define MARIO_ANI_IDLE_RIGHT		0
#define MARIO_ANI_IDLE_LEFT			1
#define MARIO_ANI_WALKING_RIGHT		2
#define MARIO_ANI_WALKING_LEFT		3
#define MARIO_ANI_JUMP_RIGHT		4
#define MARIO_ANI_JUMP_LEFT			5
class Mario : public GameObject
{
public:
	void Update(DWORD dt);
	void Render();
	void SetState(int state);
};

