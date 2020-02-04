#ifndef SNAKEOBJECT_H
#define SNAKEOBJECT_H

#include "GameObject.h"
class SnakeObject :	public GameObject
{
private:
	Transform targetPosition;
protected:
	Transform direction;
	Transform size;
	SnakeObject* nextSnake;

	float speed;
public:
	SnakeObject(GameWindow* window);
	~SnakeObject();

	void Update(float deltaTime) override;
	void FixedUpdate(float deltaTime) override;
	void Render(class SDL_Renderer* renderer) override;

	void AddSnake();
	void MoveTo(int gridX, int gridY);
	bool controlled = false;

private:
	bool CheckPosition();
};

#endif