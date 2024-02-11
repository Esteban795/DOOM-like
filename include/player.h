#ifndef PLAYER_H
#define PLAYER_H

#include "structs.h"

#define PLAYER_HEIGHT 100;

player* player_init(engine* e);

void update_player(player* p);
#endif
