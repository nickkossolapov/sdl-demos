#include <string>
#include "scoreUi.h"
#include "colors.h"
#include "constants.h"

ScoreUi::ScoreUi(TTF_Font *font, SDL_Renderer *renderer) : mP1Score(TextTexture(font)), mP2Score(TextTexture(font)) {
    mScore = Score{1, 1};

    mRenderer = renderer;
}

void ScoreUi::setScore(Score score) {
    if (score.player1 != mScore.player1 || score.player2 != mScore.player2) {
        mScore = score;
        setScoreText();
    }
}

void ScoreUi::reset() {
    mScore = {1, 1};
    setScoreText();
}

void ScoreUi::free() {
    mP1Score.free();
    mP2Score.free();
}

void ScoreUi::render(SDL_Renderer *renderer) {
    int p1TextWidth = mP1Score.getWidth();
    mP1Score.render(renderer, {SCREEN_WIDTH / 4 - p1TextWidth / 2, PADDING});

    int p2TextWidth = mP2Score.getWidth();
    mP2Score.render(renderer, {3 * SCREEN_WIDTH / 4 - p2TextWidth / 2, PADDING});
}

void ScoreUi::setScoreText() {
    mP1Score.setText(mRenderer, const_cast<char *>(std::to_string(mScore.player1).c_str()), OFF_WHITE, OFF_BLACK);
    mP2Score.setText(mRenderer, const_cast<char *>(std::to_string(mScore.player2).c_str()), OFF_WHITE, OFF_BLACK);
}
