#ifndef ASTEROIDS_SCORE_H
#define ASTEROIDS_SCORE_H

class Score {
public:
    int score = 0;

    void draw() const;

    void increment(int scale);
};

#endif //ASTEROIDS_SCORE_H
