/* Includes health and resources bar */
#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include "WindowManager.h"

class GameWindow : public Window
{
public:
	GameWindow() {};

    void Init();
	virtual void OnEnter() override;
	virtual void Update(float deltaTime) override;
	virtual void OnExit() override;
	virtual bool IsInGame() override { return true; }

    void OnKeyPressed(KeyPressedEventData &data) override;
};

#endif