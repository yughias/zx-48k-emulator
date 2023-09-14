#include <hardware.h>

size_t master_clock_counter;

z80_t cpu = {
    .readMemory  = getReadAddr,
    .writeMemory = getWriteAddr,
    .readIO      = getReadIO,
    .writeIO     = getWriteIO
};

void initAll(){
    initCPU(&cpu);
    initMemory();
    initAudio();
}

void freeAll(){
    freeMemory();
    freeAudio();
}

void emulateCpu(){
    if(!cpu.cycles)
        stepCPU(&cpu);
    cpu.cycles--;
}

void sendInterrupt(){
    cpu.INTERRUPT_PENDING = true;
}

void emulateHardware(){
    updateColorFlash();

    for(master_clock_counter = 0; master_clock_counter < CLOCK_PER_FRAME; master_clock_counter++){
        if(*cpu.PC == TRAP_TAPE_ROUTINE_ADDR && cpu.cycles == 0 && tapeFormat == TAP_INSTANT_LOAD){
            trapTapeRoutine();
        }

        emulateCpu();
        emulateAudio();
        emulateTape();
        
        emulateUlaRender(master_clock_counter);
    }

    sendInterrupt();
}