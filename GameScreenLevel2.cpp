#include "GameScreenLevel2.h"

GameScreenLevel2::GameScreenLevel2(SDL_Renderer* renderer) : GameScreen(renderer)
{
	mLevelMap = NULL;

	SetUpLeve2();
}

GameScreenLevel2::~GameScreenLevel2()
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

void GameScreenLevel2::Update(float deltaTime, SDL_Event e)
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

	//Update the player
	marioCharacter->Update(deltaTime, e);
	luigiCharacter->Update(deltaTime, e);

	if (Collisions::Instance()->Circle(marioCharacter->GetcollisionCircle(), luigiCharacter->GetcollisionCircle()))
	{
		deltaTime = 0;
	}

	if (Collisions::Instance()->Box(marioCharacter->GetCollisionBox(), luigiCharacter->GetCollisionBox()))
	{
		deltaTime = 0;
	}

	while (mNextKoopa > 0.0f)
	{
		mNextKoopa--;
	}
	if (mNextKoopa == 0.0f)
	{
		CreateKoopa(Vector2D(150, 32), FACING_RIGHT, KOOPA_SPEED);
		mEnemies.size() + 1;
		CreateKoopa(Vector2D(325, 32), FACING_LEFT, KOOPA_SPEED);
		mEnemies.size() + 1;
		mNextKoopa = 20.0f;
	}

	UpdatePOWBlock();
	UpdateEnemies(deltaTime, e);
}

void GameScreenLevel2::Render()
{
	//Draw the background
	mBackgroundTexture->Render(Vector2D(0, mBackgroundPos), SDL_FLIP_NONE);

	//Render player
	marioCharacter->Render();
	luigiCharacter->Render();

	mPowBlock->Render();

	for (unsigned int i = 0; i < mEnemies.size(); i++)
	{
		mEnemies[i]->Render();
	}
}

bool GameScreenLevel2::SetUpLeve2()
{
	//Load the background texture
	mBackgroundTexture = new Texture2D(mRenderer);
	if (!mBackgroundTexture->LoadFromFile("Images/Background.png"))
	{
		cout << "Failed to load background texture!";
		return false;
	}
	else
	{
		return true;
	}

	SetLevelMap();

	//Set up the Player charrater
	marioCharacter = new CharacterMario(mRenderer, "Images/Mario.png", Vector2D(64, 2330), mLevelMap);
	luigiCharacter = new CharacterLuigi(mRenderer, "Images/Luigi.png", Vector2D(64, 2330), mLevelMap);

	//Set up Pow block
	mPowBlock = new PowBlock(mRenderer, mLevelMap);

	mScreenshake = false;
	mBackgroundPos = 0.0f;

	CreateKoopa(Vector2D(150, 32), FACING_RIGHT, KOOPA_SPEED);
	CreateKoopa(Vector2D(325, 32), FACING_LEFT, KOOPA_SPEED);
}

void GameScreenLevel2::SetLevelMap()
{
	int map[MAP_HEIGHT][MAP_WIDTH] = { {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
									   {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
									   {1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1},
									   {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
									   {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
									   {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
									   {0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0},
									   {1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
									   {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
									   {0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0},
									   {1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1},
									   {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
									   {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1} };

	//clears the old map
	if (mLevelMap != NULL)
	{
		delete mLevelMap;
	}
	// make a new one
	mLevelMap = new LevelMap(map);
}

void GameScreenLevel2::UpdatePOWBlock()
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

void GameScreenLevel2::DoScreenshake()
{
	mScreenshake = true;
	mScreenshakeTime = SCREENSHAKE_DURATION;
	mWobble = 0.0f;

}

void GameScreenLevel2::UpdateEnemies(float deltaTime, SDL_Event e)
{
	if (!mEnemies.empty())
	{
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
						mPoints + 10;
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

void GameScreenLevel2::CreateKoopa(Vector2D position, FACING direction, float speed)
{
	mEnemies.push_back(koopaCharacter);
}

/*
void GameScreenLevel2::GameOver(float deltaTime, SDL_Event e)
{
	string a = marioCharacter->GetState;


	if (a == dead)
	{
		cout << "Game Over" << endl;
	}
}
*/