#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <string>
using namespace std;

class SDL_Window;
class SDL_Renderer;
class InputManager;

class GameWindow
{
protected:
	SDL_Window* window;
	SDL_Renderer* renderer;
	InputManager* inputManager;
	bool b_isRunning;

protected:
	void GetInputs();
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