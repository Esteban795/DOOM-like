#include "../include/engine.h"
#include <SDL2/SDL_render.h>

engine *init_engine(const char *wadPath,SDL_Renderer* renderer) {
  engine *e = malloc(sizeof(engine));
  e->wadPath = wadPath;
  e->running = true;
  e->renderer = renderer;
  e->wData = init_wad_data(e->wadPath);
  e->p = player_init(e);
  e->bsp = bsp_init(e, e->p);
  e->map_renderer = map_renderer_init(e);
  return e;
}

void update_engine(engine *e) {
  // update_player(e->p);
  // update_bsp(e->bsp);
  draw(e->map_renderer);
  SDL_RenderPresent(e->renderer);
}

void engine_free(engine* e){
  wad_data_free(e->wData);
  bsp_free(e->bsp);
  player_free(e->p);
  map_renderer_free(e->map_renderer);
}

