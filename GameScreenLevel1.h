#pragma once

#ifndef _GAMESCREENL1_H
#define _GAMESCREENL1_H

#include <SDL.h>
#include "Commons.h"
#include "GameScreen.h"
#include <string>
#include "Character.h"
#include "CharacterMario.h"
#include "CharacterLuigi.h"
#include "CharacterKoopa.h"
#include "Collisions.h"
#include "LevelMap.h"
#include <iostream>
#include "Texture2D.h"
#include "PowBlock.h"
#include <vector>

using namespace std;

class Texture2D;
class PowBlock;

class GameScreenLevel1 : GameScreen
{
public:
		GameScreenLevel1(SDL_Renderer* renderer);
		~GameScreenLevel1();

		void Render();
		void Update(float deltaTime, SDL_Event e);

private:
	Texture2D* mBackgroundTexture;
	bool SetUpLevel();
	CharacterMario* marioCharacter;
	CharacterLuigi* luigiCharacter;
	CharacterKoopa* koopaCharacter;
	void SetLevelMap();
	LevelMap* mLevelMap;
	void UpdatePOWBlock();
	PowBlock* mPowBlock;

	bool mScreenshake;
	float mScreenshakeTime;
	float mWobble;
	float mBackgroundPos;

	float mPoints = 0;

	void DoScreenshake();

	void UpdateEnemies(float deltaTime, SDL_Event e);
	void CreateKoopa(Vector2D position, FACING direction, float speed);

	vector<CharacterKoopa*> mEnemies;

	float mNextKoopa = 2.0f;

	void GameOver(float deltaTime, SDL_Event e);

	string dead;
};




#endif //_GAMESCREENL1_H