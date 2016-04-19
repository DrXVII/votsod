comp = g++
compOpt = -c -Wall -std=c++11 -I $(hDir)
libs = -lncurses
obj = main.o Char.o Char_Human.o Map.o Tile_Empty.o Tile.o Tile_Wall.o Viewport.o
binDir = bin/Debug/
src = main.cpp src/Char.cpp src/Char_Human.cpp src/Map.cpp src/Tile_Empty.cpp src/Tile.cpp src/Tile_Wall.cpp src/Viewport.cpp
hDir = include

all: votsod

votsod: objects
	$(comp) $(obj) -o $(binDir)votsod $(libs)

objects: $(src)
	$(comp) $(compOpt) $(src) $(libs)
