#ifndef LIVES_H
#define LIVES_H

#include "score.h"

class Lives {
public:
    explicit Lives(Score &_score, const int _lives = 3) : lives(_lives), score(_score) {
    }

    void draw() const;

    void update();

    void decrement() {
        if (lives > 0) {
            lives--;
        }
    };

private:
    int lives;
    int lastBonusLifeAt = 0;
    int maxLives = 10;
    Score &score;
};


#endif //LIVES_H
