#include "InputManager.h"
#include <algorithm>

using namespace std;

InputManager::InputManager()
{
}


InputManager::~InputManager()
{
}

// Updates the keystates information in the map
void InputManager::UpdateInformation(KeyState &state)
{
	state.press = false;
	state.release = false;

	if (state.pressed)
	{
		state.press = true;
		state.down = true;
		state.pressed = false;
	}

	if (state.released)
	{
		state.release = true;
		state.down = false;
		state.released = false;
	}
}

// At the end of each frame update the keys information
void InputManager::EndFrame()
{
	for (map<int, KeyState>::iterator it = keyMap.begin(); it != keyMap.end(); it++)
	{
		UpdateInformation(it->second);
	}

}

// Accessors for each keys current state
bool InputManager::GetKeyPress(int key)
{
	return keyMap[key].press;
}

bool InputManager::GetKeyDown(int key)
{
	return keyMap[key].down;
}

bool InputManager::GetKeyUp(int key)
{
	return keyMap[key].release;
}

// Mutators for each key if it's currently pressed or released in the frame
void InputManager::PressKey(int key)
{
	if (!keyMap[key].down)
		keyMap[key].pressed = true;
}

void InputManager::ReleaseKey(int key)
{
	if (keyMap[key].down)
		keyMap[key].released = true;
}
