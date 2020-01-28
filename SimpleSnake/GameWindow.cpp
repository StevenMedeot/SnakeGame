#include "GameWindow.h"
#include <SDL.h>
#include <stdio.h>
#include <iostream>
#include "InputManager.h"

void GameWindow::GetInputs()
{
	SDL_Event e;

	// Check the events for all inputs then update them in the input manager
	while (SDL_PollEvent(&e) != 0)
	{
		if (e.type == SDL_QUIT)
		{
			b_isRunning = false;
		}
		if (e.type == SDL_KEYDOWN)
		{
			inputManager->PressKey(e.key.keysym.sym);
		}
		if (e.type == SDL_KEYUP)
		{
			inputManager->ReleaseKey(e.key.keysym.sym);
		}
	}

}

void GameWindow::CalculateTime()
{
	float tick = SDL_GetTicks() * 0.001f;
	deltaTime = (SDL_GetTicks()* 0.001f) - elapsedTime;
	fixedTime += deltaTime;

	elapsedTime = tick;
}

GameWindow::GameWindow(string name, int width, int height) : title(name), screenWidth(width), screenHeight(height), deltaTime(0), elapsedTime(0), fixedTime(0)
{
}


GameWindow::~GameWindow()
{
	ShutdownWindow();
}

bool GameWindow::InitWindow()
{
	bool success = true;

	//The window we'll be rendering to
	window = NULL;

	//The surface contained by the window
	SDL_Surface* screenSurface = NULL;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		//Create window
		window = SDL_CreateWindow("Snake Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenWidth, screenHeight, SDL_WINDOW_SHOWN);
		if (window == NULL)
		{
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			//Get window surface
			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
			if (renderer == NULL)
			{
				printf("Renderer could not be created! SDL error: $s \n", SDL_GetError());
				success = false;
			}
			else
			{
				SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);

				inputManager = new InputManager();
				if (!inputManager)
				{

					printf("Input Manager could not be created! \n", SDL_GetError());
					return false;
				}
				b_isRunning = true;
			}


		}
	}

	return success;
}

float positionX = 0;
float positionY = 0;
void GameWindow::UpdateWindow()
{
	// Game Loop 
	while (b_isRunning)
	{
		GetInputs();
		CalculateTime();

		// Fixed update happens once every 1/30th of a second
		while (fixedTime >= FIXEDTIME)
		{
			if (inputManager->GetKeyDown(SDLK_ESCAPE))
			{
				b_isRunning = false;
			}
			if (inputManager->GetKeyDown(SDLK_d))
			{
				positionX += 10 * FIXEDTIME;
			}

			if (inputManager->GetKeyDown(SDLK_a))
			{
				positionX -= 10 * FIXEDTIME;
			}

			if (inputManager->GetKeyDown(SDLK_w))
			{
				positionY -= 10 * FIXEDTIME;
			}

			if (inputManager->GetKeyDown(SDLK_s))
			{
				positionY += 10 * FIXEDTIME;
			}
			fixedTime -= FIXEDTIME;
		}

		


		SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
		SDL_RenderClear(renderer);

		SDL_Rect rect = {positionX, positionY, screenWidth / 4, screenHeight / 4 };
		SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
		SDL_RenderFillRect(renderer, &rect);

		//Update the surface
		SDL_RenderPresent(renderer);

		inputManager->EndFrame();

	}
}

void GameWindow::ShutdownWindow()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	renderer = NULL;
	window = NULL;
	//Quit SDL subsystems
	SDL_Quit();
}