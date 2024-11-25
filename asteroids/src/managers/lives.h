#ifndef LIVES_H
#define LIVES_H

#include "score.h"

class Lives {
public:
    explicit Lives(Score& score) : score(score) {}

    void draw() const;

    void update();

    void decrement() {
        if (lives > 0) {
            lives--;
        }
    };

    int getLives() const {
        return lives;
    }

    void reset() {
        lives = defaultLives;
        lastBonusLifeAt = 0;
    }

private:
    static constexpr int defaultLives = 3;
    int lives = defaultLives;
    int lastBonusLifeAt = 0;
    int maxLives = 10;
    Score& score;
};


#endif //LIVES_H
