#include "GameObject.h"

GameObject::GameObject(const char* filename, int x, int y)
    : texture(nullptr), x(x), y(y), srcRect({0,0,0,0}), destRect({0,0,0,0}) {
    texture = TextureManager::LoadTexture(filename);
    if (texture == nullptr) {
        std::cerr << "Failed to load texture: " << SDL_GetError() << std::endl;
    } else {
        int texW, texH;
        SDL_QueryTexture(texture, NULL, NULL, &texW, &texH);
        srcRect = {0, 0, texW, texH};
    }
}

GameObject::~GameObject() {
    if (texture != nullptr) {
        SDL_DestroyTexture(texture);
        std::cout << "Texture Destroyed!" << std::endl;
    }
    std::cout << "Game Object Destroyed!" << std::endl;
}

void GameObject::Update() {
    destRect = {x, y, srcRect.w*2, srcRect.h*2};
}

void GameObject::Render() {
    if (texture == nullptr) {
        std::cerr << "Could not load texture!" << std::endl;
        return;
    }
    TextureManager::Draw(texture, srcRect, destRect);
}
