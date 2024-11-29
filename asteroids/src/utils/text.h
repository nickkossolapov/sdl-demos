#ifndef ASTEROIDS_NUMBERS_H
#define ASTEROIDS_NUMBERS_H

#include <string>


namespace Text {
    void drawRightAlignedNumber(int number, float rightX, float y, float scale = 10, float padding = 3);

    void drawString(const std::string &text, float x, float y, float scale = 10, float padding = 3);

    std::tuple<float, float> getStringWidthAndHeight(const std::string &text, float scale = 10, float padding = 3);
}

#endif //ASTEROIDS_NUMBERS_H
