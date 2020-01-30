#include "SnakeObject.h"
#include <SDL.h>
#include "InputManager.h"
#include <iostream>
#include "Helper.h"


SnakeObject::SnakeObject(GameWindow* window) : GameObject(window)
{
	direction.x = 1;
	direction.y = 0;
	nextSnake = NULL;
}

SnakeObject::~SnakeObject()
{
}

void SnakeObject::Update(float deltaTime)
{

}

void SnakeObject::FixedUpdate(float deltaTime)
{
	position.y += direction.y * deltaTime * 100;
	position.x += direction.x * deltaTime * 100;

	position.y = CLAMP(position.y, 0.0f, (float)gameWindow->screenHeight);
	position.x = CLAMP(position.x, 0.0f, (float)gameWindow->screenWidth);
	
	if (inputManager->GetKeyDown(SDLK_d))
	{
		direction.x = 1;
		direction.y = 0;
	}
	else if (inputManager->GetKeyDown(SDLK_a))
	{
		direction.x = -1;
		direction.y = 0;
	}
	else if (inputManager->GetKeyDown(SDLK_w))
	{
		direction.x = 0;
		direction.y = -1;
	}
	else if (inputManager->GetKeyDown(SDLK_s))
	{
		direction.x = 0;
		direction.y = 1;
	}
}

void SnakeObject::Render(SDL_Renderer * renderer)
{
	SDL_Rect rect = { position.x, position.y, 30, 30 };
	SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
	SDL_RenderFillRect(renderer, &rect);
}

void SnakeObject::MoveTo(int gridX, int gridY)
{
}
