#include <iostream>
#include "controller.h"

float getAxisTilt(Sint16 value) {
    static int deadZone = 3500;
    if (abs(value) < deadZone) {
        return 0;
    }

    return static_cast<float>(value) / static_cast<float>(SDL_MAX_SINT16);
}