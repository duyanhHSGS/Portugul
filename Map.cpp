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

	GameObject* apolos = new GameObject("char2", 10, 10, 64, 64, 4, 100, this);
	GameObject* apolos2 = new GameObject("char3", 100, 100, 64, 64, 1, 100, this);
	player = new Player("player", 4, 500, 500,this);
	objects.push_back(apolos);
	objects.push_back(apolos2);
	objects.push_back(player);
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

void Map::render() {
	// Check if the tileset is loaded.
	if (!tileset) {
		std::cerr << "No tileset loaded for map " << mapName << std::endl;
		return;
	}
	// Loop through each row of the tile grid.
	for (int row = 0; row < tiles.size(); ++row) {
		// Loop through each column in the current row.
		for (int col = 0; col < tiles[row].size(); ++col) {
			int tileID = tiles[row][col];  // Get the tile ID at (row, col)

			// Compute the source rectangle from the tileset:
			SDL_Rect src;
			// Calculate column and row in the tileset image.
			src.x = (tileID % tilesetColumns) * tileWidth;  // tile's column in the tileset
			src.y = (tileID / tilesetColumns) * tileHeight;   // tile's row in the tileset
			src.w = tileWidth;
			src.h = tileHeight;

			// Compute the destination rectangle on the screen:
			SDL_Rect dest;
			// Multiply grid position by tile size, then subtract camera offset.
			dest.x = col * tileWidth - offsetX;
			dest.y = row * tileHeight - offsetY;
			dest.w = tileWidth;
			dest.h = tileHeight;

			// Draw the tile using SDL_RenderCopy.
			SDL_RenderCopy(game->renderer, tileset, &src, &dest);
		}
	}
	//render objects
	for (auto object : objects) {
		object->render();
	}
}


void Map::update() {
	//update objects inside it
	InputManager* input = game->input;
	player->handleInput(input);
	for ( auto object : objects ) {
		object->update();
	}

	updateCamera(player->destRect,800,600);
	//implement more later
}

void Map::updateCamera(const SDL_Rect& playerRect, int screenWidth, int screenHeight) {
    // Calculate the offset to center the player
    int targetOffsetX = playerRect.x + playerRect.w / 2 - screenWidth / 2;
    int targetOffsetY = playerRect.y + playerRect.h / 2 - screenHeight / 2;

    // Print debug information
    std::cout << "Player Position: (" << playerRect.x << ", " << playerRect.y << ")\n";
    std::cout << "Target Offsets: (" << targetOffsetX << ", " << targetOffsetY << ")\n";
    std::cout << "Current Offsets: (" << offsetX << ", " << offsetY << ")\n";

    // Interpolating for smooth camera movement
    float interpolationFactor = 0.1f; // Adjust for smoothness
    offsetX += (targetOffsetX - offsetX) * interpolationFactor;
    offsetY += (targetOffsetY - offsetY) * interpolationFactor;

    // Print after interpolation
    std::cout << "Interpolated Offsets: (" << offsetX << ", " << offsetY << ")\n";

    // Clamp to map boundaries
    offsetX = std::max(0, std::min(offsetX, mapWidth * tileWidth - screenWidth));
    offsetY = std::max(0, std::min(offsetY, mapHeight * tileHeight - screenHeight));

    // Print final adjusted offsets
    std::cout << "Adjusted Offsets: (" << offsetX << ", " << offsetY << ")\n";
}




void Map::clearObjects() {
	for (auto object : objects) {
		delete object;
	}
	objects.clear();
	std::cout << "All objects from Map (" << mapName << ") destroyed" << std::endl;
}

int Map::getOffsetX() {
	return offsetX;
}

int Map::getOffsetY() {
	return offsetY;
}
