#ifndef BSP_H
#define BSP_H

#include "geometry.h"
#include "settings.h"
#include "map_renderer.h"
#include "structs.h"
#include "vec2.h"
#include "player.h"

bsp *bsp_init(engine *e, player *p);

void render_bsp_node(bsp *b, size_t node_id);

void update_bsp(bsp *b);

void bsp_free(bsp *b);
#endif