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
	// The window that we will be rendering too
	SDL_Window* window;
	// The renderer that the window will use
	SDL_Renderer* renderer;

	// boolean to make sure the game is running
	bool b_isRunning;

	// Time since game started
	float elapsedTime;
	// Time between frames
	float deltaTime;
	float fixedTime;

protected:
	// Loads inputs from the event system and off loads them to the input manager
	void GetInputs();
	// Calculate time from milliseconds to seconds
	void CalculateTime();
public:
	// Game title
	string title;
	// Game Screen width and height
	int screenWidth;
	int screenHeight;

	// The input manager owned by the game window
	InputManager* inputManager;
public:
	GameWindow(string name, int width, int height);
	~GameWindow();

	bool InitWindow();
	void UpdateWindow();
	void RenderWindow();
	void ShutdownWindow();


};

#endif