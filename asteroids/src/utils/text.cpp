#include "text.h"

#include <algorithm>
#include <vector>
#include <array>
#include <iostream>
#include <string>

#include "../globals.h"
#include "../config/colors.h"

const std::array<std::vector<SDL_FPoint>, 26> vectorisedLetters = {
    {
        /*A*/ {{0, 3}, {0, 1}, {1, 0}, {2, 1}, {2, 2}, {0, 2}, {2, 2}, {2, 3}},
        /*B*/
        {
            {0, 1.5}, {0, 3}, {1.5, 3}, {2, 2.5}, {2, 2}, {1.5, 1.5}, {0, 1.5}, {0, 0}, {1.5, 0}, {2, 0.5}, {2, 1},
            {1.5, 1.5}
        },
        /*C*/ {{2, 3}, {0, 3}, {0, 0}, {2, 0}},
        /*D*/ {{0, 0}, {0, 3}, {1.5, 3}, {2, 2.5}, {2, 0.5}, {1.5, 0}, {0, 0}},
        /*E*/ {{2, 0}, {0, 0}, {0, 1.5}, {1.7, 1.5}, {0, 1.5}, {0, 3}, {2, 3}},
        /*F*/ {{2, 0}, {0, 0}, {0, 1.5}, {1.7, 1.5}, {0, 1.5}, {0, 3}},
        /*G*/ {{2, 0}, {0, 0}, {0, 3}, {2, 3}, {2, 1.5}, {1, 1.5}},
        /*H*/ {{0, 0}, {0, 3}, {0, 1.5}, {2, 1.5}, {2, 0}, {2, 3}},
        /*I*/ {{0, 0}, {2, 0}, {1, 0}, {1, 3}, {0, 3}, {2, 3}},
        /*J*/ {{2, 0}, {2, 3}, {0, 3}, {0, 2}},
        /*K*/ {{0, 0}, {0, 3}, {0, 1.5}, {2, 0}, {0, 1.5}, {2, 3}},
        /*L*/ {{0, 0}, {0, 3}, {2, 3}},
        /*M*/ {{0, 3}, {0, 0}, {1, 1.5}, {2, 0}, {2, 3}},
        /*N*/ {{0, 3}, {0, 0}, {2, 3}, {2, 0}},
        /*O*/ {{2, 3}, {0, 3}, {0, 0}, {2, 0}, {2, 3}},
        /*P*/ {{0, 3}, {0, 0}, {2, 0}, {2, 1.5}, {0, 1.5}},
        /*Q*/ {{1, 3}, {0, 3}, {0, 0}, {2, 0}, {2, 2}, {1.5, 2.5}, {1, 2}, {1.5, 2.5}, {2, 3}, {1.5, 2.5}, {1, 3}},
        /*R*/ {{0, 3}, {0, 0}, {2, 0}, {2, 1.5}, {0, 1.5}, {0.5, 1.5}, {2, 3}},
        /*S*/ {{2, 0}, {0, 0}, {0, 1.5}, {2, 1.5}, {2, 3}, {0, 3}},
        /*I*/ {{0, 0}, {2, 0}, {1, 0}, {1, 3}},
        /*U*/ {{0, 0}, {0, 3}, {2, 3}, {2, 0}},
        /*V*/ {{0, 0}, {1, 3}, {2, 0}},
        /*W*/ {{0, 0}, {0, 3}, {1, 2}, {2, 3}, {2, 0}},
        /*X*/ {{0, 0}, {2, 3}, {1, 1.5}, {2, 0}, {0, 3}},
        /*Y*/ {{0, 0}, {1, 1.5}, {2, 0}, {1, 1.5}, {1, 3}},
        /*Z*/ {{0, 0}, {2, 0}, {0, 3}, {2, 3}},
    }
};


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

void Text::drawString(const std::string &text, float x, float y) {
    auto [r, g, b, a] = Colours::white;
    SDL_SetRenderDrawColor(gRenderer, r, g, b, a);

    std::string indexedString = text;
    std::transform(indexedString.begin(), indexedString.end(), indexedString.begin(), ::tolower);

    static float scale = 10;
    static float padding = 5;

    for (int i = 0; i < text.length(); i++) {
        float xInit = x + (scale + padding) * static_cast<float>(i) * 2;
        int charIndex = (indexedString[i] - 'a') % 26;

        auto &lines = vectorisedLetters[charIndex];

        if (lines.empty()) {
            return;
        }

        for (int j = 0; j < lines.size() - 1; j++) {
            float x0 = xInit + lines[j].x * scale;
            float y0 = y + lines[j].y * scale;
            float x1 = xInit + lines[j + 1].x * scale;
            float y1 = y + lines[j + 1].y * scale;
            SDL_RenderDrawLineF(gRenderer, x0, y0, x1, y1);
        }
    }
}


void Text::drawNumber(const int number, const int x, const int y) {
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
