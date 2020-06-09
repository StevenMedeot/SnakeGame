#include "SnakeObject.h"
#include <SDL.h>
#include "InputManager.h"
#include <iostream>
#include "Helper.h"
#include <cmath>
#include <time.h>
#include "EatableObject.h"

SnakeObject::SnakeObject(GameWindow* window) : GameObject(window)
{
	direction.x = 1;
	direction.y = 0;
	targetPosition.x = 1;
	targetPosition.y = 0;
	size.x = window->screenWidth / 16;
	size.y = window->screenHeight / 16;
	nextSnake = NULL;
	speed = 6;
}

SnakeObject::~SnakeObject()
{
	if (nextSnake)
		delete nextSnake;
}

void SnakeObject::Update(float deltaTime)
{
	if (controlled)
	{
		if (inputManager->GetKeyPress(SDLK_o))
		{
			SpawnEatable();
		}
		if (inputManager->GetKeyPress(SDLK_f))
		{
			AddSnake();
		}
	}
}

void SnakeObject::FixedUpdate(float deltaTime)
{
	if (targetPosition.x != position.x)
	{
		float targeDirX = (targetPosition.x - position.x) / abs(targetPosition.x - position.x);
		position.x += targeDirX * deltaTime * speed;
	}
	if (targetPosition.y != position.y)
	{
		float targeDirY = (targetPosition.y - position.y) / abs(targetPosition.y - position.y);
		position.y += targeDirY * deltaTime * speed;
	}
	

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
	if (nextSnake)
		nextSnake->FixedUpdate(deltaTime);
	if (CheckPosition(targetPosition, 0.01f))
	{
		if (controlled && eat)
		{
			if (CheckPosition(eat->position, 0.4f))
			{
				AddSnake();
				SpawnEatable();
			}
		}
		MoveTo(targetPosition.x + direction.x, targetPosition.y + direction.y);
	}
}

void SnakeObject::Render(SDL_Renderer * renderer)
{
	if (eat)
		eat->Render(renderer);


	SDL_Rect rect = { position.x * size.x, position.y *size.y, size.x, size.y };
	SDL_SetRenderDrawColor(renderer, 0xAA, 0x00, 0xFF, 0xFF);
	SDL_RenderFillRect(renderer, &rect);

	if (controlled)
	{
		float targeDirX = direction.x;
		float targeDirY = direction.y;
		if (targetPosition.x != position.x)
			targeDirX = (targetPosition.x - position.x) / abs(targetPosition.x - position.x);
		if (targetPosition.y != position.y)
			targeDirY = (targetPosition.y - position.y) / abs(targetPosition.y - position.y);


		SDL_Rect rectTwo = { (position.x * size.x + size.x / 2 - size.x / 8) + targeDirX * size.x / 2, (position.y* size.y + size.y / 2 - size.y / 8) + targeDirY * size.y / 2, size.x / 4, size.y / 4 };
		SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
		SDL_RenderFillRect(renderer, &rectTwo);

	}
	if (nextSnake)
		nextSnake->Render(renderer);


}


void SnakeObject::AddSnake()
{
	if (nextSnake == NULL)
	{
		nextSnake = new SnakeObject(gameWindow);
		nextSnake->position.x = position.x - direction.x;
		nextSnake->position.y = position.y - direction.y;

		nextSnake->targetPosition.x = targetPosition.x - direction.x;
		nextSnake->targetPosition.y = targetPosition.y - direction.y;
		nextSnake->direction = direction;
	}
	else
	{
		nextSnake->AddSnake();
	}
}

void SnakeObject::MoveTo(int gridX, int gridY)
{
	position = targetPosition;
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

void SnakeObject::SpawnEatable()
{
	if (!eat)
		eat = new EatableObject(gameWindow);

	srand(time(NULL));
	eat->position.x = rand() % 16;
	eat->position.y = rand() % 16;

	while (CheckOverlap(eat->position, 1.0f))
	{
		eat->position.x = rand() % 16;
		eat->position.y = rand() % 16;
	}
	
}

bool SnakeObject::CheckPosition(Transform target, float distance)
{
	if (position.x >= target.x - distance && position.x <= target.x + distance)
	{
		if (position.y >= target.y - distance && position.y <= target.y + distance)
		{
			return true;
		}
	}
	return false;
}

bool SnakeObject::CheckOverlap(Transform target, float distance)
{
	
	if (position.x >= target.x - distance && position.x <= target.x + distance)
	{
		if (position.y >= target.y - distance && position.y <= target.y + distance)
		{
			cout << "True : " << position.x << " _ " << position.y << " : " << target.x << " _ " << target.y << endl;
			return true;
		}
	}
	else if (nextSnake)
	{
		return nextSnake->CheckOverlap(target, distance);
	}

	return false;
}
