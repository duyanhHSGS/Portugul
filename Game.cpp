#include "Game.h"

SDL_Renderer* Game::renderer = nullptr;
Game::Game()
	: window(nullptr), input(nullptr),
	  isRunning(false) {}
Game::~Game() {
	clean();
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
	input = new InputManager();
	std::cout << "Input: Listening!" << std::endl;


	textureManager = new TextureManager();
	textureManager->Init();

	textureManager->Load("char2", "img/char2.png");
	textureManager->Load("apple", "img/apple.png");
	textureManager->Load("player", "img/player.png");

	
	// Print loaded textures
	textureManager->printAllTextures();

	GameObject::textureManager = textureManager;
	GameObject* apolos = new GameObject("char2", 10, 10, 64, 64, 4, 100);
	GameObject* apolos2 = new GameObject("char3", 100, 100, 64, 64, 1, 100);
	Player* player = new Player("player", 4, 500, 500);

	objects.push_back(apolos);
	objects.push_back(apolos2);
	objects.push_back(player);

	isRunning = true;
	return true;
}

void Game::handleEvents() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) {
			std::cout << "SDL_QUIT event received, shutting down..." << std::endl;
			isRunning = false;
		}
	}
	Player* player = (Player*)(objects[2]);
	player->handleInput(input);
	input->resetForFrame();
}

void Game::update() {
    auto destroyer = objects[0];
    std::vector<GameObject*> toBeDeleted;

    for (auto object : objects) {
        object->update();
        
        // If object is inactive, increase its timer
        if (!object->isActive) {
            object->inactiveTime += 0.016f; // Assuming 60 FPS (~16ms per frame)
            if (object->inactiveTime >= 3.0f) {
                toBeDeleted.push_back(object); // Mark for deletion
            }
            continue; // Skip further checks
        }

        // Check collision and deactivate object
        if (destroyer->collidesWith(object) && object != destroyer) {
            std::cout << "Object #0 is colliding with another object!" << std::endl;
            std::cout << "Deactivating that object!" << std::endl;
            object->isActive = false;
        }
    }

    // Delete inactive objects
    for (auto object : toBeDeleted) {
        auto it = std::find(objects.begin(), objects.end(), object);
        if (it != objects.end()) {
            delete *it;
            objects.erase(it);
        }
    }
}


int mx=1, my=1; //mouse pos
void Game::render() {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255 );
	SDL_RenderClear(renderer);
	//render objects
	for ( auto object : objects ) {
		object->render();
	}
	//render mouse
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