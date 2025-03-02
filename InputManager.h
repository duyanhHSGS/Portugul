#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include <SDL.h>

class InputManager {
	private:
		const Uint8* keyStates;
		Uint32 mouseState;
		Uint32 prevMouseState;
		bool quitRequested;
	public:
		InputManager();
		~InputManager();
		void resetForFrame();
		bool isKeyDown(SDL_Scancode key);
		bool isKeyUp(SDL_Scancode key);
		bool isKeyPressed(SDL_Scancode key);
		bool isMouseButtonDown(int button);
		bool isMouseButtonUp(int button);
		void getMousePosition(int &x, int &y);
		bool isMouseClicked(int button);
		bool isQuitRequested();
		void handleEvents();
		
		bool windowResized;
		int newWindowWidth;
		int newWindowHeight;
};

#endif // INPUT_MANAGER_H
