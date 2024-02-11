#include "../include/engine.h"

int main(void){
    engine* e = init_engine("maps/DOOM1.WAD");
    while (e->running){
        update_engine(e);
    }
    return 0;
}