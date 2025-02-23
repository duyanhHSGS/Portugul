#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include "Map.h"
#include "InputManager.h"
#include "TextureManager.h"

//forward
class Map;

class Game {
	private:
		SDL_Window* window;
		bool isRunning;
		std::vector<Map*> maps; //A game contains many maps
		TextureManager* textureManager;
	public:
		Game();
		~Game();
		InputManager* input;
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
