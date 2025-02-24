#ifndef MAP_H
#define MAP_H

#include "Game.h"
#include "GameObject.h" 
#include "Player.h"   

#include <vector>           
#include <string>           

//forward
class Game;
class GameObject;
class Player;

class Map {
	public:
		Map(const std::string& mapName, const std::string& tilesetPath, int mapWidth, int mapHeight, int tileWidth, int tileHeight, Game* parentGame);
		~Map();
		static TextureManager* textureManager;

		void loadMap(const std::string& filePath);
		void loadTileset(const std::string& filename);
		bool isColliding(const SDL_Rect& rect);
		int getTileType(int tileX, int tileY);
		void setTile(int tileX, int tileY, int tileType);
		int getOffsetX();
		int getOffsetY();

		void render();
		void update();
		void updateCamera();
		void clearObjects();

	private:
		std::string mapName;
		std::vector<std::vector<int>> tiles; //array 
		SDL_Texture* tileset; //store the map's texture sheet
		
		std::vector<GameObject*> objects; // a map contains many objects
		Game* game; // a map have only 1 game as its parent
		Player* player; // a map can only contains 1 player at any time
		
		int mapWidth, mapHeight;
		int tileWidth, tileHeight;
		int tilesetColumns; //current collumn in the texture sheet
		int offsetX, offsetY; // camera
};

#endif
