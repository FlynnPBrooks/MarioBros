#include "CharacterMario.h"
#include "Texture2D.h"


CharacterMario::CharacterMario(SDL_Renderer* renderer, string imagePath, Vector2D startPosition, LevelMap* map) : Character(renderer, imagePath, startPosition, map)
{
	mCurrentLevelmap = map;

	mPosition = startPosition;

	mMovingLeft = false;
	mMovingRight = false;
}

CharacterMario::~CharacterMario()
{
	delete mRenderer;
	mRenderer = NULL;
}

void CharacterMario::Render()
{
	if (Character::mFacingDirection == FACING_RIGHT)
	{
		Character::mTexture->Render(Character::mPosition, SDL_FLIP_NONE);
	}
	else
	{
		Character::mTexture->Render(Character::mPosition, SDL_FLIP_HORIZONTAL);
	}
}

void CharacterMario::Update(float deltaTime, SDL_Event e)
{
	Character::Update(deltaTime, e);

	//collided with ground can jump agin
	if (mPosition.y == 0.0f)
	{
		mCanJump = true;
	}

	if (mMovingLeft == true)
	{
		MoveLeft(deltaTime);
	}
	if (mMovingRight == true)
	{
		MoveRight(deltaTime);
	}

	switch (e.type)
	{
	case SDL_KEYUP:
		switch (e.key.keysym.sym)
		{
		case SDLK_LEFT:
			mMovingLeft = false;
			break;
		case SDLK_RIGHT:
			mMovingRight = false;
			break;
		}
	case SDL_KEYDOWN:
		switch (e.key.keysym.sym)
		{
		case SDLK_LEFT:
			mMovingLeft = true;
			break;
		case SDLK_RIGHT:
			mMovingRight = true;
			break;
		case SDLK_UP:
			if (mCanJump)
			{
				Character::Jump();
			}
			break;
		}

	}


	//Jumping
	if (mJumping)
	{
		// Adjust the postiton
		mPosition.y -= mJumpForce * deltaTime;

		//reduce the jump force
		mJumpForce -= JUMP_FORCE_DECREMENT * deltaTime;

		//has the jump force been redurced to 0
		if (mJumpForce <= 0.0f)
		{
			mJumping = false;
		}
	}


}

void CharacterMario::SetPosition(Vector2D newPosition)
{
	mPosition = newPosition;
}

Vector2D CharacterMario::GetPosition()
{
	return mPosition;
}

void CharacterMario::MoveLeft(float deltaTime)
{
	mFacingDirection = FACING_LEFT;
	mPosition.x -= MovementSpeed * deltaTime;
}

void CharacterMario::MoveRight(float deltaTime)
{
	mFacingDirection = FACING_RIGHT;

	mPosition.x += MovementSpeed * deltaTime;
}


bool CharacterMario::IsJumping()
{
	CancelJump();
	mJumping = true;
	return mJumping;
}

void CharacterMario::CancelJump()
{
	mJumping = false;
	mCanJump = true;
}

void CharacterMario::SetState(string state)
{
	MarioState = state;
}

string CharacterMario::GetState()
{
	return MarioState;
}