#include "../include/engine.h"

// handles all kind of error at SDL startup
int start_SDL(SDL_Window **window, SDL_Renderer **renderer, int width,
              int height, const char *title) {
  if (SDL_Init(SDL_INIT_VIDEO) != 0)
    return 1;
  *window =
      SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                       width, height, SDL_WINDOW_SHOWN);
  if (*window == NULL)
    return 1;
  *renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED);
  if (*renderer == NULL)
    return 1;
  return 0;
}

int main(void) {
  SDL_Window *window;
  SDL_Renderer *renderer;
  int status = start_SDL(&window, &renderer, WIDTH, HEIGHT, "Map rendering..");
  if (status == 1) {
    printf("Error at SDL startup");
    exit(-1);
  }
  engine *e = init_engine("maps/DOOM1.WAD", renderer);
  SDL_Event ev;
  while (e->running) {
    SDL_PollEvent(&ev);
    switch (ev.type) {
      case SDL_QUIT:
        e->running = false;
        break;
      case SDL_KEYDOWN:
        switch (ev.key.keysym.sym) {
        case SDLK_ESCAPE:
          e->running = false;
          break;
        case SDLK_q:
          e->running = false;
        default:
          break;
        }
      default:
        break;
    }
    update_engine(e);
    SDL_Delay(DT);
  }
  engine_free(e);
  return 0;
}