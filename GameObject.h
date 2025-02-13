#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "TextureManager.h"

class GameObject {
	private:
		SDL_Texture* texture;
	public:
		int x, y;
		SDL_Rect srcRect, destRect;
		GameObject(const char* filename, int x, int y);
		~GameObject();
		void Update();
		void Render();
};
#endif // GAME_OBJECT_H