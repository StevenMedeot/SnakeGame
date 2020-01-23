#include "InputManager.h"
#include <algorithm>

using namespace std;

InputManager::InputManager()
{
}


InputManager::~InputManager()
{
}

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

void InputManager::EndFrame()
{
	for (map<int, KeyState>::iterator it = keyMap.begin(); it != keyMap.end(); it++)
	{
		UpdateInformation(it->second);
	}

}

bool InputManager::KeyPress(int key)
{
	return keyMap[key].press;
}

bool InputManager::KeyDown(int key)
{
	return keyMap[key].down;
}

bool InputManager::KeyUp(int key)
{
	return keyMap[key].release;
}

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
