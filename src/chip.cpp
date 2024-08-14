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
                    std::cout << "clear screen" << std::endl;
                    std::fill(std::begin(pixels), std::end(pixels), 0);
                    

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
            break;

        case 3:
            break;

        case 4:
            break;

        case 5:
            break;

        case 6:
            //std::cout << "set register VX" << std::endl;
            //7XNN

            //unsigned char val = ((third << 4) | lsb);
            //vx = NN
            V[second] = value;
            
            break;

        case 7:
            std::cout << "add val to register VX" << std::endl;
            //unsigned char val = ((third <<4)|lsb);
            
            
            V[second] += value;
            break;

        case 8:
            break;

        case 9:
            break;
        case 10: //A
            std::cout << "set index register I" << std::endl;
            I  = (second << 8) | (third <<4) | lsb;
            std::cout << I << "set" << std::endl;
    
            break;
        case 11: //B
            break;
        case 12: //C
            break;
        
        case 13: //D
            std::cout << "display/draw" << std::endl;
            std::cout << "display/draww" << std::endl;


            std::cout << V[second] << " " << V[third] << std::endl;
            std::cout <<"guh" << std::endl;
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
    std::ifstream reader;

    reader.open(path, std::ios::binary);
    if (!reader){
        std::cout << "mmm wrong song" << std::endl;
        return false;
    }
    reader.seekg(0, reader.end);
    int length = reader.tellg();
    reader.seekg(0, reader.beg);

    std::cout << "working.." << std::endl;
    unsigned char instruction;
    I=0x200;
    PC =0x200;
    while (!reader.eof()){
       // memory

        //instruction = reader.read()
        reader >> instruction;
        if (reader.fail()){
            I=0x200;
            reader.close();
            break;
        }
        memory[I] = instruction;
        std::cout <<I << std::endl;
        std::cout <<std::hex << instruction << std::endl;
        I=I+1;
    }

    reader.close();
    I=0x200;

    return true;
}