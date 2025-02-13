#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include "Game.h"

class TextureManager {
	public:
		static void SetRenderer(SDL_Renderer* ren);
		static SDL_Texture* LoadTexture(const char* filename);
		static void Draw(SDL_Texture* texture, SDL_Rect src, SDL_Rect dest);
	private:
		static SDL_Renderer* renderer;
};

#endif // TEXTURE_MANAGER_H
