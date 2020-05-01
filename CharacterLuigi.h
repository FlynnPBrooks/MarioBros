#pragma once

#ifndef _CHARACTERLUIGI_H
#define _CHARACTERLUIGI_H

#include "Character.h"

class CharacterLuigi : public Character
{
public:
	SDL_Renderer* mRenderer;
	Vector2D mPosition;
	Texture2D* mTexture;
	virtual void MoveLeft(float deltaTime);
	virtual void MoveRight(float deltaTime);
	bool mJumping;
	bool mCanJump;
	float mJumpForce;

	CharacterLuigi(SDL_Renderer* renderer, string imagePath, Vector2D startPosition, LevelMap* map);
	~CharacterLuigi();

	virtual void Render();
	virtual void Update(float deltaTime, SDL_Event e);

	void SetPosition(Vector2D newPosition);
	Vector2D GetPosition();

	bool IsJumping();
	void CancelJump();

	void SetState(string state);
	string GetState();

	string LuigiState;

private:
	FACING mFacingDirection;
	bool mMovingLeft;
	bool mMovingRight;
};

#endif //_CHARACTERLUIGI_H