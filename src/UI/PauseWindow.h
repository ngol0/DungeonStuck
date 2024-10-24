/* Includes health and resources bar */
#ifndef PAUSEWINDOW_H
#define PAUSEWINDOW_H

#include "WindowManager.h"
#include "../Events/EventData.h"

class PauseWindow : public Window
{
public:
	PauseWindow() {};

    void Init();
	virtual void OnEnter() override;
	virtual void Update(float deltaTime) override;
	virtual void OnExit() override;
	virtual bool IsInGame() override { return false; }

    void OnKeyPressed(KeyPressedEventData &data);
};

#endif