#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "GameWindow.h"

struct Transform
{
	float x;
	float y;
};
class GameObject
{
protected:
	GameWindow* gameWindow;
	InputManager* inputManager;
public:
	Transform position;
	Transform size;
public:
	GameObject(GameWindow* window);
	~GameObject();

	virtual void Update(float deltaTime) = 0;
	virtual void FixedUpdate(float deltaTime) = 0;
	virtual void Render(class SDL_Renderer* renderer) = 0;
};

#endif