#include "InputManager.h"

InputManager::InputManager() {
    keyStates = SDL_GetKeyboardState(NULL);
    mouseState = 0;
}

InputManager::~InputManager() {}

void InputManager::resetForFrame() {
    SDL_PumpEvents();
    keyStates = SDL_GetKeyboardState(NULL);
    mouseState = SDL_GetMouseState(NULL, NULL);
}

bool InputManager::isKeyDown(SDL_Scancode key) {
    return keyStates[key];
}

bool InputManager::isKeyUp(SDL_Scancode key) {
    return !keyStates[key];
}

bool InputManager::isMouseButtonDown(int button) {
    return mouseState & SDL_BUTTON(button);
}

bool InputManager::isMouseButtonUp(int button) {
    return !(mouseState & SDL_BUTTON(button));
}

void InputManager::getMousePosition(int &x, int &y) {
    SDL_GetMouseState(&x, &y);
}
