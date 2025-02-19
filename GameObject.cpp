#include "GameObject.h"
TextureManager* GameObject::textureManager = nullptr;
GameObject::GameObject
(const std::string textureID, int x, int y,
 int frameWidth, int frameHeight, int totalFrames,
 int animationSpeed)
	: textureID(textureID), x(x), y(y),
	  frameWidth(frameWidth), frameHeight(frameHeight),
	  currentFrame(0), currentRow(0),
	  totalFrames(totalFrames), animationSpeed(animationSpeed) {
	if (!textureManager->checkExists(textureID)) {
		std::cout << "Warning: The textureID provided (" << textureID << ") was not found, changing to default texture." << std::endl;
		this->textureID = "default";
	}
	srcRect = { 0, 0, frameWidth, frameHeight };
	destRect = { x, y, frameWidth, frameHeight };
}
GameObject::~GameObject() {
	std::cout << "Game Object Destroyed!" << std::endl;
}
void GameObject::Update() {
	currentFrame = (SDL_GetTicks() / animationSpeed) % totalFrames;

	srcRect.x = frameWidth * currentFrame;
	srcRect.y = frameHeight * currentRow;
	destRect.x = x;
	destRect.y = y;
}
void GameObject::Render() {
	textureManager->DrawFrame(textureID, srcRect, destRect, currentRow, currentFrame, frameWidth, frameHeight);
}
