#pragma once

#ifndef _CHARACTER_H
#define _CHARACTER_H

#include <SDL.h>
#include <iostream>
#include "Commons.h"
#include "Constants.h"
#include "Texture2D.h"
#include "LevelMap.h"

using namespace std;

class Texture2D;

class Character
{
protected:
	SDL_Renderer* mRenderer;
	Vector2D mPosition;
	Texture2D* mTexture;
	virtual void MoveLeft(float deltaTime);
	virtual void MoveRight(float deltaTime);
	bool mJumping;
	bool mCanJump;
	float mJumpForce;
	float mCollisionRadius;
	FACING mFacingDirection;
	bool mMovingLeft;
	bool mMovingRight;
	LevelMap* mCurrentLevelmap;

public:
	Character(SDL_Renderer* renderer, string imagePath, Vector2D starPosition, LevelMap* map);
	~Character();

	virtual void Render();

	void AddGravity(float deltaTime);
	void Jump();

	void SetPosition(Vector2D newPosition);
	Vector2D GetPosition();

	float GetCollisionRadius();
	Rect2D GetCollisionBox() { return Rect2D(mPosition.x, mPosition.y, mTexture->GetWidth(), mTexture->GetHeight()); }
	void Update(float deltaTime, SDL_Event e);
	Circle2D GetcollisionCircle() { return Circle2D(mPosition.x, mPosition.y, mCollisionRadius, mCollisionRadius); }

private:
};


#endif //_CHARACTER_H