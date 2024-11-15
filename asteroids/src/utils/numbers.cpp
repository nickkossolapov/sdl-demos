#include "numbers.h"

#include <vector>
#include <array>
#include <string>

#include "../globals.h"
#include "../config/colors.h"


const std::array<std::vector<SDL_Point>, 10> vectorisedNumbers = {
    {
        {{0, 0}, {1, 0}, {1, 2}, {0, 2}, {0, 0}}, //0
        {{{1, 0}, {1, 2}}}, //1
        {{0, 0}, {1, 0}, {1, 1}, {0, 1}, {0, 2}, {1, 2}}, //2
        {{0, 0}, {1, 0}, {1, 1}, {0, 1}, {1, 1}, {1, 2}, {0, 2}}, //3
        {{0, 0}, {0, 1}, {1, 1}, {1, 0}, {1, 2}}, //4
        {{1, 0}, {0, 0}, {0, 1}, {1, 1}, {1, 2}, {0, 2}}, //5
        {{1, 0}, {0, 0}, {0, 2}, {1, 2}, {1, 1}, {0, 1}}, //6
        {{0, 0}, {1, 0}, {1, 2}}, //7
        {{0, 1}, {0, 0}, {1, 0}, {1, 2}, {0, 2}, {0, 1}, {1, 1}}, //8
        {{1, 1}, {0, 1}, {0, 0}, {1, 0}, {1, 2}}
    } //9
};

void Numbers::drawNumber(const int number, const int x, const int y) {
    auto [r, g, b, a] = Colours::white;
    SDL_SetRenderDrawColor(gRenderer, r, g, b, a);

    std::string str = std::to_string(number);
    std::vector<int> digits;

    for (auto i = str.length() - 1; str.length() > i; i--) {
        digits.push_back(str[i] - '0');
    }

    static int scale = 20;
    static int padding = 10;

    for (int i = 0; i < digits.size(); i++) {
        int xInit = x - (scale + padding) * i; // todo: don't use full width for 1

        auto &lines = vectorisedNumbers[digits[i]];

        for (int j = 0; j < lines.size() - 1; j++) {
            int x0 = xInit + lines[j].x * scale;
            int y0 = y + lines[j].y * scale;
            int x1 = xInit + lines[j + 1].x * scale;
            int y1 = y + lines[j + 1].y * scale;
            SDL_RenderDrawLine(gRenderer, x0, y0, x1, y1);
        }
    }
}
