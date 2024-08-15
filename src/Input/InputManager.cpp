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

void InputManager::RebindKey(const std::string &actionName, SDL_Keycode newKey)
{
	// look up the old key
	auto oldKeyIter = m_ActionNameKeyMap.find(actionName);

	if (oldKeyIter != m_ActionNameKeyMap.end())
	{
		// look up the callback
		auto oldKey = oldKeyIter->second;
		auto callbackIter = m_keyActionMap.find(oldKey);

		auto callback = callbackIter->second;

		m_keyActionMap[newKey] = callback;
		m_keyActionMap.erase(oldKey);
	}

	m_ActionNameKeyMap[actionName] = newKey;
}
