#ifndef WAD_DATA_H
#define WAD_DATA_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "header.h"
#include "map_renderer.h"
#include "vertex.h"
#include "linedef.h"
#include "node.h"
#include "subsector.h"
#include "segment.h"
#include "thing.h"

#define DT 1/60

struct WADData {
    header header;
    lump* directory;
    int map_index;
    vertex* vertexes;
    linedef* linedefs;
    node* nodes;
    subsector* subsectors;
    segment* segs;
    thing* things;
    int len_vertexes;
    int len_linedefs;
    int len_nodes;
    int len_subsectors;
    int len_segs;
    int len_things;
};

typedef struct WADData wad_data;

#endif