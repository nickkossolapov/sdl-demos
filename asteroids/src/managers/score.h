#ifndef ASTEROIDS_SCORE_H
#define ASTEROIDS_SCORE_H

class Score {
public:
    void draw() const;

    void increment(int scale);

    int getScore() const {
        return score;
    };

private:
    int score = 0;
};

#endif //ASTEROIDS_SCORE_H
