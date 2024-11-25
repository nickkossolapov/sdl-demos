#ifndef GAMESTATEMANAGER_H
#define GAMESTATEMANAGER_H

#include "playerManager.h"
#include "score.h"
#include "simulation.h"

enum class GameState {
    WelcomeScreen,
    Playing,
    GameOver
};

class GameStateManager {
public:
    GameStateManager(Score& score, PlayerManager& playerManager, Simulation& simulation, Player& player, AsteroidManager& asteroidManager,
                     Lives& lives)
        : score(score), playerManager(playerManager), simulation(simulation), player(player), asteroidManager(asteroidManager),
          lives(lives) {}

    void handleEvent(const SDL_Event& e);

    bool isInGame() const {
        return inGame;
    }

    void update();

private:
    Score& score;
    PlayerManager& playerManager;
    Simulation& simulation;
    Player& player;
    AsteroidManager& asteroidManager;
    Lives& lives;

    bool inGame = false;
    GameState gameState = GameState::WelcomeScreen;
};

#endif //GAMESTATEMANAGER_H
