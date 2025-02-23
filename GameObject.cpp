#include "GameObject.h"
#include "Map.h"
TextureManager* GameObject::textureManager = nullptr;

GameObject::GameObject
(const std::string textureID, int x, int y,
 int frameWidth, int frameHeight, int totalFrames,
 int animationSpeed, Map* parentMap)
	: textureID(textureID), x(x), y(y),
	  frameWidth(frameWidth), frameHeight(frameHeight),
	  currentFrame(0), currentRow(0),
	  totalFrames(totalFrames), animationSpeed(animationSpeed), map(parentMap) {
	if (!textureManager->checkExists(textureID)) {
		std::cout << "Warning: The textureID provided (" << textureID << ") was not found, changing to default texture." << std::endl;
		this->textureID = "default";
	}
	srcRect = { 0, 0, frameWidth, frameHeight };
	destRect = { x, y, frameWidth, frameHeight };
	std::cout << "Game Object created!" << std::endl;
}
GameObject::~GameObject() {
	std::cout << "Game Object destroyed!" << std::endl;
}
void GameObject::update() {
	currentFrame = (SDL_GetTicks() / animationSpeed) % totalFrames;

	srcRect.x = frameWidth * currentFrame;
	srcRect.y = frameHeight * currentRow;
	destRect.x = x - map->getOffsetX();
	destRect.y = y - map->getOffsetY();
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
	textureManager->DrawFrame(textureID, srcRect, destRect, currentRow, currentFrame, frameWidth, frameHeight);
}

void GameObject::handleInput(InputManager* input) {
}

