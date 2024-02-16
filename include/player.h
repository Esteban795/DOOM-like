#ifndef PLAYER_H
#define PLAYER_H

#include <math.h>

#include "structs.h"

#define PLAYER_HEIGHT 100;
#define PLAYER_SPEED .12
#define PLAYER_ROTATION_SPEED .03
#define MOUSE_SENSITIVY 0.03

double deg_to_rad(double deg);

player *player_init(engine *e);

void update_player(player *p,int mouse_x,const uint8_t* keyboard_state,int numkeys);

void player_free(player *p);
#endif