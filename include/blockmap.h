#ifndef BLOCKMAP_H
#define BLOCKMAP_H

#define BLOCKMAP_START 0x0000
#define BLOCKMAP_END 0xFFFF

#include "byte_reader.h"
#include "linedef.h"

#include <stdio.h>
#include <stdlib.h>

struct Block {
    linedef* linedefs;
    size_t nlinedefs;
};

typedef struct Block block;

struct BlockmapHeader {
    i16 x;
    i16 y;
    i16 ncols;
    i16 nrows;
};

typedef struct BlockmapHeader blockmap_header;

struct Blockmap {
    blockmap_header* header;
    block* blocks;
    size_t nblocks; 
};

typedef struct Blockmap blockmap;

#endif