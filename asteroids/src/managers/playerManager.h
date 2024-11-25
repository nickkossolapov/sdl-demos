#ifndef ASTEROIDS_PLAYERMANAGER_H
#define ASTEROIDS_PLAYERMANAGER_H

#include "../entities/player.h"
#include "score.h"
#include "lives.h"

class PlayerManager {
public:
    PlayerManager(Player& player, Lives& lives) : player(player), lives(lives) {}

    void update();

    void reset() {
        gameOver = false;
        lastSpawnedAt = 0;
    }

    bool isGameOver() const {
        return gameOver;
    };

private:
    Player& player;
    Lives& lives;
    bool gameOver = false;
    Uint32 lastSpawnedAt = 0;
};

#endif //ASTEROIDS_PLAYERMANAGER_H
