#include <SDL2/SDL.h>
#include "chip.h"
#include "window.h"
#include <iostream>

int main(){
    std::cout << "Helo World" << std::endl;
    Chip eight;
    //std::cout << "blue";

    //eight.load_rom("roms/Breakout.ch8");
    //eight.load_rom("roms/SpaceInvaders.ch8");
    //eight.load_rom("roms/bc_test.ch8");
    //eight.load_rom("roms/4-flags.ch8");
    eight.load_rom("roms/octojam1title.ch8");
    //eight.load_rom("roms/test_opcode.ch8");
    //eight.load_rom("roms/Brick.ch8");
    
    eight.interpret_program();
    //std::cout << 0xDABC << std::endl;
    //eight.decode(0xDABC);
    //std::cout << "yellow";
    //eight.decode(0x00E0);

    //Window window;
    //window.init();
    //window.update();
    //for (;;){
    //    window.updateRender();

    //}
    //window.update();
    //bool out2 = window.load();
    //std::cout << eight.getMemory();
    return 0;
}

