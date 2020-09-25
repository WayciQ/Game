#pragma once
#include "GameObject.h"
#include "Textures.h"
#include "MARIO_RACCOON.h"
#include "MARIO_FIRE.h"

#define MARIO_WALKING_SPEED		0.1f 
//0.1f
#define MARIO_JUMP_SPEED_Y		0.3f
#define MARIO_JUMP_DEFLECT_SPEED 0.2f
#define MARIO_GRAVITY			0.001f
#define MARIO_DIE_DEFLECT_SPEED	 0.5f

#define MARIO_STATE_IDLE			0
#define MARIO_STATE_WALKING_RIGHT	100
#define MARIO_STATE_WALKING_LEFT	200
#define MARIO_STATE_JUMP			300
#define MARIO_STATE_FALL			301
#define MARIO_STATE_DIE				400
#define MARIO_STATE_JUMP_RIGHT		500
#define MARIO_STATE_JUMP_LEFT		600
#define MARIO_STATE_SIT_PRESS		700
#define MARIO_STATE_STAND			702
#define MARIO_STATE_SIT				900
#define MARIO_STATE_STAND			1000
#define MARIO_STATE_FIGHT			1100
#define MARIO_STATE_NOT_FIGHT		1300
#define MARIO_STATE_FIRE			1400
#define MARIO_STATE_FIRE_LEFT		1500
#define MARIO_STATE_NOT_FIRE		1600
#pragma region Normal
//#define MARIO_ANI_BIG_IDLE_RIGHT		0
//#define MARIO_ANI_BIG_IDLE_LEFT			1
//#define MARIO_ANI_SMALL_IDLE_RIGHT		2
//#define MARIO_ANI_SMALL_IDLE_LEFT		3
//
//#define MARIO_ANI_BIG_WALKING_RIGHT		4
//#define MARIO_ANI_BIG_WALKING_LEFT		5
//#define MARIO_ANI_SMALL_WALKING_RIGHT	6
//#define MARIO_ANI_SMALL_WALKING_LEFT	7
//
//#define MARIO_ANI_SIT_RIGHT				8
//#define MARIO_ANI_SIT_LEFT				9
//
//#define MARIO_ANI_BIG_JUMP_RIGHT		10
//#define MARIO_ANI_BIG_JUMP_LEFT			11
//#define MARIO_ANI_SMALL_JUMP_RIGHT		12
//#define MARIO_ANI_SMALL_JUMP_LEFT		13
#pragma endregion

#define MARIO_ANI_IDLE_RIGHT		0
#define MARIO_ANI_IDLE_LEFT			1
#define MARIO_ANI_WALKING_RIGHT		2
#define MARIO_ANI_WALKING_LEFT		3
#define MARIO_ANI_JUMP_RIGHT		4	
#define MARIO_ANI_FALL_RIGHT		5
#define MARIO_ANI_JUMP_LEFT			6
#define MARIO_ANI_FALL_LEFT			7
#define MARIO_ANI_SIT_RIGHT			8
#define MARIO_ANI_SIT_LEFT			9
#define MARIO_ANI_FIGHT_RIGHT		10
#define MARIO_ANI_FIGHT_LEFT		11
#define MARIO_ANI_DIE				12



#define	MARIO_LEVEL_SMALL	1
#define	MARIO_LEVEL_BIG		2
#define MARIO_LEVEL_RACCOON	3

#define MARIO_BIG_BBOX_WIDTH  22
#define MARIO_BIG_BBOX_HEIGHT 30

#define MARIO_SMALL_BBOX_WIDTH  13
#define MARIO_SMALL_BBOX_HEIGHT 15

#define MARIO_BIG_SIT_BBOX_WIDTH 23
#define MARIO_BIG_SIT_BBOX_HEIGHT 19

#define MARIO_RACCOON_FIGHT_WIDTH 22
#define MARIO_RACCOON_FIGHT_HEIGHT 30
#define MARIO_RACCOON_FIGHT_WIDTH_X 8

#define MARIO_UNTOUCHABLE_TIME 5000


class Mario : public GameObject
{
	int level;
	int untouchable;
	DWORD untouchable_start;
	bool isSiting;
	bool isJumping;
	bool isFighting;
	MARIO_RACCOON* raccoon ;
	MARIO_FIRE* fire;
	vector<MARIO_FIRE*>fires;
	bool shooting;
	void AddFire();
public:
	Mario() : GameObject()	
	{
		level = MARIO_LEVEL_RACCOON;
		untouchable = 0;
		isSiting = false;
		isJumping = false;
		isFighting = false;
		shooting = false;
		raccoon = new MARIO_RACCOON();
		
		//DebugOut(L"dcm no vo:%d", fire->animations.size());
	}
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL);
	virtual void Render();
	void SetState(int state);
	void SetLevel(int l) { level = l; }
	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount(); }
	bool IsSitting() { return this->isSiting; }
	bool IsJumping() { return this->isJumping; }
	bool IsFighting() { return this->isFighting; }
	bool Shooting() { return this->shooting; }
	virtual void RenderBoundingBox();
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};