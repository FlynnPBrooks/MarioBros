#include "Character.h"
#include "Texture2D.h"



Character::Character(SDL_Renderer* renderer, string imagePath, Vector2D starPosition, LevelMap* map)
{
	mRenderer = renderer;
	mTexture = new Texture2D(renderer);
	mTexture->LoadFromFile(imagePath);

	mPosition = starPosition;
	mFacingDirection = FACING_RIGHT;
	mMovingLeft = false;
	mMovingRight = false;

	mCurrentLevelmap = map;
}

Character::~Character()
{
	delete mRenderer;
	mRenderer = NULL;
}

void Character::Render()
{
	mTexture->Render(mPosition, SDL_FLIP_NONE);
}

void Character::Jump()
{
	if (!mJumping)
	{
		mJumpForce = INITIAL_JUMP_FORCE;
		mJumping = true;
		mCanJump = false;
	}
}

void Character::SetPosition(Vector2D newPosition)
{
	mPosition = newPosition;
}

Vector2D Character::GetPosition()
{
	return mPosition;
}


void Character::MoveLeft(float deltaTime)
{
	deltaTime - 1;
	mMovingLeft = true;
}

void Character::MoveRight(float deltaTime)
{
	deltaTime + 1;
	mMovingRight = true;
}

float Character::GetCollisionRadius()
{
	mCollisionRadius = 15.0f;

	return mCollisionRadius;
}

void Character::AddGravity(float deltaTime)
{
	mPosition.y += GRAVITY * deltaTime;
	mCanJump = false;
}

void Character::Update(float deltaTime, SDL_Event e)
{
	int centralXPosition = (int)(mPosition.x + (mTexture->GetWidth() * 0.5f)) / TILE_WIDTH;
	int footPosition = (int)(mPosition.y + (mTexture->GetHeight())) / TILE_HEIGHT;

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

	//Gravity dealing
	if (mCurrentLevelmap->GetTileAt(footPosition, centralXPosition) == 1)
	{

	}
	else
	{
		mCanJump = true;
		AddGravity(deltaTime);
	}

}