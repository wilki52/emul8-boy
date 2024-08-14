#include "chip.h"
#include "window.h"
#include <iostream>
#include <fstream>
#include <SDL2/SDL.h>
#include <ios>
Chip::Chip(){
    //pixels[0]=1;
    //pixels[3]=1;
    //pixels[64]=1;
    V[0x0], V[0x1],V[0x2],V[0x3],V[0x4],V[0x5],V[0x6],V[0x7],V[0x8],V[0x9],V[0xA],V[0xB],V[0xC],V[0xD],V[0xE],V[0xF] = 0;

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
        unsigned short instruction = fetch();
        decode(instruction);

        display.updateRender(pixels);


    }
}

unsigned short Chip::fetch(){
    //fetch instruction from memory, using the PC a;s the index.
    //ex: memory[PC] = 0xA2
    //memory[PC+1] = 0xF0
    unsigned char instruction_a = memory[PC];
    unsigned char instruction_b = memory[PC+1];
    
    
    //instruction_a = 0xA2;
    //instruction_b = 0xF0;
    
    unsigned short instruction = (instruction_a << 8 | instruction_b);
    std::cout << PC << ": " << std::hex << instruction << std::endl;
    PC= PC+2;
    return instruction;

    
}

int Chip::decode(unsigned short instruction){
    //instruction = 0xA2F0;
    //char first = instruction & 0xff;
    unsigned short lsb = instruction & 0xF;
    unsigned short third = (instruction>>4) & 0xF;
    unsigned short second = (instruction>>8) & 0xF;
    unsigned short msb = (instruction>>12) & 0xF;
    //std::cout << std::hex << instruction << std::endl;
    //std::cout << std::hex << msb << std::endl;
    //std::cout << std::hex << second << std::endl;
    //std::cout << std::hex << third << std::endl;
    //std::cout << std::hex << lsb << std::endl;
    unsigned short value = ((third << 4) | lsb);
    switch (msb){
        case 0:
            switch (second){
                case 0: //00E0 
                    //update window?
                    
                    switch (lsb){

                        case 0:
                            std::cout << "clear screen" << std::endl;
                            std::fill(std::begin(pixels), std::end(pixels), 0);
                            break;
                        default:
                            std::cout << "return from subroutine" << std::endl;
                        
                    }

                    
                    

                break;
            }

            break;

        case 1:
            break;
            std::cout << "jump" << std::endl;
            //return 
            PC = ((second << 8) | (third <<4) | lsb);
            PC = PC;
            std::cout << std::hex << PC << std::endl;
            break;

        case 2:
            std::cout << "call subroutine at NNN" << std::endl;
            break;

        case 3:
            std::cout << "skip next instruction if VX==NN" << std::endl;
            break;

        case 4:
            std::cout << "skips next instruction if VX != NN" << std::endl;
            break;

        case 5:
            std::cout << "skips next instruction if VX = VY" << std::endl;

            break;

        case 6:
            std::cout << "set register VX to NN" << std::endl;
            V[second] = value;
            break;


        case 7:
            std::cout << "add NN to register VX" << std::endl;
            //unsigned char val = ((third <<4)|lsb);
            V[second] += value;
            break;

        case 8:
            switch (lsb){
                case 0:
                    std::cout << "VX = VY" << std::endl;
                    break;
                case 1:
                    std::cout << "VX |= VY bitwise OR" << std::endl;
                    break;
                case 2:
                    std::cout << "VX &= VY bitwise AND" << std::endl;
                    break;
                case 3:
                    std::cout << "VX ^= VY bitwise xor" << std::endl;
                    break;
                case 4:
                    std::cout << "VX += VY (set ZF to 1 if overflow, 0 if not)" << std::endl;
                    break;
                case 5:
                    std::cout << "VX -= VY (set ZF to 0 if underflow, 1 if not)" << std::endl;
                    break;
                case 6:
                    std::cout << "VX>>1 shift right by 1, store lsb to VF" << std::endl;
                    break;
                case 7:
                    std::cout << "VX = VY-VX if underflow, vf =0. 1 if not." << std::endl;
                    break;
                case 14:
                    std::cout << "VX<<=1 SET VF TO ONE IF SOMETHING" << std::endl;
                    break;
                
            }
            break;

        case 9:
            std::cout << "skip next instruction if vx!=vy" << std::endl;
            break;
        case 10: //A
            std::cout << "set index register I" << std::endl;
            I  = (second << 8) | (third <<4) | lsb;
            //std::cout << I << "set" << std::endl;
    
            break;
        case 11: //B
            std::cout << "jump to address NNN plus V0" << std::endl;
            break;
        case 12: //C
            std::cout << "VX = rand() & NN" << std::endl;
            break;
        
        case 13: //D
            std::cout << "display/draw" << std::endl;
            //std::cout << V[second] << " " << V[third] << std::endl;
            for (int i = V[second]; i<(V[second]+8); i++){
                for (int j = V[third]; j< V[third]+lsb;j++){
                    //std::cout << 'wooo' << std::endl;

                    //std::cout << (i+j*64) << std::endl;
                    if (pixels[i+ j*64]==0){
                        pixels[i+j*64]=1;
                        //std::cout << 'helo' << std::endl;
                    }
                    else{
                        pixels[i+j*64]=0;
                        V[0xF]=1;
                    }
                }
            }
                //for j in y:
                    //if pixel[i+ j*64]==0: pixel[i+j*64]=1;
                   
            //

            break;
        case 14: //E
            std::cout << "e stuff" << std::endl;

            break;
        case 15: //F
            std::cout << "f" << std::endl;

            break;
        
        
    }


}
int Chip::execute(){

}


//how tf do i do this
bool Chip::load_rom(const char path[]){
    //iterate through the ch8 file, starting from memory[I], I=0x200
    std::ifstream reader;

    reader.open(path, std::ios::binary);
    if (!reader){
        std::cout << "mmm wrong song" << std::endl;
        return false;
    }
    reader.seekg(0, reader.end);
    int length = reader.tellg();
    reader.seekg(0, reader.beg);

    std::cout << "working.." << length << std::endl;
    unsigned char instruction;
    I=0x200;
    PC =0x200;
    unsigned char* pointer = memory;
    while (!reader.eof()){
       // memory

        while (reader.read((char*)(&instruction), sizeof(instruction))){
            
            std::cout << std::hex << (int)(instruction) << " ";
            memory[I] = (int)instruction;
            I=I+1;

        }
        
        
    }
    std::cout <<"done reading " << std::endl;
    //std::cout << "I: " << I << std::endl;
    //std::cout << "i 2: " << memory[I-1] << std::endl;
    reader.close();
    I=0x200;

    return true;
}