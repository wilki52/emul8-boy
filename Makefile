SDLFLAGS = $(shell sdl2-config --libs --cflags)
#game: g++ main.cpp -o main $(SDLFLAGS) -std=c++14 -g
all: game

game: main.cpp
	g++ -o emul8 main.cpp $(SDLFLAGS)

clean: