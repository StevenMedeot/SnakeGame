#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <map>

struct KeyState
{
	bool pressed = false;
	bool released = false;


	bool press = false;
	bool release = false;
	bool down = false;

};

class InputManager
{
	friend class GameWindow;
private:
	std::map<int, KeyState> keyMap;
public:
	InputManager();
	~InputManager();

	bool KeyPress(int key);
	bool KeyDown(int key);
	bool KeyUp(int key);

	void EndFrame();


private:
	void UpdateInformation(KeyState& state);
	
};

#endif