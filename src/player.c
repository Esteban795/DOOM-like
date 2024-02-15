#include "../include/player.h"
#include <SDL2/SDL_timer.h>
#include <math.h>
#include <stdio.h>

#define M_PI 3.14159265358979323846
#define HALF_M_PI 1.57079632679489661923

double deg_to_rad(double deg) { return deg * (M_PI / 180); }

player *player_init(engine *e) {
  player *p = malloc(sizeof(player));
  p->engine = e;
  p->thing = e->wData->things[0];
  p->x = (double)p->thing.x;
  p->y = (double)p->thing.y;
  p->angle = (double)0.0;
  return p;
}

void update_player(player *p,bool* vec) {
  bool keydown_z = vec[0];
  bool keydown_q = vec[1];
  bool keydown_s = vec[2];
  bool keydown_d = vec[3];
  bool keydown_left = vec[4];
  bool keydown_right = vec[5];
  double speed = DT * PLAYER_SPEED;
  double rot_speed = PLAYER_ROTATION_SPEED * DT;
  if (keydown_z) {
    p->x += speed * sin(deg_to_rad(p->angle + 90.0));
    p->y += speed * cos(deg_to_rad(p->angle + 90.0));
  }
  if (keydown_s) {
    p->x += speed * sin(deg_to_rad(p->angle - 90.0));
    p->y += speed * cos(deg_to_rad(p->angle - 90.0));
  }
  if (keydown_q) {
    p->x += speed * sin(deg_to_rad(p->angle));
    p->y += speed * cos(deg_to_rad(p->angle));
  }
  if (keydown_d) {
    p->x += speed * sin(deg_to_rad(p->angle + 180.0));
    p->y += speed * cos(deg_to_rad(p->angle + 180.0));
  }
  if (keydown_left) {
    p->angle -= rot_speed;
  }
  if (keydown_right) {
    p->angle += rot_speed;
  }
  p->angle = fmod(p->angle, 360);
  p->angle = p->angle < 0 ? 360 + p->angle : p->angle;
  free(vec);
}

void player_free(player *p) { free(p); }