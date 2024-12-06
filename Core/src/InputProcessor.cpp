//
// Created by Jacob Ross on 3/24/24.
//

#include "../include/InputProcessor.h"

#include "../../../vendor/sdl2/2.30.1/include/SDL2/SDL.h"

// ProcessInput is called in the Core MainLoop() function if the SDL Event is detected as a SDL_Key event
void InputProcessor::ProcessInput(SDL_Event& event) {
    // Extract the SDL_Keycode and cast it to your KeyCode enum
    auto keyCode = static_cast<KeyCode>(event.key.keysym.sym);
    if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP) {

        // Check and trigger key down callbacks
        if (event.type == SDL_KEYDOWN) {
            if (!event.key.repeat) {
                pressedKeys.insert(keyCode);
            }
            if (!event.key.repeat && keyDownCallbacks.find(keyCode) != keyDownCallbacks.end()) {
                for (auto& callback : keyDownCallbacks[keyCode]) {
                    callback();  // Execute each callback associated with the key code
                }
            }
        }

        // Check and trigger key up callbacks if needed
        if (event.type == SDL_KEYUP) {
            setLastPressedKey(keyCode);
            pressedKeys.erase(keyCode);
            if (keyUpCallbacks.find(keyCode) != keyUpCallbacks.end()) {
                for (auto& callback : keyUpCallbacks[keyCode]) {
                    callback();  // Execute each callback associated with the key code
                }
            }
        }
    }
}

void InputProcessor::registerKeyDownCallback(KeyCode keyCode, sol::function callback) {
    keyDownCallbacks[keyCode].push_back(callback);
}

void InputProcessor::registerKeyUpCallback(KeyCode keyCode, sol::function callback) {
    keyUpCallbacks[keyCode].push_back(callback);
}

bool InputProcessor::isKeyPressed(KeyCode keyCode) {
    return pressedKeys.find(keyCode) != pressedKeys.end();
}

const std::unordered_set<KeyCode> InputProcessor::getPressedKeys() {
    return pressedKeys;
}

void InputProcessor::setLastPressedKey(KeyCode keyCode) {
    lastPressedKey = keyCode;
}

const KeyCode InputProcessor::getLastPressedKey() {
    return lastPressedKey;
}