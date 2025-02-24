#include "Map.h"

#include "InputManager.h"
#include <fstream>
#include <iostream>
#include <sstream>

TextureManager* Map::textureManager = nullptr;

Map::Map(const std::string& mapName, const std::string& tilesetPath, int mapWidth, int mapHeight, int tileWidth, int tileHeight, Game* parentGame)
	: mapName(mapName),tileWidth(tileWidth), tileHeight(tileHeight),
	  mapWidth(mapWidth), mapHeight(mapHeight), game(parentGame), offsetX(0), offsetY(0), player(nullptr) {
	textureManager->Load(mapName, tilesetPath);
	tileset = textureManager->GetTexture(mapName);
	if (!tileset) {
		std::cerr << "Failed to load tileset: " << tilesetPath << std::endl;
		return;
	}
	int textureWidth, textureHeight;
	SDL_QueryTexture(tileset, NULL, NULL, &textureWidth, &textureHeight);
	tilesetColumns = textureWidth / tileWidth;
	std::cout << "Map's texture sheet ' (" << mapName << ") loaded from " << tilesetPath << std::endl;

	GameObject* apolos = new GameObject("char2", 0, 0, 32, 32, 4, 100, this);
	GameObject* apolos2 = new GameObject("char3", 100, 100, 32, 32, 1, 100, this);
	player = new Player("player", 4, 0, 0,this);
	objects.push_back(apolos);
	objects.push_back(apolos2);
}

Map::~Map() {
	std::cout << "Map with name' (" << mapName << ") destroyed!" << std::endl;
}

void Map::loadMap(const std::string& filePath) {
	std::ifstream file(filePath);
	if (!file.is_open()) {
		std::cerr << "Failed to load map file: " << filePath << std::endl;
		return;
	}
	std::string line;
	while (std::getline(file, line)) {
		std::vector<int> row;
		std::istringstream iss(line);
		std::string tile;
		while (std::getline(iss, tile, ',')) {
			row.push_back(std::stoi(tile));
		}
		tiles.push_back(row);
	}
	file.close();
	std::cout << "Map's structure loaded from:" << filePath << std::endl;
	// delete this sht later
	std::cout << "Loaded map:" << std::endl;
	for (const auto& row : tiles) {
		for (const auto& tile : row) {
			std::cout << tile << " ";
		}
		std::cout << std::endl;
	}
}

void Map::update() {
    // Update player input and objects in the map.
    InputManager* input = game->input;
    player->handleInput(input);
    player->update();
    for (auto object : objects) {
        object->update();
    }
    updateCamera();
}

void Map::updateCamera() {
    int targetOffsetX = player->x + player->destRect.w / 2 - game->getWindowWidth() / 2;
    int targetOffsetY = player->y + player->destRect.h / 2 - game->getWindowHeight() / 2;
    // smooth
	float interpolationFactor = 0.01f;
    offsetX += (targetOffsetX - offsetX) * interpolationFactor;
    offsetY += (targetOffsetY - offsetY) * interpolationFactor;
//    offsetX = std::max(0, std::min(offsetX, mapWidth * tileWidth - game->getWindowWidth()));
//    offsetY = std::max(0, std::min(offsetY, mapHeight * tileHeight - game->getWindowHeight()));
}

void Map::render() {
    // Render map tiles
    for (int row = 0; row < tiles.size(); ++row) {
        for (int col = 0; col < tiles[row].size(); ++col) {
            int tileID = tiles[row][col];
            SDL_Rect src;
            src.x = (tileID % tilesetColumns) * tileWidth;  
            src.y = (tileID / tilesetColumns) * tileHeight; 
            src.w = tileWidth;
            src.h = tileHeight;
            SDL_Rect dest;
            dest.x = col * tileWidth - offsetX;
            dest.y = row * tileHeight - offsetY;
            dest.w = tileWidth;
            dest.h = tileHeight;
            SDL_RenderCopy(game->renderer, tileset, &src, &dest);
        }
    }

    // Render objects
    for (auto object : objects) {
        object->render();
    }

    // Render player
    player->render();
}

void Map::clearObjects() {
	for (auto object : objects) {
		delete object;
	}
	delete player;
	objects.clear();
	std::cout << "All objects from Map (" << mapName << ") destroyed" << std::endl;
}

int Map::getOffsetX() {
	return offsetX;
}

int Map::getOffsetY() {
	return offsetY;
}
