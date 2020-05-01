#pragma once

#ifndef _GAMESCREENMANAGER_H
#define _GAMESCREENMANAGER_H

#include <SDL.h>
#include "Commons.h"
#include "GameScreen.h"
#include <string>
using namespace std;

class GameScreen;


class GameScreenManager
{
public:
	GameScreenManager(SDL_Renderer* renderer, SCREENS startScreen);
	~GameScreenManager();

	void Render();
	void Update(float deltaTime, SDL_Event e);

	void ChangeScreen(SCREENS newScreen);
	GameScreen* mCurrentScreen;
private:
	SDL_Renderer* mRenderer;
};





#endif //_GAMESCREENMANAGER_H