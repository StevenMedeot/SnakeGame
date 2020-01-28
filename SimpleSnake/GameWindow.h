#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <string>

using namespace std;

class SDL_Window;
class SDL_Renderer;
class InputManager;

const float FIXEDTIME = 0.0333f;

class GameWindow
{
protected:
	SDL_Window* window;
	SDL_Renderer* renderer;
	InputManager* inputManager;
	bool b_isRunning;

	float elapsedTime;
	float deltaTime;
	float fixedTime;

protected:
	void GetInputs();
	void CalculateTime();
public:
	string title;
	int screenWidth;
	int screenHeight;
public:
	GameWindow(string name, int width, int height);
	~GameWindow();

	bool InitWindow();
	void UpdateWindow();
	void ShutdownWindow();


};

#endif