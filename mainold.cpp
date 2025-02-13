#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

const int FPS = 60;
const int frame_delay = 1000/FPS;
SDL_Renderer* renderer = nullptr;
bool running = false;
SDL_Event event;

int main2(int argc, char* argv[]) {
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		std::cerr << "SDL Initialization Failed: " << SDL_GetError() << std::endl;
		return 1;
	}
	if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG) {
		std::cerr << "SDL_image Initialization Failed: " << IMG_GetError() << std::endl;
		SDL_Quit();
		return 1;
	}
	SDL_Window* window = SDL_CreateWindow("Portugul",
	                                      SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
	                                      800, 600, SDL_WINDOW_SHOWN);
	if (!window) {
		std::cerr << "Window Creation Failed: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return 1;
	}
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	// image
	SDL_Surface* imageSurface = IMG_Load("img/apple.png");
	if (!imageSurface) {
		std::cerr << "Failed to load image: " << IMG_GetError() << std::endl;
	}
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, imageSurface);
	if (!texture) {
		std::cerr << "Failed to create texture: " << SDL_GetError() << std::endl;
	}
	SDL_FreeSurface(imageSurface);  // Surface is no longer needed after creating the texture.



	if (!renderer) {
		std::cerr << "Renderer Creation Failed: " << SDL_GetError() << std::endl;
		SDL_DestroyWindow(window);
		SDL_Quit();
		return 1;
	}

	running = true;
	int posX=200, posY=150;
	SDL_Rect destRect;

	while (running) {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				running = false;
			}
			const Uint8* keystate = SDL_GetKeyboardState(NULL);
			if (keystate[SDL_SCANCODE_D]) {
				posX += 5;
			}
			if (keystate[SDL_SCANCODE_A]) {
				posX -= 5;
			}
			if (keystate[SDL_SCANCODE_W]) {
				posY -= 5;
			}
			if (keystate[SDL_SCANCODE_S]) {
				posY += 5;
			}
		}

		SDL_RenderClear(renderer);

		// draw a red rectangle
		destRect = { posX, posY, 400, 300 };
		SDL_RenderCopy(renderer, texture, NULL, &destRect);

		// present the final image
		SDL_RenderPresent(renderer);
		SDL_Delay(frame_delay);
	}

	// Cleanup
	SDL_DestroyTexture(texture);
	IMG_Quit();  // Shutdown SDL_image.

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	SDL_Quit();

	return 0;
}