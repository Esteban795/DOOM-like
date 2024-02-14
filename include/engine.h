#ifndef ENGINE_H
#define ENGINE_H

#include "bsp.h"
#include "map_renderer.h"
#include "player.h"
#include "structs.h"

#define PLAYER_SPEED 2
#define PLAYER_ROTATION_SPEED 2

engine *init_engine(const char *wadPath, SDL_Renderer *renderer);

int update_engine(engine *e);

void engine_free(engine *e);
#endif