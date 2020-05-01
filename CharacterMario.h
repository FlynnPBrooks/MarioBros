#pragma once

#ifndef _CHARACTERMARIO_H
#define _CHARACTERMARIO_H

#include "Character.h"

class CharacterMario : public Character
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
	float mCollisionRadius;
	
	CharacterMario(SDL_Renderer* renderer, string imagePath, Vector2D startPosition, LevelMap* map);
	~CharacterMario();

	virtual void Render();
	virtual void Update(float deltaTime, SDL_Event e);

	void SetPosition(Vector2D newPosition);
	Vector2D GetPosition();

	bool IsJumping();
	void CancelJump();

	void SetState(string state);
	string GetState();

	string MarioState;

	float MovementSpeed = 0.05;
private:
	FACING mFacingDirection;
	bool mMovingLeft;
	bool mMovingRight;
};

#endif //_CHARACTERMARIO_H

