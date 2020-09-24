#include "Mario.h"
#include "debug.h"

void Mario::Update(DWORD dt) {
	GameObject::Update(dt);
	/*DebugOut(L"Y firt: %f\n", GameObject::GetY());*/
	// simple fall down
	vy += MARIO_GRAVITY*dt;
	if (y > 100)
	{
		vy = 0; y = 100.0f;
		ny = 0;
	}
	
	// simple screen edge collision!!!
	if (vx > 0 && x > 290) x = 290;
	if (vx < 0 && x < 0) x = 0;
}

void Mario::Render()
{
	int ani;
	if (vx == 0)
	{
		if (nx > 0) {
			if (ny == 1) ani = MARIO_ANI_JUMP_RIGHT;
			else 
				ani = MARIO_ANI_IDLE_RIGHT;
		}
		else {
			if (ny == 1) ani = MARIO_ANI_JUMP_LEFT;
			else 
				ani = MARIO_ANI_IDLE_LEFT;
		
		}
	}
	else if (vx > 0)
	{
		if (ny == 1) ani = MARIO_ANI_JUMP_RIGHT;
		else ani = MARIO_ANI_WALKING_RIGHT;
	}
	else if (vx < 0) {
		if (ny == 1) ani = MARIO_ANI_JUMP_LEFT;
		else ani = MARIO_ANI_WALKING_LEFT; 
	}
	

	animations[ani]->Render(x, y);
}

void Mario::SetState(int state)
{
	GameObject::SetState(state);
	switch (state)
	{
	case MARIO_STATE_WALKING_RIGHT:
		vx = MARIO_WALKING_SPEED;
		nx = 1;
		ny = 1;
		break;
	case MARIO_STATE_WALKING_LEFT:
		vx = -MARIO_WALKING_SPEED;
		nx = -1;
		ny = 1;
		break;
	case MARIO_STATE_JUMP:
		vy = -MARIO_JUMP_SPEED_Y;
		ny = 1;
		break;
	case MARIO_STATE_JUMP_RIGHT:
		vy = -MARIO_JUMP_SPEED_Y;
		vx = MARIO_WALKING_SPEED;
		ny = 1;
		break;
	case MARIO_STATE_JUMP_LEFT:
		vy = -MARIO_JUMP_SPEED_Y;
		vx = -MARIO_WALKING_SPEED;
		ny = 1;
		break;
	case MARIO_STATE_IDLE:
		vx = 0;
		ny = 0;
		break;
	}
	
}