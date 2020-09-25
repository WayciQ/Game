#include "MARIO_RACCOON.h"
#include "Textures.h"
#include "Game.h"
#include "Goomba.h"
#include "debug.h"
void MARIO_RACCOON::Render() {
	//RenderBoundingBox(x,y);
}
void MARIO_RACCOON::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	if (state == MARIO_RACCOON_STATE_OUT) {
		r = x;
		b = y;
	}
	else
	if (state == MARIO_RACCOON_STATE_FIGHT_LEFT) {
		l = x - 8;
		t = y + 17;
		r = x + 25;
		b = y + 29;
	}
	else {
		t = y + 17;
		r = x + 33;
		b = y + 29;
	}

}
void MARIO_RACCOON::RenderBoundingBox()
{
	D3DXVECTOR3 p(x,y,0);
	RECT rect;

	LPDIRECT3DTEXTURE9 bbox = Textures::GetInstance()->Get(ID_TEX_BBOX);

	float l, t, r, b;

	GetBoundingBox(l, t, r, b);
	rect.left = 0;
	rect.top = 0;
	rect.right = (int)r - (int)l;
	rect.bottom = (int)b - (int)t;
	Game::GetInstance()->Draw(l, t, bbox, rect.left, rect.top, rect.right, rect.bottom, 0);
}
void MARIO_RACCOON::SetState(int state) {
	GameObject::SetState(state);

	switch (state)
	{

	}

}
void MARIO_RACCOON::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
	GameObject::Update(dt);
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	coEvents.clear();
	
	CalcPotentialCollisions(coObjects, coEvents);
		
	
	if (coEvents.size() == 0)
	{
		
	}
	else
	{
		
		float min_tx, min_ty, nx = 0, ny;
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			if (dynamic_cast<Goomba*>(e->obj)) // if e->obj is Goomba 
			{
				Goomba* goomba = dynamic_cast<Goomba*>(e->obj);

				if (e->nx != 0 && nx != 0 ) {
					if (goomba->GetState() != GOOMBA_STATE_DIE)
					{
						goomba->SetState(GOOMBA_STATE_DIE);
						//DebugOut(L"cham nef: %d \n", e->nx);
					}
				}
			}
		}
	}
	
}
