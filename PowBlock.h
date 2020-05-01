#pragma once

#ifndef _POWBLOCK_H
#define _POWBLOCK_H

#include <SDL.h>
#include <iostream>
#include "Commons.h"
#include "Constants.h"
#include "LevelMap.h"
#include "Texture2D.h"

class PowBlock
{
public:
	PowBlock(SDL_Renderer* Render, LevelMap* map);
	~PowBlock();

	void Render();
	Rect2D GetCollisionBox();
	void TakeAHit();
	bool IsAvailable() { return mNumber0fHitsLeft > 0; }


private:
	SDL_Renderer* mRenderer;
	Vector2D mPosition;
	Texture2D* mTexture;
	LevelMap* mLevelMap;
	
	float mSingleSpriteWidth;
	float mSingleSpriteHeight;

	int mNumber0fHitsLeft;

};

#endif //_POWBLOCK_H