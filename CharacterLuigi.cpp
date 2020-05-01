#include "CharacterLuigi.h"
#include "Texture2D.h"

CharacterLuigi::CharacterLuigi(SDL_Renderer* renderer, string imagePath, Vector2D startPosition, LevelMap* map) : Character(renderer, imagePath, startPosition, map)
{
	mCurrentLevelmap = map;

	mPosition = startPosition;
}

CharacterLuigi::~CharacterLuigi()
{
	delete mRenderer;
	mRenderer = NULL;
}

void CharacterLuigi::Render()
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

void CharacterLuigi::Update(float deltaTime, SDL_Event e)
{
	Character::Update(deltaTime, e);

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

	//collided with ground can jump agin
	if (mPosition.y == 0.0f)
	{
		mCanJump = true;
	}

	switch (e.type)
	{
	case SDL_KEYUP:
		switch (e.key.keysym.sym)
		{
		case SDLK_a:
			mMovingLeft = false;
			break;
		case SDLK_d:
			mMovingRight = false;
			break;
		default:
			break;
		}

	case !SDL_KEYDOWN:
		switch (e.key.keysym.sym)
		{
		case SDLK_w:
			Character::Jump();
			break;

		case SDLK_DOWN:
			break;
		case SDLK_LEFT:
			mMovingRight = true;
			break;
		case SDLK_RIGHT:
			mMovingLeft = true;
			break;
		default:
			break;
		}

	}

	if (mMovingLeft)
	{
		MoveLeft(deltaTime);
	}
	else if (mMovingRight)
	{
		MoveLeft(deltaTime);
	}

}

void CharacterLuigi::SetPosition(Vector2D newPosition)
{
	mPosition = newPosition;
}

Vector2D CharacterLuigi::GetPosition()
{
	return mPosition;
}

void CharacterLuigi::MoveLeft(float deltaTime)
{
	deltaTime - 1;
	mMovingLeft = true;
}

void CharacterLuigi::MoveRight(float deltaTime)
{
	deltaTime + 1;
	mMovingRight = true;
}

bool CharacterLuigi::IsJumping()
{
	return mJumping;
}

void CharacterLuigi::CancelJump()
{
	mJumping = false;
	mCanJump = true;
}

void CharacterLuigi::SetState(string state)
{
	LuigiState = state;
}

string CharacterLuigi::GetState()
{
	return LuigiState;
}