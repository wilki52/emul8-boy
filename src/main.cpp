#include <SDL2/SDL.h>
#include "chip.h"
#include <iostream>

int main(){
    std::cout << "Hello World" << std::endl;
    Chip eight;
    eight.decode(0x00E0);
    //std::cout << eight.getMemory();
    return 0;
}

