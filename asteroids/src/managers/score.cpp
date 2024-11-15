#include "score.h"

#include "../utils/numbers.h"

void Score::draw() const {
    Numbers::drawNumber(score, 200, 20);
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

