#ifndef CHIP_H
#define CHIP_H

#include <vector>
#include <map>
#include "window.h"
#include <random>

class Chip {
    private:
    
// Declare a global distribution object
        bool draw;
        Window display;
        uint8_t pixels[63*32] = {0};
        //unsigned short opcode;
        uint8_t memory[4096];

        std::map<uint8_t, uint8_t> input;

        uint16_t PC; //2 bytes = 16 bits, but we only use 12.

        uint16_t I; //points to location in memory. index.
        std::vector<uint16_t> stack; //two bytes for each stack. stack b empty tho
        uint8_t delay_timer; //one byte timer
        uint8_t sound_timer; //one byte sound timer //gives out beep when not 0.

        
        std::map<uint8_t, uint8_t> V; //registers
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
        int handle_input(SDL_Event event);
        int decode(uint16_t instruction);
        uint16_t fetch();
        void interpret_program(); //emulate a cycle 
        Chip();
        bool load_rom(const char path[]);
};
#endif