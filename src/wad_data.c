#include "../include/wad_data.h"


wad_data init_wad_data(const char* path){
    FILE* file = fopen(path,"rb");
    if (file == NULL){
        printf("Error opening file\n");
        exit(1);
    } 
    wad_data wd;
    wd.header = read_header(file);
    wd.directory = read_directory(file,wd.header);
    wd.map_index = get_lump_index(wd.directory,"E1M1",wd.header.lump_count);
    wd.len_vertexes = wd.directory[wd.map_index + VERTEXES].lump_size / 4; // 4 = number of bytes per vertex
    wd.len_linedefs = wd.directory[wd.map_index + LINEDEFS].lump_size / 14; // 14 = number of bytes per linedef
    wd.len_nodes = wd.directory[wd.map_index + NODES].lump_size / 28; // 28 = number of bytes per node
    wd.len_subsectors = wd.directory[wd.map_index + SSECTORS].lump_size / 4; // 4 = number of bytes per subsector
    wd.len_segs = wd.directory[wd.map_index + SEGS].lump_size / 12; // 12 = number of bytes per seg
    wd.len_things = wd.directory[wd.map_index + THINGS].lump_size / 10; // 10 = number of bytes per thing
    wd.vertexes = get_vertexes_from_lump(file,wd.directory,wd.map_index + VERTEXES,4,0,wd.len_vertexes); 
    wd.linedefs = get_linedefs_from_lump(file,wd.directory,wd.map_index + LINEDEFS,14,0,wd.len_linedefs);
    wd.nodes = get_nodes_from_lump(file,wd.directory,wd.map_index + NODES,28,0,wd.len_nodes);
    wd.subsectors = get_subsectors_from_lump(file,wd.directory,wd.map_index + SSECTORS,4,0,wd.len_subsectors);
    wd.segs = get_segments_from_lump(file,wd.directory,wd.map_index + SEGS,12,0,wd.len_segs);
    wd.things = get_things_from_lump(file,wd.directory,wd.map_index + THINGS,10,0,wd.len_things);
    // int* bounds = get_map_bounds(wd.vertexes,wd.len_vertexes);
    // wd.vertexes = remap_vertexes(wd.vertexes,wd.len_vertexes,bounds);
    // free(bounds); //won't be used anymore
    return wd;
}


int main(void){
    wad_data wd = init_wad_data("maps/DOOM1.WAD");
    printf("Vertexes count : %d\n",wd.len_vertexes);
    printf("Linedefs count : %d\n",wd.len_linedefs);
    printf("Nodes count : %d\n",wd.len_nodes);
    printf("Subsectors count : %d\n",wd.len_subsectors);
    printf("Segs count : %d\n",wd.len_segs);
    printf("Things count : %d\n",wd.len_things);
    free(wd.vertexes);
    free(wd.linedefs);
    free(wd.header.wad_type);
    free(wd.nodes);
    free(wd.subsectors);
    free(wd.segs);
    free(wd.things);
    for (int i = 0; i < wd.header.lump_count;i++){
        free(wd.directory[i].lump_name);
    }
    free(wd.directory);
    return 0;
}