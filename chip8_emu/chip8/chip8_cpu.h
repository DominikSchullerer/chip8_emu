#ifndef _CHIP8_CPU_H_
#define _CHIP8_CPU_H_

#include "chip8_status.h"

typedef struct chip8_cpu_t chip8_cpu_t;

///////////////////////////////////////////////////////////////////////////////

chip8_status_t chip8_cpu_create(chip8_cpu_t** pout_chip8_cpu);

void chip8_cpu_destroy(chip8_cpu_t* chip8_cpu);

#endif // !_CHIP8_CPU_H_
