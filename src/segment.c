#include "../include/segment.h"

segment read_segment(FILE *f, int offset) {
  segment s;
  s.start_vertex_id = read_i16(f, offset);
  s.end_vertex_id = read_i16(f, offset + 2);
  s.angle = read_i16(f, offset + 4);
  s.linedef_id = read_i16(f, offset + 6);
  s.direction = read_i16(f, offset + 8);
  s.offset = read_i16(f, offset + 10);
  return s;
}

segment *get_segments_from_lump(FILE *f, lump *directory, int lump_index,
                                int num_bytes, int header_length,
                                int len_segments) {
  int offset = 0;
  lump lump_info = directory[lump_index];
  segment *segments = malloc(sizeof(segment) * len_segments);
  for (int i = 0; i < len_segments; i++) {
    offset = lump_info.lump_offset + i * num_bytes + header_length;
    segments[i] = read_segment(f, offset);
  }
  return segments;
}