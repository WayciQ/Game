#include <algorithm>
#include "debug.h"

#include "Mario.h"
#include "Game.h"

#include "Goomba.h"
#include "MARIO_RACCOON.h"

void Mario::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{

	// Calculate dx, dy 
	GameObject::Update(dt);
	
	// Simple fall down
	vy += MARIO_GRAVITY * dt;

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	coEvents.clear();
	//raccoon->Update(dt, coObjects);
	// turn off collision when die 
	if (state != MARIO_STATE_DIE)
		CalcPotentialCollisions(coObjects, coEvents);
	//DebugOut(L"mario: %d \n", coObjects->size());
	// reset untouchable timer if untouchable time has passed
	if (GetTickCount() - untouchable_start > MARIO_UNTOUCHABLE_TIME)
	{
		untouchable_start = 0;
		untouchable = 0;
	}
	
	// No collision occured, proceed normally
	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

		// block 
		x += min_tx * dx + nx * 0.3f;		// nx*0.4f : need to push out a bit to avoid overlapping next frame
		y += min_ty * dy + ny * 0.3f;

		isJumping = false;
		if (nx != 0) vx = 0;
		if (ny != 0) vy = 0;

		// Collision logic with Goombas
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];

			if (dynamic_cast<Goomba*>(e->obj)) // if e->obj is Goomba 
			{
				Goomba* goomba = dynamic_cast<Goomba*>(e->obj);

				// jump on top >> kill Goomba and deflect a bit 
				if (e->ny < 0)
				{
					if (goomba->GetState() != GOOMBA_STATE_DIE)
					{
						goomba->SetState(GOOMBA_STATE_DIE);
						vy = -MARIO_JUMP_DEFLECT_SPEED;
					}
				}
				else if (e->nx != 0)
				{
					if (untouchable == 0)
					{
						if (goomba->GetState() != GOOMBA_STATE_DIE)
						{
							/*if (level > MARIO_LEVEL_SMALL)
							{
								level = MARIO_LEVEL_SMALL;
								StartUntouchable();
							}
							else*/
								/*SetState(MARIO_STATE_DIE);*/
							/*if (state == MARIO_STATE_FIGHT && this->nx > 0) {
								if (nx > 1)
									if (goomba->GetState() != GOOMBA_STATE_DIE)
									{
										
									}
								goomba->SetState(GOOMBA_STATE_DIE);
							}
							else if (state == MARIO_STATE_FIGHT && this->nx < 0) {
								if (nx < 1)
									if (goomba->GetState() != GOOMBA_STATE_DIE)
									{
										
									}
								goomba->SetState(GOOMBA_STATE_DIE);
							}*/
							/*goomba->vx = 0;
							DWORD temp = GetTickCount();
							if (GetTickCount() - temp > 3000)
							{
								goomba->vx = 0.05f;
								temp = 0;

							}*/
							
						}
						
					}
				}
			}
		}
	}

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void Mario::Render()
{
	int ani;
	if (state == MARIO_STATE_DIE)
		ani = MARIO_ANI_DIE;
	else
		/*if (level == MARIO_LEVEL_BIG)
		{
			if (vx == 0)
			{
				if (nx > 0) {

					if (ny_ == 0)
						ani = MARIO_ANI_BIG_IDLE_RIGHT;
					else if (ny_ == -1)
						ani = MARIO_ANI_SIT_RIGHT;
					else 
						ani = MARIO_ANI_BIG_JUMP_RIGHT;
					
				}
				
				else {
					if (ny_ == 0)
						ani = MARIO_ANI_BIG_IDLE_LEFT;
					else if (ny_ == -1)
						ani = MARIO_ANI_SIT_LEFT;
					else
						ani = MARIO_ANI_BIG_JUMP_LEFT;
				}
			}
			else if (vx > 0) {
				if (ny_ == 0)
					ani = MARIO_ANI_BIG_WALKING_RIGHT;
				else if (ny_ == -1)
					ani = MARIO_ANI_SIT_RIGHT;
				else
					ani = MARIO_ANI_BIG_JUMP_RIGHT;
			}
				
			else {
				if (ny_ == 0)
					ani = MARIO_ANI_BIG_WALKING_LEFT;
				else if (ny_ == -1)
					ani = MARIO_ANI_SIT_LEFT;
				else
					ani = MARIO_ANI_BIG_JUMP_LEFT;
				DebugOut(L"[a]  vx <0", ani);
			} 
		}
		else if (level == MARIO_LEVEL_SMALL)
		{
			if (vx == 0)
			{
				if (nx > 0) {
					if (ny_ == 0)
						ani = MARIO_ANI_SMALL_IDLE_RIGHT;
					else ani = MARIO_ANI_SMALL_JUMP_RIGHT;
				}
				else {
					if (ny_ == 0)
						ani = MARIO_ANI_SMALL_IDLE_LEFT;
					else ani = MARIO_ANI_SMALL_JUMP_LEFT;
				}
			}
			else if (vx > 0) {
				if(ny_ == 0)
					ani = MARIO_ANI_SMALL_WALKING_RIGHT;
				else ani = MARIO_ANI_SMALL_JUMP_RIGHT;
			}
				
			else {
				if (ny_ == 0)
					ani = MARIO_ANI_SMALL_WALKING_LEFT;
				else ani = MARIO_ANI_SMALL_JUMP_LEFT;
			} 
		}
		else*/
		if (level == MARIO_LEVEL_RACCOON) {

			if (vx == 0)
			{
				if (nx > 0) {

					if (isSiting)
						ani = MARIO_ANI_SIT_RIGHT;
					else if (isJumping)
						ani = MARIO_ANI_JUMP_RIGHT;
					else if (isFighting)
						ani = MARIO_ANI_FIGHT_RIGHT;
					else
						ani = MARIO_ANI_IDLE_RIGHT;
						
					//DebugOut(L"[a]  nx== 0", ani);

				}

				else {
					if (isSiting)
						ani = MARIO_ANI_SIT_LEFT;
					else if (isJumping)
						ani = MARIO_ANI_JUMP_LEFT;
					else if (isFighting)
						ani = MARIO_ANI_FIGHT_LEFT;
					else
						ani = MARIO_ANI_IDLE_LEFT;
						
					//DebugOut(L"[a]  vx==0", ani);
				}
			}
			else if (vx > 0) {
				if (isJumping)
					ani = MARIO_ANI_JUMP_RIGHT;
				else if (isSiting)
					ani = MARIO_ANI_SIT_RIGHT;
				else if (isFighting)
					ani = MARIO_ANI_FIGHT_RIGHT;
				else
					ani = MARIO_ANI_WALKING_RIGHT;
					
				//DebugOut(L"[a]  vx >0", ani);
			}

			else {
				if (isJumping)
					ani = MARIO_ANI_JUMP_LEFT;
				else if (isSiting)
					ani = MARIO_ANI_SIT_LEFT;
				else if (isFighting)
					ani = MARIO_ANI_FIGHT_LEFT;
				else
					ani = MARIO_ANI_WALKING_LEFT;
					
				//DebugOut(L"[a]  vx <0", ani);
			}
		}
		
	int alpha = 255;
	if (untouchable) alpha = 128;
	//DebugOut(L"[a] ANi: %d\n", ani);
	if (ani == MARIO_ANI_FIGHT_LEFT) {
		animations[ani]->Render(x - 8, y, alpha);
	}
	else {
		animations[ani]->Render(x, y, alpha);
		RenderBoundingBox();
	}
	if (isFighting) {
		raccoon->RenderBoundingBox();
	}
	
}

void Mario::SetState(int state)
{
	GameObject::SetState(state);

	switch (state)
	{
	case MARIO_STATE_WALKING_RIGHT:
		vx = MARIO_WALKING_SPEED;
		isSiting = false;
		isJumping = false;
		nx = 1;
		break;
	case MARIO_STATE_WALKING_LEFT:
		vx = -MARIO_WALKING_SPEED;
		isSiting = false;
		isJumping = false;
		nx = -1;
		break;

	case MARIO_STATE_JUMP_LEFT:
		//vy = -MARIO_JUMP_SPEED_Y;
		nx = -1;
		isSiting = false;
		isJumping = true;
		vx = -MARIO_WALKING_SPEED;
		break;
	case MARIO_STATE_JUMP_RIGHT:
		//vy = -MARIO_JUMP_SPEED_Y;
		nx = 1;
		isSiting = false;
		isJumping = true;
		vx = MARIO_WALKING_SPEED;
		break;
	case MARIO_STATE_JUMP:
		vy = -MARIO_JUMP_SPEED_Y;
		isSiting = false;
		isJumping = true;
	case MARIO_STATE_IDLE:
		vx = 0;
		isSiting = false;
		isJumping = false;
		isFighting = false;
		break;
	case MARIO_STATE_DIE:
		vy = -MARIO_DIE_DEFLECT_SPEED;
		break;
	case MARIO_STATE_SIT:
		isSiting = true;
		isJumping = false;
		//nx = -1;
		y += 11;
		vx = 0;
		break;
	case MARIO_STATE_SIT_PRESS:
		isSiting = true;
		isJumping = false;
		vx = 0;
		break;
	case MARIO_STATE_STAND:
		y -= 11;
		break;
	case MARIO_STATE_FIGHT:
		isFighting = true;
		raccoon->SetPosition(this->x, this->y + 15);
		if (nx > 0)
			raccoon->SetState(MARIO_RACCOON_STATE_FIGHT_RIGHT);
		else raccoon->SetState(MARIO_RACCOON_STATE_FIGHT_LEFT);
		break;
	case MARIO_STATE_NOT_FIGHT:
		isFighting = false;
		break;
	}
}

void Mario::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;

	if (level == MARIO_LEVEL_RACCOON)
	{
			if (isSiting) {
				right = x + MARIO_BIG_SIT_BBOX_WIDTH;
				bottom = y + MARIO_BIG_SIT_BBOX_HEIGHT;
			}
			else if (nx > 0)
			{
				left = x + MARIO_RACCOON_FIGHT_WIDTH_X;
				right = x + MARIO_RACCOON_FIGHT_WIDTH;
				bottom = y + MARIO_RACCOON_FIGHT_HEIGHT;
			}
			else 
			{
				right = x + 15;
				bottom = y + MARIO_RACCOON_FIGHT_HEIGHT;
			}
			
	}
	
}
void Mario::RenderBoundingBox()
{
	D3DXVECTOR3 p(this->x, this->y, 0);
	RECT rect;

	LPDIRECT3DTEXTURE9 bbox = Textures::GetInstance()->Get(ID_TEX_BBOX);

	float l, t, r, b;

	GetBoundingBox(l, t, r, b);
	rect.left = 0;
	rect.top = 0;
	rect.right = (int)r - (int)l;
	rect.bottom = (int)b - (int)t;

	Game::GetInstance()->Draw(l, t, bbox, rect.left, rect.top, rect.right, rect.bottom, 255);
}
