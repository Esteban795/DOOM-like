#ifndef THING_H 
#define THING_H

#include "byte_reader.h"
#include "lump.h"
// https://doomwiki.org/wiki/Thing

struct Thing {
    i16 x;
    i16 y;
    i16 angle;
    i16 type;
    i16 flags;
};

typedef struct Thing thing;

#endif