#include "GameObject.h"

GameObject::GameObject(std::string textureID, int x, int y, int frameWidth, int frameHeight)
    : textureID(textureID), x(x), y(y), 
	frameWidth(frameWidth), frameHeight(frameHeight), 
	currentFrame(0), currentRow(0) 
	{
    srcRect = { 0, 0, frameWidth, frameHeight };
    destRect = { x, y, frameWidth, frameHeight };
    textureManager = new TextureManager();
}
GameObject::~GameObject() {
    std::cout << "Game Object Destroyed!" << std::endl;
}
void GameObject::Update() {
    currentFrame = (SDL_GetTicks() / 100) % 2;
    srcRect.x = frameWidth * currentFrame;
    srcRect.y = frameHeight * currentRow;
    destRect.x = x;
    destRect.y = y;
}
void GameObject::Render() {
    textureManager->DrawFrame(textureID, srcRect ,destRect, currentRow, currentFrame, frameWidth, frameHeight);
}
