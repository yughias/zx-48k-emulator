#ifndef __MEMORY_H__
#define __MEMORY_H__

#include <stdint.h>
#include <stdbool.h>

#define MEMORY_SIZE 0x10000
#define RAM_ADDR    0x4000

extern uint8_t* MEMORY;

uint8_t* getReadAddr(uint16_t);
uint8_t* getWriteAddr(uint16_t);

uint8_t* getReadIO(uint16_t);
uint8_t* getWriteIO(uint16_t);

void initMemory();
void freeMemory();

void emulateMemoryContention(size_t, uint16_t);
void ulaContention(size_t);

#endif