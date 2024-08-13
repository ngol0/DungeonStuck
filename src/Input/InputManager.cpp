#include "InputManager.h"

InputManager &InputManager::GetInstance()
{
	static InputManager manager;
	return manager;
}

InputManager::~InputManager()
{
	// go through the map
	for (auto &pair : m_keyActionMap)
	{
		// delete the pointer
		delete pair.second;
	}
	m_keyActionMap.clear();
}

void InputManager::Execute(SDL_Keycode key)
{
	auto iter = m_keyActionMap.find(key);
	if (iter != m_keyActionMap.end())
	{
		iter->second->Call();
	}
}
