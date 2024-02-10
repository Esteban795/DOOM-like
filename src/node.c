#include "../include/node.h"

node read_node(FILE* f, int offset) {
    node n;
    n.x_partition = read_i16(f, offset);
    n.y_partition = read_i16(f, offset + 2);
    n.dx_partition = read_i16(f, offset + 4);
    n.dy_partition = read_i16(f, offset + 6);
    n.left_bbox.top = read_i16(f, offset + 8);
    n.left_bbox.bottom = read_i16(f, offset + 10);
    n.left_bbox.left = read_i16(f, offset + 12);
    n.left_bbox.right = read_i16(f, offset + 14);
    n.right_bbox.top = read_i16(f, offset + 16);
    n.right_bbox.bottom = read_i16(f, offset + 18);
    n.right_bbox.left = read_i16(f, offset + 20);
    n.right_bbox.right = read_i16(f, offset + 22);
    n.right_child_id = read_i16(f, offset + 24);
    n.left_child_id = read_i16(f, offset + 26);
    return n;
}

node* get_nodes_from_lump(FILE* f,lump* directory,int lump_index, int num_bytes,int header_length,int len_nodes){
    int offset = 0;
    lump lump_info = directory[lump_index];
    node* nodes = malloc(sizeof(node) * len_nodes);
    for (int i = 0; i < len_nodes;i++){
        offset = lump_info.lump_offset + i * num_bytes + header_length;
        nodes[i] = read_node(f,offset);
    }
    return nodes;
}
