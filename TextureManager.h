#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <map>


class TextureManager {
	public:
		bool Load(std::string id, std::string filename);
		SDL_Texture* GetTexture(std::string id);
		void DrawFrame(std::string id, SDL_Rect src, SDL_Rect dest, int currentRow, int currentFrame, int frameWidth, int frameHeight);
		void ClearFromTextureMap(std::string id);
		void Clean();
	private:
		static std::map<std::string, SDL_Texture*> textureMap;
		SDL_Texture* LoadTexture(std::string filename);
		void Draw(SDL_Texture* texture, SDL_Rect src, SDL_Rect dest);
};

#endif // TEXTURE_MANAGER_H
