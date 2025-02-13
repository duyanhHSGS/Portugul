#include "Game.h"


SDL_Renderer* Game::renderer = nullptr;
Game::Game()
	: window(nullptr), input(nullptr),
	  isRunning(false) {}
Game::~Game() {
}

bool Game::init(const std::string& title, int xpos, int ypos, int width, int height, bool fullscreen) {
	int flags = fullscreen ? SDL_WINDOW_FULLSCREEN : 0;
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		std::cerr << "SDL Initialization Failed: " << SDL_GetError() << std::endl;
		return false;
	}

	std::cout << "SDL Initiated!" << std::endl;
	if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG) {
		std::cerr << "SDL_image Initialization Failed: " << IMG_GetError() << std::endl;
		SDL_Quit();
		return false;
	}
	std::cout << "SDL Image Initiated!" << std::endl;
	std::cout << "Creating Window" << std::endl;
	window = SDL_CreateWindow(title.c_str(), xpos, ypos, width, height, flags);
	if (!window) {
		std::cerr << "Window Creation Failed: " << SDL_GetError() << std::endl;
		return false;
	}
	std::cout << "Window Created!" << std::endl;
	std::cout << "Creating Renderer" << std::endl;
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (!renderer) {
		std::cerr << "Renderer Creation Failed: " << SDL_GetError() << std::endl;
		return false;
	}
	std::cout << "Renderer Created!" << std::endl;
	TextureManager::SetRenderer(renderer);
	input = new InputManager();
	std::cout << "Input: Listening!" << std::endl;


	GameObject* apolos = new GameObject("img/apple.png", 10, 10);
	GameObject* apolos2 = new GameObject("img/apple.png", 30, 30);
	objects.push_back(apolos);
	objects.push_back(apolos2);

	isRunning = true;
	return true;
}

int mx=1, my=1; //mouse pos
void Game::handleEvents() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) {
			std::cout << "SDL_QUIT event received, shutting down..." << std::endl;
			isRunning = false;
		}
	}
	input->resetForFrame();
	if (input->isKeyDown(SDL_SCANCODE_A)) {
		std::cout << "The 'A' key is being held down." << std::endl;
		objects[0]->x--;
	}
	if (input->isKeyDown(SDL_SCANCODE_W)) {
		std::cout << "The 'W' key is being held down." << std::endl;
		objects[0]->y--;
	}
	if (input->isKeyDown(SDL_SCANCODE_S)) {
		std::cout << "The 'S' key is being held down." << std::endl;
		objects[0]->y++;
	}
	if (input->isKeyDown(SDL_SCANCODE_D)) {
		std::cout << "The 'D' key is being held down." << std::endl;
		objects[0]->x++;
	}
	if (input->isMouseButtonDown(SDL_BUTTON_RIGHT)) {
		std::cout << "The Right Mouse Button is being held down." << std::endl;
		objects[1]->x=mx;
		objects[1]->y=my;
	}
	if (input->isMouseButtonDown(SDL_BUTTON_LEFT)) {
		std::cout << "Clicked at: (" << mx << ", "    << my  << ")." << std::endl;
	}
}


void Game::update() {
	for ( auto object : objects ) {
		object->Update();
	}
}

void Game::render() {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255 );
	SDL_RenderClear(renderer);
	for ( auto object : objects ) {
		object->Render();
	}

	input->getMousePosition(mx, my);
	SDL_Rect gameMouse = { mx-5, my-5, 10, 10 };
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	SDL_RenderFillRect(renderer, &gameMouse);

	SDL_RenderPresent(renderer);
}


void Game::clean() {
	for ( auto object : objects ) {
		delete object;
	}
	objects.clear();
	std::cout << "All Objects Destroyed!" << std::endl;
	delete input;
	std::cout << "Input: Stopped Listening!" << std::endl;
	SDL_DestroyRenderer(renderer);
	std::cout << "Renderer Destroyed!" << std::endl;
	SDL_DestroyWindow(window);
	std::cout << "Window Destroyed!" << std::endl;
	IMG_Quit();
	SDL_Quit();
}