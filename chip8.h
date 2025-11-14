#ifndef __CHIP__
#define __CHIP__


#include <cstdint>
#include <vector>
#include <array>
#include <random>
#include <chrono>
#include <iterator>


using namespace std;

class Chip8{
public:
    uint16_t opcode;

    /*
     * chip8 use 4Kb memory frome address 0x000 to 0xFFF 
     * this address segmented into 3 parts
     *  {
     *      0x000 - 0x1FF : this part is reserved for chip8 interpreter but in ours we dont read or write frome this segmanet
     *      0x050 - 0x0A0 : this is for 16 built in characters (0-F)
     *      0x200 - 0xFFF : instructions from rom will be stored in the address 0x200 and anything left after the rom is free to use
     *  }
     */
    array<uint8_t, 4096> memory{};

    /*
     * registers is a dedicated locations for cpu to use for storage and cpu uses this special places for calculations 
     * in our simulator we have 16 8bit registers (from V0 to VF) each register can hold a value from 0x00 to 0xFF
     */
    array<uint8_t, 16> registers{};

    /*
     * this register have to hold memory address for next instruction this is why it should be 16 bit cause last 
     * memory addres stores in 0xFFF and memory address is 16bit 
     */ 
    uint16_t VI;
 
    /*
     * pc or programm counter stores the next instruction cpu need to handle and its 16 bit 
     */
    uint16_t PC;

    /*
     * when programm CALL's it should remmeber "wher i came from" cause when it finished should come back to place where
     * we jumped out chip8 only can remembe 16 calls 
     */
    array<uint16_t, 16> stack{};


    /*
     * sp always points to wher we are in the stack and holds its addres this register is stack pointer
     */
    uint8_t SP;

    /*
     * The CHIP-8 has an additional memory buffer used for storing the
     * graphics to display. It is 64 pixels wide and 32 pixels high. Each pixel
     * is either on or off, so only two colors can be represented.
     *
     * Understanding and then emulating its operation is probably the most
     * challenging part of the entire project (but still very easy compared to
     * the NES).
     *
     * I’ll cover the exact implementation of the draw instruction down
     * below, but first let’s cover how the drawing works. As mentioned, a pixel
     * can be either on or off. In our case, we’ll use a uint32 for each pixel
     * to make it easy to use with SDL (discussed later), so on is 0xFFFFFFFF
     * and off is 0x00000000.
     *
     * The draw instruction iterates over each pixel in a sprite and XORs
     * the sprite pixel with the display pixel.
     *
     *        Sprite Pixel Off XOR Display Pixel Off = Display Pixel Off
     *        Sprite Pixel Off XOR Display Pixel On = Display Pixel On
     *        Sprite Pixel On XOR Display Pixel Off = Display Pixel On
     *        Sprite Pixel On XOR Display Pixel On = Display Pixel Off
     *
     * In other words, a display pixel can be set or unset with a sprite. This
     * is often done to only update a specific part of the screen. If you knew
     * you had drawn a sprite at (X,Y) and you now want to draw it at (X+1,Y+1),
     * you could first issue a draw command again at (X,Y) which would erase the
     * sprite, and then you could issue another draw command at (X+1,Y+1) to
     * draw it in the new location. This is why moving objects in CHIP-8 games
     * flicker.
     */
    array<uint32_t, 64*32> display{};

    /*
     * chip8 uses 8 bit delay timer if it's 0 it stays zero but if it's loaded with value it count it down with rate of 60Hz
     */
    uint8_t delaytimer; 

    /*
     * its another timer in chip8 produce sound (with 60Hz rate) but its single ton buzz 
     */
    uint8_t soundtimer;

    /*
     * Chip-8 has 16 input keys that match the first 16 hex values. 0 to F
     * each key can be pressed or not pressed.
     * Keypad       Keyboard
     * +-+-+-+-+    +-+-+-+-+
     * |1|2|3|C|    |1|2|3|4|
     * +-+-+-+-+    +-+-+-+-+
     * |4|5|6|D|    |Q|W|E|R|
     * +-+-+-+-+ => +-+-+-+-+
     * |7|8|9|E|    |A|S|D|F|
     * +-+-+-+-+    +-+-+-+-+
     * |A|0|B|F|    |Z|X|C|V|
     * +-+-+-+-+    +-+-+-+-+
     */
    array<uint8_t, 16> keypad{};




    void LoadRom(char const* filename);
    Chip8();
    std::default_random_engine randGen;
    std::uniform_int_distribution<uint8_t> randByte;
};





#endif  // __CHIP__
