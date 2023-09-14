#ifndef __HARDWARE_H__
#define __HARDWARE_H__

#define CLOCK_PER_FRAME 69888

#include <stdio.h>

#include <z80.h>
#include <video.h>
#include <audio.h>
#include <memory.h>
#include <io_port.h>
#include <tape.h>

extern size_t master_clock_counter;
extern z80_t cpu;

void initAll();
void freeAll();

void emulateHardware();
void emulateCpu();
void sendInterrupt();

#endif