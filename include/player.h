#ifndef PLAYER_H
#define PLAYER_H

#include <math.h>

#include "structs.h"

#define PLAYER_HEIGHT 100;
#define PLAYER_SPEED 2
#define PLAYER_ROTATION_SPEED 2

double deg_to_rad(double deg);

player *player_init(engine *e);

void update_player(player *p,bool* vec);

void player_free(player *p);
#endif