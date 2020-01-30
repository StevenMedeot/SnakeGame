#include "GameObject.h"

GameObject::GameObject(GameWindow * window)
{
	gameWindow = window;
	inputManager = window->inputManager;

	position.x = 0;
	position.y = 0;
}


GameObject::~GameObject()
{
}
