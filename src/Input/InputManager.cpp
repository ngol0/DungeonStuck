#include "InputManager.h"

InputManager& InputManager::GetInstance()
{
	static InputManager manager;
	return manager;
}

InputManager::~InputManager()
{
	//go through the map
	for (auto& pair : m_keyActionMap)
	{
		//delete the pointer
		delete pair.second;
	}
	m_keyActionMap.clear();
}