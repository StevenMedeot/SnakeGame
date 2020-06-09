#ifndef SNAKEOBJECT_H
#define SNAKEOBJECT_H

#include "GameObject.h"
class SnakeObject :	public GameObject
{
private:
	Transform targetPosition;
	class EatableObject* eat;
protected:
	Transform direction;
	SnakeObject* nextSnake;
	Transform targetDir;

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

	void SpawnEatable();

private:
	bool CheckPosition(Transform target, float distance);
	bool CheckOverlap(Transform target, float distance);
};

#endif