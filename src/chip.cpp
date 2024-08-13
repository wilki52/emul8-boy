#include "chip.h"
#include <iostream>

Chip::Chip(){
    opcode = 1;
}

void Chip::interpret_program(){
    //for (;;){
        unsigned short instruction = fetch();
        decode(instruction);
        //decode();
        //execute();
    //}
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
                    std::cout << "clear screen" << std::endl;
                    break;
            }

            break;

        case 1:
            std::cout << "jump" << std::endl;
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