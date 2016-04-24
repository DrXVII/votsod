comp = g++
compOpt = -c -Wall -std=c++11 -I $(hDir)
libs = -lncurses
obj = main.o \
	Char.o Char_Human.o \
	Map.o \
	Tile.o Tile_Empty.o Tile_Wall.o \
	Viewport.o
binDir = bin/
hDir = include

all: votsod

votsod: objects
	$(comp) $(obj) -o $(binDir)votsod $(libs)

objects: $(src)
	$(comp) $(compOpt) src/* $(libs)

clean:
	rm -fr *.o
