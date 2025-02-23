#include "TextureManager.h"
#include <vector>
#include "Game.h"

std::map<std::string, SDL_Texture*> TextureManager::textureMap;

TextureManager::TextureManager() {
    std::cout << "An instance of TextureManager was created!" << std::endl;
}

TextureManager::~TextureManager() {
    std::cout << "An instance of TextureManager was destroyed!" << std::endl;
}

void TextureManager::Init() {
    if (textureMap.find("default") != textureMap.end()) {
        std::cout << "Warning: the default texture is already loaded!" << std::endl;
        return;
    }
    if (!Load("default", "img/default.png")) {
        std::cout << "Error: Cannot load the default texture!" << std::endl;
        return;
    }
    std::cout << "The default texture is loaded successfully!" << std::endl;
}

bool TextureManager::checkExists(const std::string& id) {
    return textureMap.find(id) != textureMap.end();
}

bool TextureManager::Load(const std::string& id, const std::string& filename) {
    SDL_Texture* texture = LoadTexture(filename);
    if (texture == nullptr) {
        std::cout << "Failed to load texture: " << filename << std::endl;
        return false;
    }
    std::cout << "Loading texture with ID: " << id << std::endl;
    textureMap.insert({id, texture});
    return true;
}

SDL_Texture* TextureManager::GetTexture(const std::string& id) {
    auto it = textureMap.find(id);
    if (it == textureMap.end()) {
        std::cout << "Could not find any texture with that ID: " << id << std::endl;
        return nullptr;
    }
    return it->second;
}

void TextureManager::Clean() {
    std::vector<std::string> textureIDs;
    for (const auto& pair : textureMap) {
        textureIDs.push_back(pair.first);
    }
    for (const auto& id : textureIDs) {
        ClearFromTextureMap(id);
    }
    if (!textureMap.empty()) {
        textureMap.clear();
    }
    std::cout << "Cleared all textures successfully!" << std::endl;
}

void TextureManager::ClearFromTextureMap(const std::string& id) {
    if (id.empty()) {
        std::cerr << "Error: Texture ID is empty!" << std::endl;
        return;
    }
    auto it = textureMap.find(id);
    if (it == textureMap.end()) {
        std::cout << "Could not find any texture with ID: " << id << std::endl;
        return;
    }
    SDL_DestroyTexture(it->second);
    textureMap.erase(it);
    std::cout << "Erased texture with ID: " << id << " successfully!" << std::endl;
}

void TextureManager::DrawFrame(
    const std::string& id,
    SDL_Rect src,
    SDL_Rect dest,
    int currentRow,
    int currentFrame,
    int frameWidth,
    int frameHeight
) {
    auto it = textureMap.find(id);
    if (it == textureMap.end()) {
        std::cerr << "Could not find any texture with ID: " << id << std::endl;
        return;
    }
    src.x = frameWidth * currentFrame;
    src.y = frameHeight * currentRow;
    src.w = frameWidth;
    src.h = frameHeight;
    SDL_Texture* texture = it->second;
    Draw(texture, src, dest);
}

void TextureManager::DrawTile(const std::string& id, SDL_Rect src, SDL_Rect dest) {
    auto it = textureMap.find(id);
    if (it == textureMap.end()) {
        std::cerr << "Could not find any texture with ID: " << id << std::endl;
        return;
    }
    SDL_Texture* texture = it->second;
    Draw(texture, src, dest);
}

void TextureManager::printAllTextures() {
    std::cout << "All textures:" << std::endl;
    for (const auto& maps : textureMap) {
        std::cout << maps.first << std::endl;
    }
}

// private
SDL_Texture* TextureManager::LoadTexture(const std::string& filename) {
    SDL_Surface* tmpSurface = IMG_Load(filename.c_str());
    if (!tmpSurface) {
        std::cerr << "Failed to load image: " << IMG_GetError() << std::endl;
        return nullptr;
    }
    std::cout << "Successfully loaded " << filename << std::endl;
    SDL_Texture* texture = SDL_CreateTextureFromSurface(Game::renderer, tmpSurface);
    if (texture == nullptr) {
        std::cerr << "Failed to create texture: " << SDL_GetError() << std::endl;
        SDL_FreeSurface(tmpSurface);
        return nullptr;
    }
    SDL_FreeSurface(tmpSurface);
    return texture;
}

void TextureManager::Draw(SDL_Texture* texture, SDL_Rect src, SDL_Rect dest) {
    SDL_RenderCopy(Game::renderer, texture, &src, &dest);
}
