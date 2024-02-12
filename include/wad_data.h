#ifndef WAD_DATA_H
#define WAD_DATA_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "header.h"
#include "linedef.h"
#include "node.h"
#include "segment.h"
#include "subsector.h"
#include "thing.h"
#include "vertex.h"

#define DT 1 / 60

struct WADData {
  header header;
  lump *directory;
  int map_index;
  vertex *vertexes;
  linedef *linedefs;
  node *nodes;
  subsector *subsectors;
  segment *segments;
  thing *things;
  int len_vertexes;
  int len_linedefs;
  int len_nodes;
  int len_subsectors;
  int len_segments;
  int len_things;
};

typedef struct WADData wad_data;

wad_data init_wad_data(const char *path);

#endif