#ifndef ENGINE_H
#define ENGINE_H

#include "bsp.h"
#include "map_renderer.h"
#include "player.h"
#include "structs.h"

engine *init_engine(const char *wadPath);

void update_engine(engine *e);
#endif