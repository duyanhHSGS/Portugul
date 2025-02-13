#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include <SDL.h>

class InputManager {
	private:
		const Uint8* keyStates;
		Uint32 mouseState;
	public:
		InputManager();
		~InputManager();
		void resetForFrame();
		bool isKeyDown(SDL_Scancode key);
		bool isKeyUp(SDL_Scancode key);
		bool isMouseButtonDown(int button);
		bool isMouseButtonUp(int button);
		void getMousePosition(int &x, int &y);
};

#endif // INPUT_MANAGER_H
