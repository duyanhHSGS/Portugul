#include "Game.h"

Map* map1 = nullptr;

SDL_Renderer* Game::renderer = nullptr;
Game::Game()
	: window(nullptr), input(nullptr),
	  isRunning(false), windowWidth(0), windowHeight(0) {}

Game::~Game() {
	clean();
}

int Game::getWindowWidth() {
	return windowWidth;
}
int Game::getWindowHeight() {
	return windowHeight;
}

bool Game::init(const std::string& title, int xpos, int ypos, int windowWidth, int windowHeight, bool fullscreen) {
	this->windowWidth = windowWidth;
	this->windowHeight = windowHeight;
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


	int flags = SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE;
	if (fullscreen) {
		flags |= SDL_WINDOW_FULLSCREEN;
	}
	window = SDL_CreateWindow(title.c_str(), xpos, ypos, windowWidth, windowHeight, flags);
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
	input = new InputManager();
	std::cout << "Input: Listening!" << std::endl;


	textureManager = new TextureManager();
	textureManager->Init();
	textureManager->Load("char2", "img/char2.png");
	textureManager->Load("apple", "img/apple.png");
	textureManager->Load("player", "img/player.png");

	GameObject::textureManager = textureManager;
	Map::textureManager = textureManager;
	textureManager->printAllTextures();

	map1 = new Map("Map1","img/map1.png",600,800,32,32,this);
	map1->loadMap("maps/map1.txt");
	maps.push_back(map1);

	isRunning = true;
	return true;
}

int mx=1, my=1; //mouse pos
void Game::handleEvents() {
	input->handleEvents();
	if (input->isQuitRequested()) {
		std::cout << "Quit event received, shutting down..." << std::endl;
		isRunning = false;
	}
	if (input->windowResized) {
		windowWidth = input->newWindowWidth;
		windowHeight = input->newWindowHeight;
		std::cout << "Window resized to: " << windowWidth << "x" << windowHeight << std::endl;
	}
	if (input->isKeyPressed(SDL_SCANCODE_F12)) {
		static bool isFullscreen = false;
		isFullscreen = !isFullscreen;
		SDL_SetWindowFullscreen(window, isFullscreen ? SDL_WINDOW_FULLSCREEN : 0);
		std::cout << "Toggled fullscreen: " << (isFullscreen ? "ON" : "OFF") << std::endl;
	}
	if (input->isMouseClicked(SDL_BUTTON_LEFT)) {
		input->getMousePosition(mx, my);
		std::cout << "Mouse clicked at (" << mx << "," << my << ")" << std::endl;
	}
	input->resetForFrame();
}

void Game::update() {
	for (auto map : maps) {
		map->update();
	}
}

void Game::render() {
	//render background
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255 );
	SDL_RenderClear(renderer);
	//render maps
	for (auto map : maps) {
		map->render();
	}
	//render mouse
	input->getMousePosition(mx, my);
	SDL_Rect gameMouse = { mx-5, my-5, 10, 10 };
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	SDL_RenderFillRect(renderer, &gameMouse);
	//implement more later
	SDL_RenderPresent(renderer);
}

void Game::clean() {
	for (auto map : maps) {
		map->clearObjects();
		delete map;
	}
	maps.clear();
	std::cout << "All Maps Destroyed!" << std::endl;

	delete input;
	std::cout << "Input: Stopped Listening!" << std::endl;

	textureManager->Clean();
	delete textureManager;
	std::cout << "All stored textures cleared!" << std::endl;

	SDL_DestroyRenderer(renderer);
	std::cout << "Renderer Destroyed!" << std::endl;
	SDL_DestroyWindow(window);
	std::cout << "Window Destroyed!" << std::endl;
	IMG_Quit();
	SDL_Quit();
}