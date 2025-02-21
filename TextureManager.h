#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <map>

class TextureManager {
public:
    TextureManager();
    ~TextureManager();
    void Init();
    bool Load(const std::string& id, const std::string& filename);
    SDL_Texture* GetTexture(const std::string& id);
    void DrawFrame(const std::string& id, SDL_Rect src, SDL_Rect dest, int currentRow, int currentFrame, int frameWidth, int frameHeight);
    void ClearFromTextureMap(const std::string& id);
    void Clean();
    void printAllTextures();
    bool checkExists(const std::string& id);
private:
    static std::map<std::string, SDL_Texture*> textureMap;
    SDL_Texture* LoadTexture(const std::string& filename);
    void Draw(SDL_Texture* texture, SDL_Rect src, SDL_Rect dest);
};

#endif // TEXTURE_MANAGER_H
