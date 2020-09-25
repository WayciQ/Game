#include "MARIO_FIRE.h"
#include "Textures.h"
#include "Game.h"
#include "Goomba.h"
#include "debug.h"

void MARIO_FIRE::Render() {
	int ani;
	if (state == MARIO_FIRE_STATE_FIRE_RIGHT)
		ani = MARIO_FIRE_ANI_FIRE_RIGHT;
	else ani = MARIO_FIRE_ANI_FIRE_LEFT;
	//DebugOut(L"render");
	animations[ani]->Render(x,y);
	//RenderBoundingBox();
}

void MARIO_FIRE::GetBoundingBox(float& left, float& top, float& right, float& bottom) {
	left = x;
	top = y;
	right = x + 17;
	bottom = y + 17;
	if (state == MARIO_FIRE_STATE_HIT)
	{
		left = 0;
		top = 0;
		right = x + 0;
		bottom = y + 0;
	}
}

void MARIO_FIRE::SetState(int state) {
	GameObject::SetState(state);
	switch (state)
	{
	case MARIO_FIRE_STATE_FIRE_RIGHT:
		vx = FIRE_SPEED;
		//vy = FIRE_SPEED;
		break;
	case MARIO_FIRE_STATE_FIRE_LEFT:
		vx = -FIRE_SPEED;
		//vy = FIRE_SPEED;
		break;
	case MARIO_FIRE_STATE_HIT:
		vx = 0;
		vy = 0;
		break;
	}
}

void MARIO_FIRE::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
	GameObject::Update(dt);
	//vy += FIRE_GRAVITY * dt;
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	coEvents.clear();
	x += dx;
	y += dy;
	if (vx < 0 && x < 0) {
		state = MARIO_FIRE_STATE_HIT;
	}
	
	if (vx > 0 && x > 290) {
		state = MARIO_FIRE_STATE_HIT;
	}
	
	if(state != MARIO_FIRE_STATE_HIT)
		CalcPotentialCollisions(coObjects, coEvents);
	
	if (coEvents.size() == 0)
	{
		/*x += dx;
		y += dy;*/
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);
		
		/*x += min_tx * dx + nx * 0.05f;	
		y -= min_ty * dy + ny * 0.05f;
		
		vy = -vy;
		if (nx != 0) vx = -vx;
		if (ny != 0) vy = -vy;*/

		//for (UINT i = 0; i < coEventsResult.size(); i++)
		//{
		//	LPCOLLISIONEVENT e = coEventsResult[i];
		//	if (dynamic_cast<Goomba*>(e->obj)) // if e->obj is Goomba 
		//	{
		//		Goomba* goomba = dynamic_cast<Goomba*>(e->obj);

		//		if (e->nx != 0 && nx != 0) {
		//			if (goomba->GetState() != GOOMBA_STATE_DIE)
		//			{
		//				goomba->SetState(GOOMBA_STATE_DIE);
		//				DebugOut(L"cham nef: %d \n", e->nx);
		//			}
		//		}
		//	}

		//}
	}
}
