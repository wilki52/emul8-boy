SDLFLAGS = $(shell sdl2-config --libs --cflags)
SRC = main.cpp chip.cpp
#game: g++ main.cpp -o main $(SDLFLAGS) -std=c++14 -g
all: game

game: src/main.cpp
	g++ -o emul8 src/main.cpp src/chip.cpp $(SDLFLAGS)

clean: