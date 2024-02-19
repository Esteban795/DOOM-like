#include "../include/blockmap.h"
#include <stdlib.h>

blockmap_header* read_blockmap_header(FILE* f,int offset) {
    blockmap_header* bh = malloc(sizeof(blockmap_header));
    bh->x = read_i16(f, offset);
    bh->y = read_i16(f, offset + 2);
    bh->ncols = read_i16(f, offset + 4);
    bh->nrows = read_i16(f, offset + 6);
    return bh;
}

blockmap* read_blockmap(FILE* f,int offset){
    blockmap* bm = malloc(sizeof(blockmap));
    bm->header = read_blockmap_header(f, offset);
    bm->nblocks = bm->header->ncols * bm->header->nrows;
    bm->blocks = malloc(sizeof(block) * bm->nblocks);
}