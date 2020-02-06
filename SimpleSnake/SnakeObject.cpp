#include "SnakeObject.h"
#include <SDL.h>
#include "InputManager.h"
#include <iostream>
#include "Helper.h"
#include <cmath>


SnakeObject::SnakeObject(GameWindow* window) : GameObject(window)
{
	direction.x = 1;
	direction.y = 0;
	targetPosition.x = 1;
	targetPosition.y = 0;
	size.x = window->screenWidth / 16;
	size.y = window->screenHeight / 16;
	nextSnake = NULL;
	speed = 10;
}

SnakeObject::~SnakeObject()
{
	if (nextSnake)
		delete nextSnake;
}

void SnakeObject::Update(float deltaTime)
{

}

void SnakeObject::FixedUpdate(float deltaTime)
{

	position.y += (targetPosition.y - position.y) * deltaTime * speed;

	position.x += (targetPosition.x - position.x) * deltaTime * speed;

	position.y = CLAMP(position.y, 0.0f, (float)gameWindow->screenHeight - size.y);
	position.x = CLAMP(position.x, 0.0f, (float)gameWindow->screenWidth - size.x);
	
	if (controlled)
	{
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
	if(nextSnake)
		nextSnake->FixedUpdate(deltaTime);
	if (CheckPosition())
	{
		MoveTo(targetPosition.x + direction.x, targetPosition.y + direction.y);
	}
}

void SnakeObject::Render(SDL_Renderer * renderer)
{
	SDL_Rect rect = { position.x * size.x, position.y *size.y, size.x, size.y };
	SDL_SetRenderDrawColor(renderer, 0xAA, 0x00, 0xFF, 0xFF);
	SDL_RenderFillRect(renderer, &rect);

	if (controlled)
	{
		SDL_Rect rectTwo = { (position.x * size.x + size.x/2 - size.x/8) + direction.x * size.x/2, (position.y* size.y + size.y / 2 - size.y/8) + direction.y * size.y/2, size.x/4, size.y/4 };
		SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
		SDL_RenderFillRect(renderer, &rectTwo);

	}
	if(nextSnake)
		nextSnake->Render(renderer);
}


void SnakeObject::AddSnake()
{
	if (nextSnake == NULL)
	{
		nextSnake = new SnakeObject(gameWindow);
		nextSnake->position = position;
		nextSnake->position.x = position.x - direction.x;
		nextSnake->position.y = position.y - direction.y;

		nextSnake->targetPosition.x = targetPosition.x;
		nextSnake->targetPosition.y = targetPosition.y;
	}
	else
	{
		nextSnake->AddSnake();
	}	
}

void SnakeObject::MoveTo(int gridX, int gridY)
{
	Transform oldTarget = targetPosition;
	targetPosition.x = CLAMP(gridX, 0, gameWindow->screenWidth / (int)size.x - 1);
	targetPosition.y = CLAMP(gridY, 0, gameWindow->screenHeight / (int)size.y - 1);

	if (nextSnake)
	{
		if (oldTarget.x != targetPosition.x || oldTarget.y != targetPosition.y)
		{
			nextSnake->direction.x = oldTarget.x - nextSnake->targetPosition.x;
			nextSnake->direction.y = oldTarget.y - nextSnake->targetPosition.y;
		}
		else
		{
			nextSnake->direction.x = 0;
			nextSnake->direction.y = 0;
		}
	}
}

bool SnakeObject::CheckPosition()
{
	if (position.x >= targetPosition.x - 0.1f && position.x <= targetPosition.x + 0.1f)
	{
		if (position.y >= targetPosition.y - 0.1f && position.y <= targetPosition.y + 0.1f)
		{
			return true;
		}
	}
	return false;
}
