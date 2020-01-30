#ifndef SNAKEOBJECT_H
#define SNAKEOBJECT_H

#include "GameObject.h"
class SnakeObject :	public GameObject
{
protected:
	Transform direction;
protected:
	SnakeObject* nextSnake;
public:
	SnakeObject(GameWindow* window);
	~SnakeObject();

	void Update(float deltaTime) override;
	void FixedUpdate(float deltaTime) override;
	void Render(class SDL_Renderer* renderer) override;

protected:
	void MoveTo(int gridX, int gridY);
};

#endif