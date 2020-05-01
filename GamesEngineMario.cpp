
#include "Constants.h"
#include "GameScreen.h"
#include "Commons.h"
#include "GameScreenManager.h"
#include "Texture2D.h"

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#undef main

using namespace::std;

//Globals
SDL_Window* gMWindow = NULL;
SDL_Renderer* gMRenderer = NULL;
GameScreenManager* gameScreenManager;
Uint32 g0oldTime;
Mix_Music* gMusic = NULL;

//Function
bool MainInitSDL();
void MainCloseSDL();
bool MainUpdate();
void MainRender();
void LoadMusic(string music);
SDL_Texture* MainLoadTextureFromFile(string path);

int main()
{
	bool quit = false;

	if (MainInitSDL())
	{
		//Set up the game screen manager starts with level 1
		gameScreenManager = new GameScreenManager(gMRenderer, SCREEN_LEVEL1);

		g0oldTime = SDL_GetTicks();
		while (!quit)
		{
			MainRender();
			quit = MainUpdate();
		}
	}
	if (quit)
	{
		MainCloseSDL();
	}

	LoadMusic("Music/Mario.mp3");
	if (Mix_PlayingMusic() == 0)
	{
		Mix_PlayMusic(gMusic, -1);
	}


	return 0;
}

bool MainInitSDL()
{
	//Setup SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		cout << "SDL did not initialise. Error: " << SDL_GetError();
		return false;
	}
	else
	{
		//All good attemps to make window
		gMWindow = SDL_CreateWindow("Games Engine Creation",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			SCREEN_WIDTH,
			SCREEN_HEIGHT,
			SDL_WINDOW_SHOWN);
		//Did the window get created
		gMRenderer = SDL_CreateRenderer(gMWindow, -1, SDL_RENDERER_ACCELERATED);

		if (gMRenderer != NULL)
		{
			//Initialise PNG loading
			int imageFlags = IMG_INIT_PNG;
			if (!(IMG_Init(imageFlags) && imageFlags))
			{
				cout << "SDL_Image could not initialise. Error: " << IMG_GetError();
				return false;
			}
		}
		else
		{
			cout << "Renderer could not initalise. Error: " << SDL_GetError();
			return false;
		}

		if (gMWindow == NULL)
		{
			//No
			cout << "Window was not created. Error: " << SDL_GetError();
			return false;
		}
	}
	return true;

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		cout << "Mixer could not initialise. Error: " << Mix_GetError();
		return false;
	}

}

void MainCloseSDL()
{
	//Release the renderer
	SDL_DestroyRenderer(gMRenderer);
	gMRenderer = NULL;

	//Quit SDL Subsystems
	IMG_Quit();
	SDL_Quit();

	//Destroy the game screen manager
	delete gameScreenManager;
	gameScreenManager = NULL;

	Mix_FreeMusic(gMusic);
	gMusic = NULL;

}

bool MainUpdate()
{
	//get the new time
	Uint32 newTime = SDL_GetTicks();

	//Event Handler
	SDL_Event e;

	SDL_PollEvent(&e);
	//Handle any events

	switch (e.type)
	{
		//Click the x to quit
	case SDL_QUIT:
		return true;
		break;
	}

	gameScreenManager->Update((float)(newTime - g0oldTime) / 1000.0f, e);
	g0oldTime = newTime;
	return false;
}


void MainRender()
{
	SDL_SetRenderDrawColor(gMRenderer, 0x00, 0x00, 0x00, 0x00);
	SDL_RenderClear(gMRenderer);

	//Set where to render the texture
	gameScreenManager->Render();

	//Update the screen
	SDL_RenderPresent(gMRenderer);
}

SDL_Texture* MainLoadTextureFromFile(string path)
{
	SDL_Texture* pTexture = NULL;

	//Lord the image
	SDL_Surface* pSurface = IMG_Load(path.c_str());
	if (pSurface != NULL)
	{
		//Create the texture form the pixels opn the surface
		pTexture = SDL_CreateTextureFromSurface(gMRenderer, pSurface);
		if (pTexture == NULL)
		{
			cout << "Unable to create texture from surface. Error: " << SDL_GetError() << endl;
		}
		//Remove the loaded surface now that we have the texture
		SDL_FreeSurface(pSurface);
	}
	else
	{
		cout << "Unable to crate texture from surface Error: " << IMG_GetError() << endl;
	}
	return pTexture;
}

void LoadMusic(string path)
{
	gMusic = Mix_LoadMUS(path.c_str());

	if (gMusic == NULL)
	{
		cout << "Failed to load background music! Error: " << Mix_GetError() << endl;
	}
}
