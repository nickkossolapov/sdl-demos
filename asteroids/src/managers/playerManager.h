#ifndef ASTEROIDS_PLAYERMANAGER_H
#define ASTEROIDS_PLAYERMANAGER_H

#include "../entities/player.h"
#include "score.h"
#include "lives.h"

class PlayerManager {
public:
    PlayerManager(Player &player, Lives &lives) : player(player), lives(lives) {};

    void update();

private:
    Player &player;
    Lives &lives;
};

#endif //ASTEROIDS_PLAYERMANAGER_H
