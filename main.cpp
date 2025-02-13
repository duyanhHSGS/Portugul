#include"Game.h"
#include <iostream>

Game* game = nullptr;
int main(int argc, char* argv[]) {
	const int fps = 60;
	const int frameDelay = 1000 / fps;
	Uint32 frameStart;
	int frameTime;

	game = new Game();
	if (!game->init("Portugul", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, false)) {
		std::cerr << "Game Initialization Failed!" << std::endl;
		return 1;
	}
	std::cout << "Game Initiated!" << std::endl;
	
	while (game->running()) {
		frameStart = SDL_GetTicks();
		game->handleEvents();
		game->update();
		game->render();
		frameTime = SDL_GetTicks() - frameStart;
		if (frameDelay > frameTime) SDL_Delay(frameDelay-frameTime);
	}
	game->clean();
	return 0;
}
