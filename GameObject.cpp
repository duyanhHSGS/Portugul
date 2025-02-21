#include "GameObject.h"
TextureManager* GameObject::textureManager = nullptr;
GameObject::GameObject
(const std::string textureID, int x, int y,
 int frameWidth, int frameHeight, int totalFrames,
 int animationSpeed)
	: textureID(textureID), x(x), y(y),
	  frameWidth(frameWidth), frameHeight(frameHeight),
	  currentFrame(0), currentRow(0), isActive(true),
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
void GameObject::update() {
	currentFrame = (SDL_GetTicks() / animationSpeed) % totalFrames;

	srcRect.x = frameWidth * currentFrame;
	srcRect.y = frameHeight * currentRow;
	destRect.x = x;
	destRect.y = y;
}
void GameObject::switchAnimation(int newRow) {
	std::cout << "Switching animation of the object from row " << currentRow<< " to " << newRow << "!" << std::endl;
	currentRow = newRow;
	currentFrame = 0;
}

bool GameObject::collidesWith(GameObject* other) {
    return SDL_HasIntersection(&this->destRect, &other->destRect);
}

void GameObject::render() {
    if (!isActive) {
        Uint8 alpha = static_cast<Uint8>(std::max(0.0f, 255 - (inactiveTime * 255.0f / 3.0f)));
        std::cout << "alpha = "  << (int)alpha << std::endl;
        SDL_SetTextureAlphaMod(textureManager->GetTexture(textureID), alpha);
    }
    textureManager->DrawFrame(textureID, srcRect, destRect, currentRow, currentFrame, frameWidth, frameHeight);
}

