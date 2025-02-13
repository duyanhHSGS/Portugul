#ifndef GAME_H
#define GAME_H
#include "GameObject.h"
#include "InputManager.h"
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <string>
#include <vector>

class Game {
	private:
		SDL_Window* window;
		bool isRunning;
		std::vector<GameObject*> objects;
		InputManager* input;
	public:
		Game();
		~Game();
		bool init(const std::string& title, int x, int y, int width, int height, bool fullscreen);
		void handleEvents();
		void update();
		void render();
		void clean();
		bool running() const {
			return isRunning;
		}
		static SDL_Renderer* renderer;
};

#endif // GAME_H
