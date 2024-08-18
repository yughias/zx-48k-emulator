#ifndef __MEMORY_H__
#define __MEMORY_H__

#include <stdint.h>
#include <stdbool.h>

#define MEMORY_SIZE 0x10000
#define RAM_ADDR    0x4000

extern uint8_t* MEMORY;

uint8_t readMemory(z80_t*, uint16_t);
void    writeMemory(z80_t*, uint16_t, uint8_t);

uint8_t readIO(z80_t*, uint16_t);
void writeIO(z80_t*, uint16_t, uint8_t);

void initMemory();
void freeMemory();

void emulateMemoryContention(size_t, uint16_t);
void ulaContention(size_t);

#endif