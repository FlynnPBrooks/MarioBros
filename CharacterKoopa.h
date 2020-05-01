#pragma once

#ifndef _CHARACTERKOOPA_H
#define _CHARACTERKOOPA_H

#include "Character.h"

class CharacterKoopa : public Character
{
public:
	CharacterKoopa(SDL_Renderer* renderer, string imagePath, LevelMap* map, Vector2D startPosition, FACING startFacing, float movementSpeed);
	~CharacterKoopa();

	virtual void Render();
	virtual void Update(float deltaTime, SDL_Event e);

	void TakeDamage();
	void Jump();

	FACING mFacingDirection;
	bool mMovingLeft;
	bool mMovingRight;

	float mMovementSpeed;

	bool mInjured;

	void SetAlive(bool deadoralive);
	bool GetAlive();

	bool State;

private:
	float mSingleSpriteWidth;
	float mSingleSpriteHeight;

	float mInjuredTime;

	void FlipRightwayUp();
};

#endif //_CHARACTERKOOPA_H