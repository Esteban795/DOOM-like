#include "../include/bsp.h"

bsp *bsp_init(engine *e, player *p) {
  bsp *b = malloc(sizeof(bsp));
  b->engine = e;
  b->player = p;
  b->nodes = e->wData->nodes;
  b->subsectors = e->wData->subsectors;
  b->segments = e->wData->segments;
  b->root_node_id = e->wData->len_nodes - 1;
  return b;
}

static bool is_on_back_side(bsp *b, node n) {
  i16 dx = b->player->x - n.x_partition;
  i16 dy = b->player->y - n.y_partition;
  return dx * n.x_partition + dy * n.y_partition <= 0;
}

void render_bsp_node(bsp *b, int node_id) {
  if (node_id >= SUBSECTOR_IDENTIFIER) {
    int subsector_id = node_id - SUBSECTOR_IDENTIFIER;
  }
  node n = b->nodes[node_id];
  bool is_back_side = is_on_back_side(b, n);
  if (is_back_side) {
    render_bsp_node(b, n.back_child_id);
    render_bsp_node(b, n.front_child_id);
  } else {
    render_bsp_node(b, n.front_child_id);
    render_bsp_node(b, n.back_child_id);
  }
}

void update_bsp(bsp *b) { b->root_node_id -= 1; }

void bsp_free(bsp *b) { free(b); }