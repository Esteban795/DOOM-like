#include "../include/player.h"

player *player_init(engine *e) {
  player *p = malloc(sizeof(player));
  p->engine = e;
  p->thing = e->wData->things[0];
  p->x = p->thing.x;
  p->y = p->thing.y;
  p->angle = p->thing.angle;
  return p;
}

void update_player(player *p) {
  p->x += 0;
  p->y += 0;
}

void player_free(player *p) { free(p); }