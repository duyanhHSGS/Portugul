#include "InputManager.h"

InputManager::InputManager() {
    keyStates = SDL_GetKeyboardState(NULL);
    mouseState = 0;
    prevMouseState = 0;
    quitRequested = false;
}

InputManager::~InputManager() {
}

void InputManager::resetForFrame() {
    SDL_PumpEvents();
    keyStates = SDL_GetKeyboardState(NULL);
    prevMouseState = mouseState;
    mouseState = SDL_GetMouseState(NULL, NULL);
}

bool InputManager::isKeyDown(SDL_Scancode key) {
    return keyStates[key];
}

bool InputManager::isKeyUp(SDL_Scancode key) {
    return !keyStates[key];
}

bool InputManager::isKeyPressed(SDL_Scancode key) {
    static Uint8 prevKeyStates[SDL_NUM_SCANCODES] = {0};
    bool pressed = keyStates[key] && !prevKeyStates[key];
    prevKeyStates[key] = keyStates[key];
    return pressed;
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

bool InputManager::isMouseClicked(int button) {
    return (mouseState & SDL_BUTTON(button)) && !(prevMouseState & SDL_BUTTON(button));
}

bool InputManager::isQuitRequested() {
    return quitRequested;
}

void InputManager::handleEvents() {
    windowResized = false;
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            quitRequested = true;
        } else if (event.type == SDL_WINDOWEVENT) {
            if (event.window.event == SDL_WINDOWEVENT_RESIZED) {
                newWindowWidth = event.window.data1;
                newWindowHeight = event.window.data2;
                windowResized = true;
            }
        }
    }
}

