#include "text.h"

#include <vector>
#include <array>
#include <iostream>
#include <optional>
#include <string>

#include "../globals.h"
#include "../config/colors.h"

const std::array<std::vector<SDL_FPoint>, 26> vectorisedLetters = {
    {
        /*A*/ {{0, 3}, {0, 1}, {1, 0}, {2, 1}, {2, 2}, {0, 2}, {2, 2}, {2, 3}},
        /*B*/ {{0, 1.5}, {0, 3}, {1.5, 3}, {2, 2.5}, {2, 2}, {1.5, 1.5}, {0, 1.5}, {0, 0}, {1.5, 0}, {2, 0.5}, {2, 1}, {1.5, 1.5}},
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

const std::array<std::vector<SDL_FPoint>, 10> vectorisedNumbers = {
    {
        /*0*/ {{0, 0}, {2, 0}, {2, 3}, {0, 3}, {0, 0}},
        /*1*/ {{{2, 0}, {2, 3}}},
        /*2*/ {{0, 0}, {2, 0}, {2, 1.5}, {0, 1.5}, {0, 3}, {2, 3}},
        /*3*/ {{0, 0}, {2, 0}, {2, 1.5}, {0, 1.5}, {2, 1.5}, {2, 3}, {0, 3}},
        /*4*/ {{0, 0}, {0, 1.5}, {2, 1.5}, {2, 0}, {2, 3}},
        /*5*/ {{2, 0}, {0, 0}, {0, 1.5}, {2, 1.5}, {2, 3}, {0, 3}},
        /*6*/ {{2, 0}, {0, 0}, {0, 3}, {2, 3}, {2, 1.5}, {0, 1.5}},
        /*7*/ {{0, 0}, {2, 0}, {2, 3}},
        /*8*/ {{0, 1.5}, {0, 0}, {2, 0}, {2, 3}, {0, 3}, {0, 1.5}, {2, 1.5}},
        /*9*/ {{2, 1.5}, {0, 1.5}, {0, 0}, {2, 0}, {2, 3}}
    }
};

std::optional<std::vector<SDL_FPoint>> getLinesForChar(char c)
{
    if (c >= 'A' && c <= 'Z')
    {
        return vectorisedLetters[c - 'A'];
    }

    if (c >= 'a' && c <= 'z')
    {
        return vectorisedLetters[c - 'a'];
    }

    if (c >= '0' && c <= '9')
    {
        return vectorisedNumbers[c - '0'];
    }

    return {};
}

void Text::drawString(const std::string& text, float x, float y, float scale, float padding)
{
    auto [r, g, b, a] = Colours::white;
    SDL_SetRenderDrawColor(gRenderer, r, g, b, a);

    for (int i = 0; i < text.length(); i++)
    {
        auto lines = getLinesForChar(text[i]);

        if (!lines)
        {
            continue;
        }

        float xInit = x + (scale + padding) * static_cast<float>(i) * 2;

        for (int j = 0; j < lines->size() - 1; j++)
        {
            float x0 = xInit + (*lines)[j].x * scale;
            float y0 = y + (*lines)[j].y * scale;
            float x1 = xInit + (*lines)[j + 1].x * scale;
            float y1 = y + (*lines)[j + 1].y * scale;
            SDL_RenderDrawLineF(gRenderer, x0, y0, x1, y1);
        }
    }
}

void Text::drawRightAlignedNumber(const int number, const float rightX, const float y, float scale, float padding)
{
    auto [r, g, b, a] = Colours::white;
    SDL_SetRenderDrawColor(gRenderer, r, g, b, a);

    std::string str = std::to_string(number);

    float xOffset = (scale + padding) * static_cast<float>(str.length()) * 2 - padding;

    drawString(str, rightX - xOffset, y, scale, padding);
}
