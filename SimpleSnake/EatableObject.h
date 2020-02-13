#pragma once
#include "GameObject.h"
class EatableObject :
	public GameObject
{
public:
	EatableObject(GameWindow* window);
	~EatableObject();


	void Update(float deltaTime) override;
	void FixedUpdate(float deltaTime) override;
	void Render(class SDL_Renderer* renderer) override;
};

