SRCDIR = src
HEADDIR = include
LIBDIR = ./src

FLAGS = -lSDL2
DEBUGFLAGS = -W -Wall -Wextra -Wvla -fsanitize=address -g -O3
DEPENDENCIES = $(SRCDIR)/bsp.c $(SRCDIR)/byte_reader.c $(SRCDIR)/engine.c $(SRCDIR)/header.c $(SRCDIR)/linedef.c $(SRCDIR)/lump.c $(SRCDIR)/map_renderer.c $(SRCDIR)/node.c $(SRCDIR)/player.c $(SRCDIR)/segment.c $(SRCDIR)/subsector.c $(SRCDIR)/thing.c $(SRCDIR)/vertex.c $(SRCDIR)/wad_data.c

build:
	gcc $(SRCDIR)/main.c -o ./bin/doomlike $(DEPENDENCIES) $(FLAGS) $(DEBUGFLAGS)

run:
	./bin/doomlike

clean:
	rm ./bin/doomlike

all:
	make build
	make run