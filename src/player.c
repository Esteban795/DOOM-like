#include "../include/player.h"

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

void update_player(player *p,int mouse_x,const uint8_t* keyboard_state,int numkeys) {
  bool keydown_z = keyboard_state[SDL_SCANCODE_W];
  bool keydown_q = keyboard_state[SDL_SCANCODE_A];
  bool keydown_s = keyboard_state[SDL_SCANCODE_S];
  bool keydown_d = keyboard_state[SDL_SCANCODE_D];
  double speed = DT * PLAYER_SPEED;
  double rot_speed = PLAYER_ROTATION_SPEED * DT;
  double vec[2] = {0.0, 0.0};
  if (keydown_z) {
    vec[0] += speed * cos(deg_to_rad(p->angle));
    vec[1] -= speed * sin(deg_to_rad(p->angle));
  }
  if (keydown_s) {
    vec[0] -= speed * cos(deg_to_rad(p->angle));
    vec[1] += speed * sin(deg_to_rad(p->angle));
  }
  if (keydown_q) {
    vec[0] += speed * sin(deg_to_rad(p->angle));
    vec[1] += speed * cos(deg_to_rad(p->angle));
  }
  if (keydown_d) {
    vec[0] -= speed * sin(deg_to_rad(p->angle));
    vec[1] -= speed * cos(deg_to_rad(p->angle));
  }
  p->angle += rot_speed * mouse_x;
  p->angle = fmod(p->angle, 360);
  p->angle = p->angle < 0 ? 360 + p->angle : p->angle;
}

void player_free(player *p) { free(p); }