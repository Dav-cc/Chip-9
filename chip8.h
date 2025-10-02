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
const unsigned int VIDEO_WIDTH                    = 64;
const unsigned int VIDEO_HEIGHT                   = 32;


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


    std::array<uint32_t, VIDEO_WIDTH * VIDEO_HEIGHT> video;


    uint16_t opcode{};


    void LoadRom(const char* filename);

    Chip8() ;


    // CLS
    // clear the display
    void OP_00E0();

    // Ret
    // return from a subroutine
    void OP_00EE();

    // Jump to location nnn
    // the interpreter sets the pc to nnn
    void OP_1nnn();


    // CALL addr
    // call subroutine at nnn
    void OP_2nnn();

    // SE Vx, byte
    // skip next instruction if Vx = kk
    void OP_3xkk();

    // SNE Vx, byte
    // skip next instruction if Vx != kk
    void OP_4xkk();

    // SE Vx, Vy
    // skip next instruction if Vx = Vy
    void OP_5xy0();

    // LD Vx, byte
    // set Vx = kk
    void OP_6xkk();

    // ADD Vx, byte
    // set Vx = Vx+kk
    void OP_7xkk();

    // LD Vx, Vy
    // set Vx = Vy
    void OP_8xy0();

    // OR Vx, Vy
    // set Vx = Vx OR Vy
    void OP_8xy1();

    // AND Vx, Vy
    // set Vx = Vx AND Vy
    void OP_8xy2();

    // XOR Vx, Vy
    // set Vx = Vx XOR Vy
    void OP_8xy3();

    // ADD Vx, Vy
    // set Vx = Vx + Vy, set Vf = carry
    void OP_8xy4();

    // SUB Vx, Vy
    // set Vx = Vx - Vy, set Vf = not borrow
    void OP_8xy5();

    // SHR Vx
    // set Vx = Vx SHR 1
    void OP_8xy6();

    // SUBN Vx, Vy
    // set Vx = Vy - Vx, set Vf = Not borrow
    void OP_8xy7();

    // SHL Vx {,Vy}
    // Set Vx = Vx SHL 1
    void OP_8xyE();

    // SNE Vx, Vy
    // skip next instruction if Vx != Vy
    void OP_9xy0();

    // LD I, Addr
    // set I = nnn
    void OP_Annn();

    // JP V0, addr
    // jump to location nnn+V0
    void OP_Bnnn();

    // RND Vx, byte
    // set Vx = random byte AND kk
    void OP_Cxkk();

    // DRW Vx, Vy, nibble
    // display n byte sprite starting at memory location I at (Vx,Vy), set Vf =
    // collison
    void OP_Dxyn();

    // SKP Vx
    // skip next instruction if key with the value of Vx is pressed
    void OP_Ex9E();

    // SKNP Vx
    // Skip next instruction if key with the value of Vx is not pressed
    void OP_ExA1();

    // LD Vx, DT
    // set Vx = delay timer value
    void OP_Fx07();

    // LD Vx, K
    // wait for a key press, store the value of key in Vx
    void OP_Fx0A();

    // LD DT,Vx
    // set delay timer = Vx
    void OP_Fx15();

    // LD ST, Vx
    // set sounde timer to Vx
    void OP_Fx18();

    // Add I, Vx
    // set I = I + Vx
    void OP_Fx1E();

    // LD F, Vx
    // set I = location of sprite for digit Vx
    void OP_Fx29();

    // LD B, Vx
    // store BCD representation of Vx in memory locations I, I+1, and I+2
    void OP_Fx33();

    // LD [I], Vx
    // store registers V0 through Vx in memory starting at location I
    void OP_Fx55();

    // LD Vx, [I]
    // read registers V0 through Vx from memory starting at location I
    void OP_Fx65();
};



#endif  // __CHIP__
