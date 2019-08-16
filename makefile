comp = g++
compOpt = -c -Wall -std=c++11 -I $(hDir)
libs = -lncurses
obj = main.o \
	Actor.o Actor_Human.o Actor_Watcher.o \
	Map.o \
	Tile.o Tile_Empty.o Tile_Wall.o \
	Viewport.o System.o \
	etools.o
binDir = bin/
hDir = include

all: $(binDir) votsod 

votsod: objects
	$(comp) $(obj) -o $(binDir)votsod $(libs)

objects: $(src)
	$(comp) $(compOpt) src/*.cpp $(libs)

$(binDir):
	mkdir -p $@

clean:
	rm -fr *.o
	rm bin/votsod
