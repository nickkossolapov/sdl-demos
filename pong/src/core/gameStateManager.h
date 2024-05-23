#ifndef PONG_GAMESTATEMANAGER_H
#define PONG_GAMESTATEMANAGER_H

#include "gameState.h"
#include "inGameState.h"

struct GameStates {
    InGameState inGameState;
};

class GameStateManager : public GameState {
public:
    GameStateManager(SDL_Renderer *renderer, TTF_Font *font);

    void handleEvent(SDL_Event &e) override;

    void update() override;

    void render(SDL_Renderer *renderer) override;

private:
    GameState *mCurrentState;
    GameStates mGameStates;
};

#endif //PONG_GAMESTATEMANAGER_H
