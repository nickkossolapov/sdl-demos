#include "score.h"

#include "../utils/text.h"

void Score::draw() const {
    Text::drawRightAlignedNumber(score, 210, 30);
}

void Score::increment(const int scale) {
    switch (scale) {
        case 1:
            score += 100;
            break;
        case 2:
            score += 50;
            break;
        case 3:
            score += 20;
            break;
        default:
            break;
    }
}
