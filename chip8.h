#ifndef __CHIP__
#define __CHIP__



#include <cstdint>
#include <random>
#include <chrono>
#include <array>
#include <iterator>

const unsigned int START_ADDRESS                  = 0x200;
const unsigned int FONTSET_SIZE                   = 80;
const unsigned int FONTSET_START_ADDRESS          = 0x50;



class Chip8{
 public:
    std::default_random_engine randGen;
    std::uniform_int_distribution<uint8_t> randByte;
    /*
     *  this are general perpose registers use for calculaton
     *  16 gpr regiseters that every one has 8bit (2bytes)
     */
    std::array<uint8_t, 16> registers{}; 


    /**
     * 
     *   chip 8 has a 4KB memory and it means 4096 byts from 0x000 to oxFFF
     *   this space devited into three segments :
     *   1. 0x000 to 0x1FF : reserved for chip 8 intrpreter
     *   2. 0x050 to 0x0A0 : store 16 built in characters (some roms expecte to we have this segment)
     *   3. 0x200 to 0xFFF : Instructions from the ROM will be stored starting at 0x200, and anything left after the ROM’s space is free to use.
     */
    std::array<uint8_t, 4096> memory{};


    /**
     *  is a register that stores memory addresses and caus last memory address is oxFFF 8bit register is so little we make it 16 bit.
     */
    uint16_t index{};


    /**
     * the actual program instructions are stored in memory starting at address 0x200.
     * The CPU needs a way of keeping track of which instruction to execute next.
     * The Program Counter (PC) is a special register that holds the address of the next instruction to execute.
     * Again, it’s 16 bits because it has to be able to hold the maximum memory address (0xFFF).
     */
    uint16_t pc{};


    std::array<uint16_t,16>stack{};



    uint8_t sp{};


    uint8_t delayTimer{};



    uint8_t soundTimer{};
    

    std::array<uint8_t, 16> keypad{};


    std::array<uint32_t, 64 * 32> video;


    uint16_t opcode{};


    void LoadRom(const char* filename);

    Chip8() ;

    
};



#endif  // __CHIP__
