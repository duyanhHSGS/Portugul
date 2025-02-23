#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "TextureManager.h"
#include "InputManager.h"
#include <string.h>

//forward
class Map;

class GameObject {
	protected:
		std::string textureID;
		int currentFrame;
		int currentRow;
		int frameWidth;
		int frameHeight;
		int totalFrames;
		int animationSpeed;
		SDL_Rect srcRect;
		Map* map; //an object only have 1 map as its parent
	public:
		static TextureManager* textureManager;
		bool collidesWith(GameObject* other);
		void switchAnimation(int newRow);
		int x, y;
		SDL_Rect destRect;
		GameObject(std::string textureID, int x, int y, int frameWidth, int frameHeight, int totalFrames, int animationSpeed, Map* parentMap);
		~GameObject();
		virtual void update();
		virtual void render();
		virtual void handleInput(InputManager* input);	
};

#endif // GAME_OBJECT_H