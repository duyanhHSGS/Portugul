#include "TextureManager.h"

SDL_Renderer* TextureManager::renderer = nullptr;
void TextureManager::SetRenderer(SDL_Renderer* ren) {
	renderer = ren;
}
SDL_Texture* TextureManager::LoadTexture(const char* filename) {
	SDL_Surface* tmpSurface = IMG_Load(filename);
	    if (!tmpSurface) {
        std::cerr << "Failed to load image: " << IMG_GetError() << std::endl;
        return nullptr;
    }
    std::cout << "Successfully loaded " << filename << std::endl;
	SDL_Texture* texture = SDL_CreateTextureFromSurface(Game::renderer, tmpSurface);
	SDL_FreeSurface(tmpSurface);
	return texture;
}

void TextureManager::Draw(SDL_Texture* texture, SDL_Rect src, SDL_Rect dest) {
    SDL_RenderCopy(renderer, texture, &src, &dest);
}