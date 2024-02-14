#include "../include/player.h"
#include <SDL2/SDL_timer.h>
#include <stdio.h>


double deg_to_rad(double deg) { return deg * (M_PI / 180); }

player *player_init(engine *e) {
  player *p = malloc(sizeof(player));
  p->engine = e;
  p->thing = e->wData->things[0];
  p->x = (double)p->thing.x;
  p->y = (double)p->thing.y;
  p->angle = (double)p->thing.angle;
  return p;
}

void update_player(player *p, double *vec) {
  p->angle += vec[2];
  p->x += vec[0] * cos(deg_to_rad(p->angle)) - vec[1] * sin(deg_to_rad(p->angle));
  p->y += vec[0] * sin(deg_to_rad(p->angle)) + vec[1] * cos(deg_to_rad(p->angle));
  printf("x: %f, y: %f, angle: %f\n", p->x, p->y, p->angle);
  // SDL_Delay(250);
}

void player_free(player *p) { free(p); }