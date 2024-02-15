#include "../include/engine.h"
#include <stdbool.h>


static bool* events_handling(engine* engine){
    SDL_Event e;
    bool* vec = calloc(6,sizeof(double)); // {z,q,s,d,left,right}
    while (SDL_PollEvent(&e)){
        switch (e.type) {
          case SDL_QUIT:
              return NULL;
          case SDL_KEYDOWN: {
            if (e.key.keysym.sym == SDLK_ESCAPE) return NULL;
            if (e.key.keysym.sym == SDLK_z) vec[0] = true;
            if (e.key.keysym.sym == SDLK_q) vec[1] = true;
            if (e.key.keysym.sym == SDLK_s) vec[2] = true;
            if (e.key.keysym.sym == SDLK_d) vec[3] = true;
            if (e.key.keysym.sym == SDLK_LEFT) vec[4] = true;
            if (e.key.keysym.sym == SDLK_RIGHT) vec[5] = true;
          }
            break;
          default:
              break;
        } 
    }
    
  return vec;
}

engine *init_engine(const char *wadPath, SDL_Renderer *renderer) {
  engine *e = malloc(sizeof(engine));
  e->wadPath = wadPath;
  e->running = true;
  e->wData = init_wad_data(e->wadPath);
  e->p = player_init(e);
  e->bsp = bsp_init(e, e->p);
  e->map_renderer = map_renderer_init(e,renderer);
  e->keys = SDL_GetKeyboardState(e->numkeys);
  return e;
}

int update_engine(engine *e) {
  SDL_PumpEvents();
  bool* vec = events_handling(e);
  if (vec == NULL) {
    e->running = false;
    free(vec);
    return 1;
  }
  SDL_SetRenderDrawColor(e->map_renderer->renderer, 0, 0, 0, 255);
  SDL_RenderClear(e->map_renderer->renderer);
  
  update_player(e->p,vec);
  update_bsp(e->bsp);
  draw(e->map_renderer);
  SDL_RenderPresent(e->map_renderer->renderer);
  return 0;
}

void engine_free(engine *e) {
  wad_data_free(e->wData);
  bsp_free(e->bsp);
  player_free(e->p);
  map_renderer_free(e->map_renderer);
  free(e);
}