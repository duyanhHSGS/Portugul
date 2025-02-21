#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "TextureManager.h"
#include <string.h>
class GameObject {
	protected:
		std::string textureID;
		int currentFrame;
		int currentRow;
		int frameWidth;
		int frameHeight;
		int totalFrames;
		int animationSpeed;
		SDL_Rect srcRect;	
	public:
		bool isActive;
		float inactiveTime=0;
		
		static TextureManager* textureManager;
		bool collidesWith(GameObject* other);
		void switchAnimation(int newRow);
		int x, y;
		SDL_Rect destRect;
		GameObject(std::string textureID, int x, int y, int frameWidth, int frameHeight, int totalFrames, int animationSpeed);
		~GameObject();
		virtual void update();
		virtual void render();
};

#endif // GAME_OBJECT_H