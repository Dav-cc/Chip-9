#include "chip8.h"
#include <fstream>
#include <random>
#include <chrono>

const unsigned int START_ADDRESS                     = 0x200; 
const unsigned int FONT_STARTING_ADDRESS             = 0x050; 
const unsigned int FONTSET_SIZE                      = 80;

// reading file and fill the memory
void Chip8::LoadRom(char const* filename){
    std::ifstream file(filename, std::ios::binary | std::ios::ate );
    if(file.is_open()){
        std::streampos size = file.tellg();
        char* buffer = new char[size];

        file.seekg(0, std::ios::beg);
        file.read(buffer, size);
        file.close();

        for(long i = 0 ; i < size ;++i){
            memory[START_ADDRESS + i] = buffer[i];   // NOTE: as mentioned befor memory address till 0x200 is reservd
        }
        delete[] buffer;
    }
}

Chip8::Chip8()
    : randGen(std::chrono::system_clock::now().time_since_epoch().count())
{
    PC = START_ADDRESS;

    uint8_t fontset[FONTSET_SIZE] = {
        0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
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

    for(unsigned int i = 0 ; i <    FONTSET_SIZE; ++i){
        memory[FONT_STARTING_ADDRESS + i] = fontset[i];
    }
    randByte = std::uniform_int_distribution<uint8_t>(0, 255U);
}
