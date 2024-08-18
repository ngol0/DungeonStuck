#include "InputManager.h"

InputManager &InputManager::GetInstance()
{
	static InputManager manager;
	return manager;
}

InputManager::InputManager()
{
	for (int i = 0; i < 355; ++i)
	{
		KEYS[i] = false;
	}
}

InputManager::~InputManager()
{
	// go through the map
	for (auto &pair : m_keyDownActionMap)
	{
		// delete the pointer
		delete pair.second;
	}
	m_keyDownActionMap.clear();
}

void InputManager::Update(float dt)
{
	for (auto &pair : m_keyPressedAction)
	{
		if (KEYS[pair.first])
		{
			pair.second->Call(dt);
		}
	}
}

void InputManager::OnKeyDown(SDL_Keycode key)
{
	auto iter = m_keyDownActionMap.find(key);
	if (iter != m_keyDownActionMap.end())
	{
		iter->second->Call();
	}
}

void InputManager::OnKeyUp(SDL_Keycode key)
{
	auto iter = m_keyUpActionMap.find(key);
	if (iter != m_keyUpActionMap.end())
	{
		iter->second->Call();
	}
}

bool InputManager::IsKeyExist(SDL_Keycode newKey)
{
	// look up new key in action map
	auto iter = m_keyDownActionMap.find(newKey);
	return (iter != m_keyDownActionMap.end());
}

void InputManager::RebindKey(const std::string &actionName, SDL_Keycode newKey)
{
	// look up the old key
	auto oldKeyIter = m_ActionNameKeyMap.find(actionName);

	if (oldKeyIter != m_ActionNameKeyMap.end())
	{
		// look up the callback
		auto oldKey = oldKeyIter->second;

		// update key pressed
		auto iterPressed = m_keyPressedAction.find(oldKey);
		if (iterPressed != m_keyPressedAction.end())
		{
			auto callbackPressed = iterPressed->second;

			m_keyPressedAction[newKey] = callbackPressed;
			m_keyPressedAction.erase(oldKey);
		}

		// update key down map
		auto iterDown = m_keyDownActionMap.find(oldKey);
		if (iterDown != m_keyDownActionMap.end())
		{
			auto callbackDown = iterDown->second;

			m_keyDownActionMap[newKey] = callbackDown;
			m_keyDownActionMap.erase(oldKey);

			// update key up map
			auto iterUp = m_keyUpActionMap.find(oldKey);
			if (iterUp != m_keyUpActionMap.end())
			{
				auto callbackUp = iterUp->second;

				m_keyUpActionMap[newKey] = callbackUp;
				m_keyUpActionMap.erase(oldKey);
			}
		}
	}

	m_ActionNameKeyMap[actionName] = newKey;
}
