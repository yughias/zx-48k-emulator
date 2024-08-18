#include <hardware.h>
#include <loader.h>

uint8_t* MEMORY;
uint8_t NOT_MAPPED[2];

uint8_t readMemory(z80_t* z80, uint16_t addr){
    emulateMemoryContention(master_clock_counter, addr);
    return MEMORY[addr];
}

void writeMemory(z80_t* z80, uint16_t addr, uint8_t byte){
    emulateMemoryContention(master_clock_counter, addr);
    if(addr < RAM_ADDR){
        return;
    }

    MEMORY[addr] = byte;
}

uint8_t readIO(z80_t* z80, uint16_t ioaddr){
    if(!(ioaddr & 1))
        ulaContention(master_clock_counter);

    if(!(ioaddr & 0b11100000))
        return KEMPSTON_REG;

    calculateULAReg(ioaddr >> 8);
    return WORK_REG;
}

void writeIO(z80_t* z80, uint16_t ioaddr, uint8_t byte){
    if(!(ioaddr & 1)){
        ulaContention(master_clock_counter);
        ULA = byte;
        return;
    }
    
    if((ioaddr >> 14) == 0b11 && !(ioaddr & 0b10)){
        AY_SELECTED_REG = byte;
        return;
    }

    if((ioaddr >> 14) == 0b10 && !(ioaddr & 0b10)){  
        AY_REG[AY_SELECTED_REG & 0x0F] = byte;
        if(AY_SELECTED_REG == AY_ENV_SHAPE)
            updateEnvelopeAy();
        return;
    }
}

void initMemory(){
    MEMORY = malloc(MEMORY_SIZE);
    loadROM("data/ROMs/48k.rom");
}

void freeMemory(){
    free(MEMORY);
}

void emulateMemoryContention(size_t clock, uint16_t addr){
    if(addr < 0x4000 || addr > 0x7FFF)
        return;
    
    ulaContention(clock);
}

void ulaContention(size_t clock){
    const int delay_pattern[] = {6, 5, 4, 3, 2, 1, 0, 0};
    const size_t delay_pattern_size = 8;

    int vertical_line = clock / LINE_T_STATES;
    int clockOffset = clock % LINE_T_STATES;

    if(vertical_line < 64 || vertical_line >= 64+SCREEN_HEIGHT)
        return;

    if(clockOffset >= SCREEN_T_STATES)
        return;

    cpu.cycles += delay_pattern[ clockOffset % delay_pattern_size];
}