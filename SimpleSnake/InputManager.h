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

	bool GetKeyPress(int key);
	bool GetKeyDown(int key);
	bool GetKeyUp(int key);

	void EndFrame();

private:
	void UpdateInformation(KeyState& state);
	void PressKey(int key);
	void ReleaseKey(int key);
	
};

#endif