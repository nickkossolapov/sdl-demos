#ifndef SCOREUI_H
#define SCOREUI_H

#include <SDL.h>
#include "../game/score.h"
#include "../utils/textTexture.h"

class ScoreUi {
public:
    ScoreUi(TTF_Font *font, SDL_Renderer *renderer);

    void setScore(Score score);

    void reset();

    void free();

    void render(SDL_Renderer *renderer);

private:
    Score mScore{};
    TextTexture mP1Score;
    TextTexture mP2Score;
    SDL_Renderer *mRenderer;

    void setScoreText();
};

#endif //SCOREUI_H
