#ifndef ENGINE_H
#define ENGINE_H

#include "structs.h"
#include "map_renderer.h"

engine* init_engine(const char* wadPath);

void update_engine(engine* e);
#endif