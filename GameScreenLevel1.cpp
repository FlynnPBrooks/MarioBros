#include "GameScreenLevel1.h"

GameScreenLevel1::GameScreenLevel1(SDL_Renderer* renderer) : GameScreen(renderer)
{
	SetUpLevel();
	mScreenshake = false;
	mLevelMap = NULL;

}

GameScreenLevel1::~GameScreenLevel1()
{
	delete mBackgroundTexture;
	mBackgroundTexture = NULL;

	delete marioCharacter;
	marioCharacter = NULL;

	delete luigiCharacter;
	luigiCharacter = NULL;

	delete mPowBlock;
	mPowBlock = NULL;

	mEnemies.clear();
}

void GameScreenLevel1::Update(float deltaTime, SDL_Event e)
{
	if (mScreenshake)
	{
		mScreenshakeTime -= deltaTime;
		mWobble++;
		mBackgroundPos = sin(mWobble);
		mBackgroundPos *= 3.0f;
		if (mScreenshakeTime <= 0.0f)
		{
			mScreenshake = false;
			mBackgroundPos = 0.0f;
		}
	}

	if (Collisions::Instance()->Circle(marioCharacter->GetcollisionCircle(), luigiCharacter->GetcollisionCircle()))
	{
		deltaTime = 0;
	}

	if (Collisions::Instance()->Box(marioCharacter->GetCollisionBox(), luigiCharacter->GetCollisionBox()))
	{
		deltaTime = 0;
	}

	//Update the player
	marioCharacter->Update(deltaTime, e);
	luigiCharacter->Update(deltaTime, e);

	UpdatePOWBlock();
	UpdateEnemies(deltaTime, e);

	//if coin = 1000 level 2

}

void GameScreenLevel1::Render()
{
	if (!mEnemies.empty())
	{
		for (unsigned int i = 0; i < mEnemies.size(); i++)
		{
			mEnemies[i]->Render();
		}
	}
	//Draw the background
	mBackgroundTexture->Render(Vector2D(0, mBackgroundPos), SDL_FLIP_NONE);

	//Render player
	marioCharacter->Render();
	luigiCharacter->Render();

	mPowBlock->Render();	
}

bool GameScreenLevel1::SetUpLevel()
{
	SetLevelMap();

	//Load the background texture
	mBackgroundTexture = new Texture2D(mRenderer);
	if (!mBackgroundTexture->LoadFromFile("Images/BackgroundMB.png"))
	{
		cout << "Failed to load background texture!";
		return false;
	}


	//Set up the Player charrater
	marioCharacter = new CharacterMario (mRenderer, "Images/Mario.png", Vector2D(80, 330), mLevelMap);
	luigiCharacter = new CharacterLuigi (mRenderer, "Images/Luigi.png", Vector2D(340, 330), mLevelMap);

	//Set up Pow block
	mPowBlock = new PowBlock(mRenderer, mLevelMap);	

	mScreenshake = false;
	mBackgroundPos = 0.0f;

	CreateKoopa(Vector2D(150, 32), FACING_RIGHT, KOOPA_SPEED);
	CreateKoopa(Vector2D(325, 32), FACING_LEFT, KOOPA_SPEED);

	return true;
}

void GameScreenLevel1::SetLevelMap()
{
	int map[MAP_HEIGHT][MAP_WIDTH] = { { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
									   { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
									   { 1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1 },
									   { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
									   { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
									   { 0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0 },
									   { 1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1 },
									   { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
									   { 0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0 },
									   { 1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1 },
									   { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
									   { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
									   { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 } };

	//clears the old map
	if (mLevelMap != NULL)
	{
		delete mLevelMap;
	}
	// make a new one
	mLevelMap = new LevelMap(map);

}

void GameScreenLevel1::UpdatePOWBlock()
{
	if (Collisions::Instance()->Box(marioCharacter->GetCollisionBox(), mPowBlock->GetCollisionBox()))
	{
		if (mPowBlock->IsAvailable())
		{
			if (marioCharacter->IsJumping())
			{
				DoScreenshake();
				mPowBlock->TakeAHit();
				marioCharacter->CancelJump();
			}
		}
	}
}

void GameScreenLevel1::DoScreenshake()
{
	mScreenshake = true;
	mScreenshakeTime = SCREENSHAKE_DURATION;
	mWobble = 0.0f;

}

void GameScreenLevel1::UpdateEnemies(float deltaTime, SDL_Event e)
{
	if (!mEnemies.empty())
	{
	//	CreateKoopa(Vector2D(150, 90), FACING_RIGHT, KOOPA_SPEED);
	//	CreateKoopa(Vector2D(325, 90), FACING_LEFT, KOOPA_SPEED);

		int enemyIndexToDelete = -1;
		for (unsigned int i = 0; i < mEnemies.size(); i++)
		{
			if (mEnemies[i]->GetPosition().y > 300.0f)
			{
				if (mEnemies[i]->GetPosition().x < (float)(-mEnemies[i]->GetCollisionBox().width * 0.5f) || mEnemies[i]->GetPosition().x > SCREEN_WIDTH - (float)(mEnemies[i]->GetCollisionBox().width * 0.55f))
				{
					mEnemies[i]->SetAlive(false);
				}

			}

			mEnemies[i]->Update(deltaTime, e);

			while (mScreenshake == true)
			{
				mEnemies[i]->TakeDamage();
			}

			if ((mEnemies[i]->GetPosition().y > 300.0f || mEnemies[i]->GetPosition().y > 64.0f) && (mEnemies[i]->GetPosition().x > 64.0f || mEnemies[i]->GetPosition().x > SCREEN_WIDTH - 96.0f))
			{

			}
			else
			{
				if (mEnemies[i]->mInjured == true)
				{
					if (Collisions::Instance()->Circle(mEnemies[i]->GetcollisionCircle(), marioCharacter->GetcollisionCircle()))
					{
						mEnemies[i]->SetAlive(false);
						mPoints + 100;
					}

				}
				else if (mEnemies[i]->mInjured == false)
				{
					if (Collisions::Instance()->Circle(mEnemies[i]->GetcollisionCircle(), marioCharacter->GetcollisionCircle()))
					{
						marioCharacter->SetState(dead);
					}
				}
			}




			if (!mEnemies[i]->GetAlive())
			{
				enemyIndexToDelete = i;
			}
		}

		if (enemyIndexToDelete != -1)
		{
			mEnemies.erase(mEnemies.begin() + enemyIndexToDelete);
		}
	}
}

void GameScreenLevel1::CreateKoopa(Vector2D position, FACING direction, float speed)
{
	koopaCharacter = new CharacterKoopa(mRenderer, "Images/Koopa.png", mLevelMap, position, direction, speed);
	koopaCharacter = new CharacterKoopa(mRenderer, "Images/Koopa.png", mLevelMap, position, direction, speed);

	mEnemies.push_back(koopaCharacter);
}

/*
void GameScreenLevel1::GameOver(float deltaTime, SDL_Event e)
{
	string a = marioCharacter->GetState;


	if (a == dead)
	{
		cout << "Game Over" << endl;
	}
}
*/