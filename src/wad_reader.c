#include "../include/wad_reader.h"

// handles all kind of error at SDL startup
int start_SDL(SDL_Window** window,SDL_Renderer** renderer,int width,int height, const char* title){
    if (SDL_Init(SDL_INIT_VIDEO) != 0) return 1;
    *window = SDL_CreateWindow(title,SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,width,height,SDL_WINDOW_SHOWN);
    if (*window == NULL) return 1;
    *renderer = SDL_CreateRenderer(*window,-1,SDL_RENDERER_ACCELERATED);
    if (*renderer == NULL) return 1;
    return 0;
}

void draw(engine engi){
    draw_linedefs(engi.renderer,engi.wData.linedefs,engi.wData.len_linedefs,engi.wData.vertexes);
    draw_vertexes(engi.renderer,engi.wData.vertexes,engi.wData.len_vertexes);
    SDL_RenderPresent(engi.renderer);
}

wad_data init_wad_data(const char* path){
    FILE* file = fopen(path,"rb");
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
    wd.segs = get_segs_from_lump(file,wd.directory,wd.map_index + SEGS,12,0,wd.len_segs);
    wd.things = get_things_from_lump(file,wd.directory,wd.map_index + THINGS,10,0,wd.len_things);
    int* bounds = get_map_bounds(wd.vertexes,wd.len_vertexes);
    wd.vertexes = remap_vertexes(wd.vertexes,wd.len_vertexes,bounds);
    free(bounds); //won't be used anymore
    return wd;
}


engine init_engine(SDL_Renderer* renderer,const char* path){
    engine engi = {
        .running = true,
        .wadPath = path,
        .renderer = renderer,
        .wData = init_wad_data(path)
    };
    return engi;
}

void free_engine(engine engi){
    free(engi.wData.vertexes);
    free(engi.wData.linedefs);
    free(engi.wData.header.wad_type);
    for (int i = 0; i < engi.wData.header.lump_count; i++) {
        free(engi.wData.directory[i].lump_name);
    }
    free(engi.wData.directory);
}


int main(int argc, char* argv[]){
    if (argc < 2) exit(-1);
    SDL_Window* window;
    SDL_Renderer* renderer;
    int status = start_SDL(&window,&renderer,WIDTH,HEIGHT,"Map rendering..");
    if (status == 1){
        printf("Error at SDL startup");
        exit(-1);
    }
    engine engi = init_engine(renderer,argv[1]);
    SDL_Event e;
    while (engi.running) {
        SDL_PollEvent(&e);
        draw(engi);
        switch (e.type) {
        case SDL_QUIT:
            engi.running = false;
            break;
        case SDL_KEYDOWN:
            switch (e.key.keysym.sym) {
            case SDLK_ESCAPE:
                engi.running = false;
                break;
            case SDLK_q:
                engi.running = false;
            default:
                break;
            }
        default:
            break;
        }
        SDL_Delay(DT);
    }
    free_engine(engi);
    return 0;
}