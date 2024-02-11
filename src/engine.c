#include "../include/engine.h"

engine* init_engine(const char* wadPath){
    engine* e = malloc(sizeof(engine));
    e->wadPath = wadPath;
    e->running = true;
    e->renderer = NULL;
    e->wData = init_wad_data(e->wadPath);
    e->p = player_init(e);
    e->bsp = bsp_init(e, e->p);
    e->map_renderer = map_renderer_init(e);
    return e;
}

void update_engine(engine* e){
    update_player(e->p);
    update_bsp(e->bsp);
    draw(e->map_renderer);
}
