#ifndef CHIP_H
#define CHIP_H

#include <vector>
#include <map>
#include "window.h"
#include <random>

class Chip {
    private:
    
// Declare a global distribution object
   
        Window display;
        uint8_t pixels[63*32] = {0};
        //unsigned short opcode;
        uint8_t memory[4096];

        unsigned short PC; //2 bytes = 16 bits, but we only use 12.

        unsigned short I; //points to location in memory. index.
        std::vector<short> stack; //two bytes for each stack. stack b empty tho
        unsigned char delay_timer; //one byte timer
        unsigned char sound_timer; //one byte sound timer //gives out beep when not 0.

        unsigned char V0, V1, V2, V3, V4, V5, V6, V7, V8, V9, VA, VB, VC, VD, VE, VF; //REGISTERS
        std::map<uint8_t, uint8_t> V;
        //fontset
        uint8_t chip8_fontset[80] = 
        {
            0xF0, 0X90, 0X90, 0X90, 0xF0, //0  //
            0x20, 0x60, 0x20, 0x20, 0x70, // 1
            0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
            0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
            0x90, 0x90, 0xF0, 0x10, 0x10, // 4
            0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
            0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
            0xF0, 0x10, 0x20, 0x40, 0x40, // 7
            0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
            0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
            0xF0, 0x90, 0xF0, 0x90, 0x90, // A
            0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
            0xF0, 0x80, 0x80, 0x80, 0xF0, // C
            0xE0, 0x90, 0x90, 0x90, 0xE0, // D
            0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
            0xF0, 0x80, 0xF0, 0x80, 0x80  // F


        };

        std::map<uint8_t, unsigned char> font_map;
        
        int execute();

    public:
        int decode(unsigned short instruction);
        unsigned short fetch();
        void interpret_program(); //emulate a cycle 
        Chip();
        bool load_rom(const char path[]);
};
#endif