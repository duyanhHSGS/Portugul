#include "Player.h"
#include <iostream>
#include <cmath>

// del this later
#include "Game.h"

Player::Player(std::string textureID, int totalFrame, int x, int y, Map* parentMap)
	: GameObject(textureID, x, y, 32, 32, 6, 100,parentMap),
	  movementSpeed(5.0f),
	  state("Idle"),
	  health(100.0f),
	  velocityX(0), velocityY(0),
	  direction("Left") {
	hitbox = { x, y, 64, 64 };
	std::cout << "Player created!" << std::endl;
}

Player::~Player() {
	std::cout << "Player destroyed!" << std::endl;
}

void Player::handleInput(InputManager* input) {
    if (state == "Attacking") {
        return;
    }
    float dx = 0.0f, dy = 0.0f;
    if (input->isKeyDown(SDL_SCANCODE_W)) dy -= 1.0f;
    if (input->isKeyDown(SDL_SCANCODE_S)) dy += 1.0f;
    if (input->isKeyDown(SDL_SCANCODE_A)) dx -= 1.0f;
    if (input->isKeyDown(SDL_SCANCODE_D)) dx += 1.0f;

    float length = sqrt(dx * dx + dy * dy);
    if (length > 0) {
        float angle = atan2(dy, dx);
        velocityX = movementSpeed * cos(angle); 
        velocityY = movementSpeed * sin(angle); 
        state = "Moving";
        if (velocityX > 0) direction = "Right";
        if (velocityX < 0) direction = "Left";
    } else {
        state = "Idle"; // Set state to idle if no keys are pressed
    }

    if (input->isMouseClicked(SDL_BUTTON_LEFT) && state != "Attacking") {
        std::cout << "The player is attacking!" << std::endl;
        state = "Attacking";
        currentFrame = 0;
        attackStartTime = SDL_GetTicks();
    }
}

void Player::update() {
    if (state == "Attacking") {
        velocityX = 0.0f;
        velocityY = 0.0f;
        Uint32 currentTime = SDL_GetTicks();
        Uint32 elapsed = currentTime - attackStartTime;
        currentFrame = elapsed / animationSpeed;
        if (currentFrame >= totalFrames) {
            currentFrame = 0;
            state = "Idle";
        }
    } else {
        if (state == "Idle") {
            float friction = 0.95f; // Friction factor (adjust as needed)
            velocityX *= friction;
            velocityY *= friction;
        }
        x += velocityX;
        y += velocityY;

        currentFrame = (SDL_GetTicks() / animationSpeed) % totalFrames;
        if (abs(velocityX) < 0.1f && abs(velocityY) < 0.1f) {
            velocityX = 0.0f;
            velocityY = 0.0f;
            state = "Idle";
        }
    }
    destRect.x = x - map->getOffsetX();
    destRect.y = y - map->getOffsetY();
}


void Player::render() {
	SDL_Texture* tex = textureManager->GetTexture(textureID);
	if (!tex) {
		std::cerr << "Texture not found for ID: " << textureID << std::endl;
		return;
	}
	int renderRow = 0;
	if (state == "Idle") renderRow = 0;
	if (state == "Moving") renderRow = 1;
	if (state == "Attacking") renderRow = 3;

	srcRect.y = renderRow * frameHeight;
	srcRect.x = frameWidth * currentFrame;
	if (direction == "Right") {
		SDL_RenderCopyEx(Game::renderer, tex, &srcRect, &destRect, 0, NULL, SDL_FLIP_HORIZONTAL);
	} else {
		SDL_RenderCopy(Game::renderer, tex, &srcRect, &destRect);
	}
}

