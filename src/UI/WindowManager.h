/* This class's main responsibility is to manage all the UI windows in the game using State Pattern
 * It has a pointer to the current window that needs to be updated and rendered
 * When there's input, set window function is called to "point" to the wanted ui
 * then update and render it
 */
#ifndef WINDOWMANAGER_H
#define WINDOWMANAGER_H

#include "../ECS/ECS.h"

/* An interface for all windows
Inherits by all the specific windows in game */

//----------------------------------------------------------------------------------------------------------//
//----------------------------------------------Window State------------------------------------------------//
//----------------------------------------------------------------------------------------------------------//
class Window
{
public:
	virtual ~Window() {};
	virtual void Update(float deltaTime) {};
	virtual bool IsInGame() = 0;

	virtual void OnEnter();
	virtual void OnExit();

	// void* m_FONT = GLUT_BITMAP_9_BY_15;

protected:
	std::vector<Entity> m_entitites;
};

/* Creates all the static windows object to use when needs to set window */
class GameWindow;
class PauseWindow;

class WindowState
{
public:
	static GameWindow vitals;
	static PauseWindow pause;
};

//----------------------------------------------------------------------------------------------------------//
//----------------------------------------------Window Manager----------------------------------------------//
//----------------------------------------------------------------------------------------------------------//
struct SDL_Renderer;

class WindowManager
{
public:
	WindowManager();
	WindowManager(const WindowManager &) = delete; // avoid copy constructor

	void Init(SDL_Renderer *renderer);
	void SetWindow(Window &window);
	void Update(float deltaTime);
	void Render();

	Window *GetCurrentWindow() { return m_current_window; }
	void Restart();

	// singleton
	static WindowManager &GetInstance();

private:
	Window *m_current_window;
	SDL_Renderer *m_renderer;
};

#endif