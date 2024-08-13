#include "chip.h"
#include "window.h"
#include <iostream>
#include <fstream>
#include <SDL2/SDL.h>
Chip::Chip(){
    pixels[0]=1;
    pixels[3]=1;
    //pixels[64]=1;
   display.open();
}

void Chip::interpret_program(){
    SDL_Event e;

    bool running = true;
    while (running){

        while (SDL_PollEvent(&e)!=0){

            if (e.type==SDL_QUIT){
                running = false;
            }
        }
        
        //display.();
        //unsigned short instruction = fetch();
        //decode(instruction);
        //decode();
        //execute();
        unsigned short instruction = fetch();
        //decode(instruction);
        //decode(0x0000);
        display.updateRender(pixels);


    }
}

unsigned short Chip::fetch(){
    //fetch instruction from memory, using the PC a;s the index.
    //ex: memory[PC] = 0xA2
    //memory[PC+1] = 0xF0
    unsigned char instruction_a = memory[PC];
    unsigned char instruction_b = memory[PC+1];
    instruction_a = 0xA2;
    instruction_b = 0xF0;
    PC= PC+2;
    unsigned short instruction = (instruction_a << 8 | instruction_b);
    return instruction;

    
}

int Chip::decode(unsigned short instruction){
    //instruction = 0xA2F0;
    //char first = instruction & 0xff;
    unsigned short lsb = instruction & 0xF;
    unsigned short third = (instruction>>4) & 0xF;
    unsigned short second = (instruction>>8) & 0xF;
    unsigned short msb = (instruction>>12) & 0xF;
    std::cout << msb << std::endl;
    std::cout << std::hex << second << std::endl;
    std::cout << std::hex << third << std::endl;
    std::cout << std::hex << lsb << std::endl;
    switch (msb){
        case 0:
            switch (second){
                case 0: //00E0 
                    //update window?
                    std::cout << "clear screen" << std::endl;
                    std::fill(std::begin(pixels), std::end(pixels), 0);
                    

                    break;
            }

            break;

        case 1:
            std::cout << "jump" << std::endl;
            //return 
            
            PC = ((second << 4) | (third <<4) | lsb);
            std::cout << std::hex << PC << std::endl;
            break;

        case 2:
            break;

        case 3:
            break;

        case 4:
            break;

        case 5:
            break;

        case 6:
            std::cout << "set register VX" << std::endl;
            break;

        case 7:
            std::cout << "add value to register VX" << std::endl;
            break;

        case 8:
            break;

        case 9:
            break;
        case 10: //A
            std::cout << "set index register I" << std::endl;
            break;
        case 11: //B
            break;
        case 12: //C
            break;
        case 13: //D
            std::cout << "display/draw" << std::endl;
            break;
        case 14: //E
            break;
        case 15: //F
            break;
        
    }


}
int Chip::execute(){

}

//how tf do i do this
bool Chip::load_rom(const char path[]){
    //iterate through the ch8 file, starting from memory[I], I=0x200
    std::ifstream reader(path);

    if (!reader){
        std::cout << "mmm wrong song" << std::endl;
        return false;
    }
    std::cout << "working.." << std::endl;
    unsigned char instruction;
    I=0x200;
    PC =0x200;
    while (reader >> instruction){
        memory[I] = instruction;
        std::cout << instruction << std::endl;
        I=I+1;
    }
    return true;
}