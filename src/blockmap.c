#include "../include/blockmap.h"
#include <stdio.h>

static blockmap_header* read_blockmap_header(FILE* f,int offset) {
    blockmap_header* bh = malloc(sizeof(blockmap_header));
    bh->x = read_i16(f, offset);
    bh->y = read_i16(f, offset + 2);
    bh->ncols = read_i16(f, offset + 4);
    bh->nrows = read_i16(f, offset + 6);
    return bh;
}

static size_t find_number_of_linedefs(FILE* f, int init_offset){
    size_t nlinedefs = 0;
    if (read_i16(f, init_offset) != BLOCK_START) return 0;
    int offset = init_offset + 2;
    while (read_i16(f, offset) != BLOCK_END) {
        offset += 2;
        nlinedefs++;
    }
    return nlinedefs;
}

static block read_block(FILE* f,int offset,linedef* linedefs) {
    block b;
    b.nlinedefs = find_number_of_linedefs(f, offset);
    //printf("ok on est passé\n");
    b.linedefs = malloc(sizeof(linedef) * b.nlinedefs);
    for (size_t i = 1; i < b.nlinedefs; i++) {
        b.linedefs[i] = linedefs[read_i16(f, offset + i * 2)];
    }
    return b;
}

blockmap* read_blockmap(FILE* f,int offset,linedef* linedefs){
    blockmap* bm = malloc(sizeof(blockmap));
    bm->header = read_blockmap_header(f, offset);
    bm->nblocks = bm->header->ncols * bm->header->nrows;
    bm->blocks = malloc(sizeof(block) * bm->nblocks);
    i16* block_offsets = malloc(sizeof(i16) * bm->nblocks);
    for (size_t i = 0; i < bm->nblocks; i++) {
        block_offsets[i] = read_i16(f, offset + 8 + i * 2);
    }
    printf("Nb blocks : %lu\n",bm->nblocks);
    for (size_t i = 0; i < bm->nblocks -1 ; i++) {
        printf("Etape %zu : Block offset : %d\n",i,block_offsets[i]);
        bm->blocks[i] = read_block(f, offset + block_offsets[i],linedefs);
    }
    return  bm;
}

blockmap* read_blockmap_from_lump(FILE* f,lump* directory,int lump_index,linedef* linedefs){
    blockmap* bm = read_blockmap(f, directory[lump_index].lump_offset,linedefs);
    return bm;
}
void blockmap_free(blockmap* bm){
    free(bm->header);
    for (size_t i = 0; i < bm->nblocks; i++) {
        free(bm->blocks[i].linedefs);
    }
    free(bm->blocks);
    free(bm);
}