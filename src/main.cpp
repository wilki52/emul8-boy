#include <SDL2/SDL.h>
#include "chip.h"
#include "window.h"
#include <iostream>

int main(){
    std::cout << "Helo World" << std::endl;
    Chip eight;
    std::cout << "blue";
    eight.load_rom("roms/IBM Logo.ch8");
    std::cout << "yellow";
    eight.decode(0x00E0);

    //Window window;
    //window.update();
    //bool out2 = window.load();
    //std::cout << eight.getMemory();
    return 0;
}

