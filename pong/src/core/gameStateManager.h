#ifndef PONG_GAMESTATEMANAGER_H
#define PONG_GAMESTATEMANAGER_H

#include <memory>
#include <unordered_map>
#include "gameState.h"
#include "inGameState.h"
#include "pausedState.h"

enum class GameStates {
    IN_GAME,
    PAUSED
};

class GameStateManager : public GameState {
public:
    GameStateManager(SDL_Renderer *renderer, TTF_Font *font);

    void handleEvent(SDL_Event &e) override;

    void update() override;

    void render(SDL_Renderer *renderer) override;

private:
    GameStates mCurrentState;
    std::unordered_map<GameStates, std::unique_ptr<GameState>> mGameStates;
};

#endif //PONG_GAMESTATEMANAGER_H
