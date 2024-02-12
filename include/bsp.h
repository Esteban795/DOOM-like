#ifndef BSP_H
#define BSP_H

#include "structs.h"

#define SUBSECTOR_IDENTIFIER 0x8000

bsp *bsp_init(engine *e, player *p);

void render_bsp_node(bsp *b, int node_id);

void update_bsp(bsp *b);
#endif