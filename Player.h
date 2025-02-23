#ifndef PLAYER_H
#define PLAYER_H
#include "GameObject.h"
#include <string>
#include <cmath>

class Player : public GameObject {
	public:
		Player(std::string textureID, int totalFrame, int x, int y, Map* parentMap);
		~Player();
		void handleInput(InputManager* input) override;
		void update() override;
		void render() override;
	private:
		float movementSpeed, velocityX, velocityY;
		std::string state;
		std::string direction;
		SDL_Rect hitbox;
		float health;
		Uint32 attackStartTime;
};

#endif // PLAYER_H
