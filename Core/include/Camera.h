//
// Created by Jacob Wiley Ross on 3/30/24.
//

#ifndef BLOOM_ENGINE_CAMERA_H
#define BLOOM_ENGINE_CAMERA_H


#include "../../../vendor/sdl2/2.30.1/include/SDL2/SDL.h"
#include "Component.h"

class Camera : public Component {
public:
    Camera() {
        type = "Camera";
        viewPort.x = 0;
        viewPort.y = 0;
        viewPort.w = 32;
        viewPort.h = 32;
    }
    SDL_Rect viewPort; // Defines the part of the world the camera is looking at.
    float zoomLevel = 1.0f;
    // Add more properties as needed, such as rotation for more advanced camera systems.

    Camera(int x, int y, int width, int height) : viewPort({x, y, width, height}) {}

    // Methods to move, zoom, and rotate the camera as needed.
    void move(int deltaX, int deltaY) {
        viewPort.x += deltaX;
        viewPort.y += deltaY;
    }

    void setZoom(float zoom) {
        zoomLevel = zoom;
    }
};


#endif //BLOOM_ENGINE_CAMERA_H
