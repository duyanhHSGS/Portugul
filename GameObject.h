#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "TextureManager.h"
#include <string.h>
class GameObject {
	private:
		std::string textureID;
		TextureManager* textureManager;
		int currentFrame;
		int currentRow;
		int frameWidth;
		int frameHeight;
		SDL_Rect srcRect;
	public:
		int x, y;
		SDL_Rect destRect;
		GameObject(std::string textureID, int x, int y, int frameWidth, int frameHeight);
		~GameObject();
		void Update();
		void Render();
};
#endif // GAME_OBJECT_H