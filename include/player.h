#ifndef PLAYER_H
#define PLAYER_H

#include "structs.h"

#define PLAYER_HEIGHT 100;


double deg_to_rad(double deg);

player *player_init(engine *e);

void update_player(player *p,double* vec);

void player_free(player *p);
#endif
