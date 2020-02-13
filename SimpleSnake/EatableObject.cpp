#include "EatableObject.h"

#include <SDL.h>
#include "InputManager.h"


EatableObject::EatableObject(GameWindow* window) : GameObject(window)
{
	size.x = window->screenWidth / 16;
	size.y = window->screenHeight / 16;
}


EatableObject::~EatableObject()
{
}

void EatableObject::Update(float deltaTime)
{
}

void EatableObject::FixedUpdate(float deltaTime)
{
}

void EatableObject::Render(SDL_Renderer * renderer)
{

	SDL_Rect rect = { position.x * size.x + size.x/4, position.y *size.y + size.x/4, size.x/2, size.y/2};
	SDL_SetRenderDrawColor(renderer, 0xAA, 0xFF, 0x00, 0xFF);
	SDL_RenderFillRect(renderer, &rect);
}
