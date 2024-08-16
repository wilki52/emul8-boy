#include "chip.h"
#include "window.h"
#include <iostream>
#include <fstream>
#include <SDL2/SDL.h>
#include <ios>
#include <random>
Chip::Chip(){

    //random here
    std::random_device dev;
    std::mt19937 rng;
    std::uniform_int_distribution<std::mt19937::result_type> dist6(0,255);
    //rng(dev(), dist6(0, 255));
    //pixels[0]=1;
    //pixels[3]=1;
    //pixels[64]=1;
    V[0x0], V[0x1],V[0x2],V[0x3],V[0x4],V[0x5],V[0x6],V[0x7],V[0x8],V[0x9],V[0xA],V[0xB],V[0xC],V[0xD],V[0xE],V[0xF] = 0;

    int counter = 0;
    //put font into memory. 
    for (int i = 0x050; i< 0x09F; i++){
        memory[i] = chip8_fontset[counter];
        counter++;
    }

    

    //create font map

    display.open();
}


void Chip::interpret_program(){
    SDL_Event e;

    bool running = true;
    while (running){
        SDL_PollEvent(&e);
        //if (SDL_PollEvent(&e)!=0){

            if (e.type==SDL_QUIT){
                running = false;
            }
            //store here?
        //}
        unsigned short instruction = fetch();
        decode(instruction);

        delay_timer -=1;
        sound_timer -=1;
        display.updateRender(pixels);
//   SDL_Delay(50);

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
    uint8_t lsb = instruction & 0xF;
    uint8_t third = (instruction>>4) & 0xF;
    uint8_t second = (instruction>>8) & 0xF;
    uint8_t msb = (instruction>>12) & 0xF;
    //std::cout << std::hex << instruction << std::endl;
    //std::cout << std::hex << msb << std::endl;
    //std::cout << std::hex << second << std::endl;
    //std::cout << std::hex << third << std::endl;
    //std::cout << std::hex << lsb << std::endl;
    unsigned short value = ((third << 4) | lsb);

    if (msb==0xC){
       // std::random_device dev;
       // std::mt19937 rng(dev());
       // std::uniform_int_distribution<std::mt19937::result_type> dist6(0,255);
    }
  

    switch (msb){
        case 0:
            switch (second){
                case 0: //00E0 
                    //update window?
                    
                    switch (lsb){

                        case 0: //00E0
                            std::cout << "clear screen" << std::endl;
                            std::fill(std::begin(pixels), std::end(pixels), 0);
                            break;
                        default: //00EE
                            std::cout << "return from subroutine" << std::endl;
                            PC = stack.back();
                            stack.pop_back();
                        
                    }

                    
                    

                break;
            }

            break;

        case 1:
       
            std::cout << "jump" << std::endl;
            //return 
            PC = ((second << 8) | (third <<4) | lsb);
            PC = PC;
            std::cout << std::hex << PC << std::endl;
            break;

        case 2:
            std::cout << "call subroutine at NNN" << std::endl;
            stack.push_back(PC);
            PC = ((second << 8) | (third <<4) | lsb);
            break;

        case 3: //3XNN
            std::cout << "skip next instruction if VX==NN" << std::endl;
            if (V[second] == value){
                PC= PC+2;
            }
            break;

        case 4: //4XNN
            std::cout << "skips next instruction if VX != NN" << std::endl;
            if (V[second] != value){
                PC= PC+2;
            }
            break;

        case 5:
            std::cout << "skips next instruction if VX = VY" << std::endl;
            if (V[second] == V[third]){
                PC= PC+2;
            }
            break;

        case 6: //6XNN
            std::cout << "set register VX to NN" << std::endl;
            V[second] = value;
            break;


        case 7: //7XNN
            std::cout << "add NN to register VX" << std::endl;
            //unsigned char val = ((third <<4)|lsb);
            V[second] = V[second] + value;
            break;

        case 8: //8
            switch (lsb){
                case 0: //8XY0
                    std::cout << "VX = VY" << std::endl;
                    V[second] = V[third];
                    break;
                case 1://8XY1
                    std::cout << "VX |= VY bitwise OR" << std::endl;
                    V[second] = (V[second]|V[third]);
                    break;
                case 2:
                    std::cout << "VX &= VY bitwise AND" << std::endl;
                    V[second] = (V[second] & V[third]);

                    break;
                case 3:
                    std::cout << "VX ^= VY bitwise xor" << std::endl;
                    V[second] = (V[second] ^ V[third]);

                    break;
                case 4:
                    std::cout << "VX += VY (set ZF to 1 if overflow, 0 if not)" << std::endl;
                    //
                    
                    V[second] = V[second] + V[third]; //would need to do 

                    if (V[second] >255 ){ //overflow, check for uint8_t
                        
                        V[0xf] = 1;
                    }
                    else{
                        V[0xf]=0;
                    }
                    break;
                case 5:
                    std::cout << "VX -= VY (set ZF to 0 if underflow, 1 if not)" << std::endl;
                    

                    V[second] = V[second] - V[third];
                    
                    if (V[second] < 0){
                        V[0xF] = 0;
                    }
                    else{
                        V[0xF] = 1;
                    }
                    break;
                case 6:
                    std::cout << "VX>>1 shift right by 1, store lsb to VF" << std::endl;
                    V[0xF] = (V[second] & 0x1);
                    V[second] = V[second] >>1;
                    break;
                case 7:
                    std::cout << "VX = VY-VX if underflow, vf =0. 1 if not." << std::endl;
                    V[second] = V[third] - V[second];
                    if (V[second] >=0){
                        V[0xF] = 1;
                    }
                    else{
                        V[0xF] = 0;
                    }
                    break;
                case 14:
                    std::cout << "VX<<=1 SET VF TO ONE IF SOMETHING" << std::endl;
                    unsigned char v_msb = (V[second] >> 7 & 0x1);
                    V[second] = V[second] <<1;
                    if (v_msb == 0x1){
                        V[0xF] = 1;
                    }
                    else{
                        V[0xF] = 0;
                    }
                    break;
                
            }
            break;

        case 9:
            std::cout << "skip next instruction if vx!=vy" << std::endl;
            if (V[second] != V[third]){
                PC = PC +2;
            }
            
            break;
        case 10: //A
            std::cout << "set index register I" << std::endl;
            I  = (second << 8) | (third <<4) | lsb;
            //std::cout << I << "set" << std::endl;
    
            break;
        case 11: //B
            std::cout << "jump to address NNN plus V0" << std::endl;
            PC= V[0x0]+((second << 8) | (third <<4) | lsb); //v0 + NNN
            break;
        case 12: //C
            std::cout << "VX = rand() & NN" << std::endl;
             
            //std::cout << "rand: " << dist6(rng) << std::endl;
            V[second] = std::rand() % 256 & value;
            break;
        
        case 13: //D
            std::cout << "display/draw" << std::endl;


            V[0xF] = 0;
            //std::cout << V[second] << " " << V[third] << std::endl;
            for (int j = 0; j<lsb ; j++){
        
                unsigned short sprite = memory[I+j];
                //std::cout << I << " + " << j << ": "<<  sprite << std::endl;

                /*
                if ((sprite)>0){
                    //std::cout << "sprite is 1" << std::endl;
                }
                else{
                    //std::cout << "sprite is 0" << std::endl;
                }
                */
                for (int i = 0; i<=(7); i++){
                    //std::cout << 'wooo' << std::endl;

                    //std::cout << (i+j*64) << std::endl;
                    int bit = ((sprite >> 7-i)& 0x01);
    
                    if ((bit)>0){
                        
                        if (pixels[(V[second]+i)+ (V[third]+j)*64]==1){
                            pixels[(V[second]+i)+(V[third]+j)*64]=0;
                            V[0xF]=1;
                        }
                        else{
                            pixels[(V[second]+i)+ (V[third]+j)*64]=1;
                        }
                        if (((V[second]+i)!=0) && (V[second]+i) %63==0){
                            break;
                        }
                        //std::cout << 'helo' << std::endl;
                    }
                }
            }
            break;
        case 14: //E
            std::cout << "e stuff" << std::endl;
            switch (lsb){
                case 1: //EXA1
                    std::cout << "skip if VX is not prressed" << std::endl;
                    SDL_Event event;
                    
                    if (SDL_PollEvent(&event)!=0){
                        if (event.key.keysym.scancode != V[second]){
                            PC= PC+2;
                        }
                    }
                    else{
                        PC=PC+2;
                    }
                    
                   PC= PC+2;
                    break;
                case 14: //EX9E
                    std::cout << "skip next i if key stored in vx is pressed" << std::endl;
                    SDL_Event eve;
                    
                    if (SDL_PollEvent(&eve)!=0){
                        if (eve.key.keysym.scancode == V[second]){
                            PC=PC+2;
                        }
                    }
                    
                    break;
                    
            }
            break;
        case 15: //F
            std::cout << "f" << std::endl;
            switch ((third<<4)| lsb){
                case (0x07): //FX07
                    std::cout << "set delay timer to VX" << std::endl;
                    V[second] = delay_timer;
                    break;
                case (0x0A): //FX0A
                    std::cout << "A key press is awaited, and then stored in VX (blocking operation, all instruction halted until next key event," << std::endl;
            
                    SDL_Event ev;
                    //while input:

                    while (SDL_PollEvent(&ev)){
                        if (ev.type == SDL_KEYDOWN){

                        
                        switch (ev.key.keysym.scancode){
                            case SDL_SCANCODE_1:
                                V[second] = 0x1;
                                break;
                            case SDL_SCANCODE_2:
                                V[second] = 0x2;
                                break;
                            case SDL_SCANCODE_3:
                                V[second] = 0x3;
                                break;
                            case SDL_SCANCODE_4:
                                V[second] = 0xC;
                                break;

                            case SDL_SCANCODE_Q:
                                V[second] = 0x4;
                                break;
                            case SDL_SCANCODE_W:
                                V[second] = 0x5;
                                break;
                            case SDL_SCANCODE_E:
                                V[second] = 0x6;
                                break;
                            case SDL_SCANCODE_R:
                                V[second] = 0xD;
                                break;

                            case SDL_SCANCODE_A:
                                V[second] = 0x7;
                                break;
                            case SDL_SCANCODE_S:
                                V[second] = 0x8;
                                break;
                            case SDL_SCANCODE_D:
                                V[second] = 0x9;
                                break;
                            case SDL_SCANCODE_F:
                                V[second] = 0xE;
                                break;

                            case SDL_SCANCODE_Z:
                                V[second] = 0xA;
                                break;
                            case SDL_SCANCODE_X:
                                V[second] = 0x0;
                                break;
                            case SDL_SCANCODE_C:
                                V[second] = 0xB;
                                break;
                            case SDL_SCANCODE_V:
                                V[second] = 0xF;
                                break;
                            default:
                                PC = PC-2;
                        }
                        }
                       // V[second] = ev.key.keysym.scancode;
            
                    }
                    //else{
                    //    PC= PC-2;
                    //} 
                    //else: return 0, aka PC=PC-2;
                    break;
                case (0x15): //FX07
                    std::cout << "Sets the delay timer to VX." << std::endl;
                    delay_timer = V[second];
                    break;
                case (0x18): //FX07
                    std::cout << "Sets the sound timer to VX." << std::endl;
                    sound_timer = V[second];
                    break;
                case (0x1E): //FX1E
                    std::cout << "Adds VX to I. VF is not affected" << std::endl;
                    I = I+ V[second];
                    break;
                case (0x29): //FX07
                    std::cout << "Sets I to the location of the sprite for the character in VX. Characters 0-F (in hexadecimal) are represented by a 4x5 font" << std::endl;
                    //TODO: put font in memory
                    I= ((V[second])* 5)+0x050;
                    //I= 0x055;
                    break;
                case (0x33): //FX07
                    std::cout << "Stores the binary-coded decimal representation of VX, with the hundreds digit in memory at location in I, the tens digit at location I+1, and the ones digit at location I+2." << std::endl;
                    memory[I+2] = V[second]%10;
                    memory[I+1] = V[second]/10%10;
                    memory[I] = V[second]/100%10;
                    break;
                case (0x55): //FX07
                    std::cout << "Stores from V0 to VX (including VX) in memory, starting at address I. The offset from I is increased by 1 for each value written, but I itself is left unmodified." << std::endl;
                    //stores from v0 to vx
                    //for 0 to 0xX, store at I
                    for (int i= 0; i<= second; i++){
                        memory[I+i] = V[i];
                    }
                    break;
                case (0x65): //FX07
                    std::cout << "Fills from V0 to VX (including VX) with values from memory, starting at address I. The offset from I is increased by 1 for each value read, but I itself is left unmodified." << std::endl;
                    for (int i= 0x0; i<= second; i++){
                        V[i] = memory[I+i];
                    }
                    
                    break;
                
                
                
            }
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
            
            std::cout << "I: " << I << " hex: "<< std::hex << (int)(instruction) << " ";
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