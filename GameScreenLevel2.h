#pragma once

#ifndef _GAMESCREENL2_H
#define _GAMESCREENL2_H

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

class GameScreenLevel2 : GameScreen
{
public:
	GameScreenLevel2(SDL_Renderer* renderer);
	~GameScreenLevel2();

	void Render();
	void Update(float deltaTime, SDL_Event e);

private:
	Texture2D* mBackgroundTexture;
	bool SetUpLeve2();
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

	float mNextKoopa = 20.0f;

	void GameOver(float deltaTime, SDL_Event e);

	string dead;
};




#endif //_GAMESCREENL2_H